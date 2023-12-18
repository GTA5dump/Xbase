#include "pch.h"
#include "Pointers.hpp"
#include "Invoker.hpp"

Invoker::Invoker()
{
	init_map();
}

Invoker::~Invoker()
{

}

void Invoker::init_map()
{
	static int init = 0;
	struct twoQwords
	{
		uint64_t first;
		uint64_t second;
	} *p2q;

	if (init) return;
	p2q = reinterpret_cast<twoQwords *>(CROSSMAPPING);
	while (p2q->first)
	{
		native_map.emplace(p2q->first, p2q->second);
		++p2q;
	}
	init = 1;
}

bool Invoker::search_map(nMap map, uint64_t inNative, uint64_t *outNative)
{
	bool found = false;
	for (nMap::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		found = (inNative == it->first);
		if (found) {
			*outNative = it->second;
			break;
		}
	}
	return found;
}

uint64_t Invoker::map_native(uint64_t inNative)
{
	uint64_t currentNative, outNative;
	bool found = false;

	currentNative = inNative;
	found = search_map(native_cache, currentNative, &outNative);
	if (found) return outNative;
	found = search_map(native_map, currentNative, &outNative);
	if (found) {
		native_cache[inNative] = outNative;
		return outNative;
	}

	found = std::find(native_fail.begin(), native_fail.end(), inNative) != native_fail.end();
	if (found) return NULL;
	else native_fail.push_back(inNative);
	return NULL;
}

NativeHandler Invoker::get_native_handler(uint64_t origHash)
{
	uint64_t newHash = map_native(origHash);
	if (newHash == 0) return nullptr;
	NativeRegistrationNew * table = g_pointers->m_registrationTable[newHash & 0xFF];

	for (; table; table = table->getNextRegistration()) {
		for (uint32_t i = 0; i < table->getNumEntries(); i++) {
			if (newHash == table->getHash(i))
				return table->handlers[i];
		}
	}
	return nullptr;
}

void Invoker::native_init(UINT64 hash) 
{
	g_context.Reset();
	g_hash = hash;
}

void Invoker::native_push64(UINT64 value) 
{
	g_context.Push(value);
}

bool Invoker::is_system_native(UINT64 nhash)
{
	if (nhash != 0x4EDE34FBADD967A6 &&
		nhash != 0xE81651AD79516E48 &&
		nhash != 0xB8BA7F44DF1575E1 &&
		nhash != 0xEB1C67C3A5333A92 &&
		nhash != 0xC4BB298BD441BE78 &&
		nhash != 0x83666F9FB8FEBD4B &&
		nhash != 0xC9D9444186B5A374 &&
		nhash != 0xC1B1E9A034A63A62 &&
		nhash != 0x5AE11BC36633DE4E &&
		nhash != 0x0000000050597EE2 &&
		nhash != 0x0BADBFA3B172435F &&
		nhash != 0xD0FFB162F40A139C &&
		nhash != 0x71D93B57D07F9804 &&
		nhash != 0xE3621CC40F31FE2E &&
		nhash != 0x652D2EEEF1D3E62C &&
		nhash != 0xA8CEACB4F35AE058 &&
		nhash != 0x2A488C176D52CCA5 &&
		nhash != 0xB7A628320EFF8E47 &&
		nhash != 0xEDD95A39E5544DE8 &&
		nhash != 0x97EF1E5BCE9DC075 &&
		nhash != 0xF34EE736CF047844 &&
		nhash != 0x11E019C8F43ACC8A &&
		nhash != 0xF2DB717A73826179 &&
		nhash != 0xBBDA792448DB5A89) {
		return false;
	}
	return true;
}

bool is_exception_native(UINT64 nhash)
{
	if (nhash != 0x00DC833F2568DBF6 &&
		nhash != 0x0CF2B696BBF945AE &&
		nhash != 0x8362B09B91893647 &&
		nhash != 0x6D0DE6A7B5DA71F8) {
		return false;
	}
	return true;
}

PUINT64 Invoker::native_call()
{
	auto fn = get_native_handler(g_hash);
	if (fn != soosnull) {
		__try {
			if (is_system_native(g_hash))
				fn(&g_context);
			else
				spoof_call(g_pointers->jmp_rbx, fn, (scrNativeCallContext*)&g_context);
			g_pointers->set_vector_results(&g_context);
		}
		__except (g_exception_address = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER) {
			if (is_exception_native(g_hash)) LOG_INFO("Failed to execute native 0x{} at address {}", g_hash, g_exception_address);
		}
	}
	return reinterpret_cast<uint64_t*>(g_context.GetResultPointer());
}
