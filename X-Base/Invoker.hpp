#pragma once
#include "pch.h"
#include <cstddef>
#include <type_traits>

namespace detail
{
	extern "C" void* _spoofer_stub();

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		// At least 5 params
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first,
				Second second,
				Third third,
				Fourth fourth,
				Pack... pack
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*,
				Pack...
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr,
				pack...
				);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first = First{},
				Second second = Second{},
				Third third = Third{},
				Fourth fourth = Fourth{}
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
				);
		}
	};
}


template <typename Ret, typename... Args>
static inline auto spoof_call(
	const void* trampoline,
	Ret(*fn)(Args...),
	Args... args
) -> Ret
{
	struct shell_params
	{
		const void* trampoline;
		void* function;
		void* rdi;
	};

	shell_params p{ trampoline, reinterpret_cast<void*>(fn) };
	using mapper = detail::argument_remapper<sizeof...(Args), void>;
	return mapper::template do_call<Ret, Args...>((const void*)&detail::_spoofer_stub, &p, args...);
}

class scrNativeCallContext {
protected:

	void *		m_pReturn;
	uint32_t	m_nArgCount;
	void *		m_pArgs;
	uint32_t	m_nDataCount;
	alignas(uintptr_t)uint8_t m_vectorSpace[192];

public:

	template<typename T>
	inline T GetArgument(int idx) {

		intptr_t * arguments = (intptr_t*)m_pArgs;
		return *(T*)&arguments[idx];
	}

	template<typename T>
	inline void SetResult(int idx, T value) {

		intptr_t * returnValues = (intptr_t*)m_pReturn;
		*(T*)&returnValues[idx] = value;
	}

	inline int GetArgumentCount() {

		return m_nArgCount;
	}

	template<typename T>
	inline T GetResult(int idx) {

		intptr_t * returnValues = (intptr_t*)m_pReturn;
		return *(T*)&returnValues[idx];
	}

	static void(*SetVectorResults)(scrNativeCallContext*);
};

class NativeContext : public scrNativeCallContext {
private:

	enum {
		MaxNativeParams = 16,
		ArgSize = 8,
	};

	uint8_t m_TempStack[MaxNativeParams * ArgSize];

public:

	inline NativeContext() {

		m_pArgs = &m_TempStack;
		m_pReturn = &m_TempStack;
		m_nArgCount = 0;
		m_nDataCount = 0;
	}

	template <typename T>
	inline void Push(T value) {

		if (sizeof(T) > ArgSize) {
			throw "Argument has an invalid size";
		}
		else if (sizeof(T) < ArgSize) {
			*reinterpret_cast<uintptr_t*>(m_TempStack + ArgSize * m_nArgCount) = 0;
		}

		*reinterpret_cast<T*>(m_TempStack + ArgSize * m_nArgCount) = value;
		m_nArgCount++;
	}

	inline void Reverse() {

		uintptr_t tempValues[MaxNativeParams];
		uintptr_t * args = (uintptr_t*)m_pArgs;

		for (uint32_t i = 0; i < m_nArgCount; i++) {

			int target = m_nArgCount - i - 1;
			tempValues[target] = args[i];
		}

		memcpy(m_TempStack, tempValues, sizeof(m_TempStack));
	}

	template <typename T>
	inline T GetResult() {

		return *reinterpret_cast<T*>(m_TempStack);
	}
};

struct pass {
	template<typename ...T> pass(T...) {}
};

class NativeManagerContext : public NativeContext {
public:

	NativeManagerContext()
		: NativeContext() {
	}

	void Reset() {

		m_nArgCount = 0;
		m_nDataCount = 0;
	}

	inline void* GetResultPointer() {

		return m_pReturn;
	}
};

typedef void(__cdecl * NativeHandler)(scrNativeCallContext * context);

struct NativeRegistrationNew
{
	uint64_t nextRegistration1;
	uint64_t nextRegistration2;
	NativeHandler handlers[7];
	uint32_t numEntries1;
	uint32_t numEntries2;
	uint64_t hashes;

	inline NativeRegistrationNew* getNextRegistration()
	{
		uintptr_t result;
		auto v5 = reinterpret_cast<uintptr_t>(&nextRegistration1);
		auto v12 = 2i64;
		auto v13 = v5 ^ nextRegistration2;
		auto v14 = (char *)&result - v5;
		do
		{
			*(DWORD*)&v14[v5] = v13 ^ *(DWORD*)v5;
			v5 += 4i64;
			--v12;
		} while (v12);

		return reinterpret_cast<NativeRegistrationNew*>(result);
	}

	inline uint32_t getNumEntries()
	{
		return ((uintptr_t)&numEntries1) ^ numEntries1 ^ numEntries2;
	}

	inline uint64_t getHash(uint32_t index)
	{

		auto naddr = 16 * index + reinterpret_cast<uintptr_t>(&nextRegistration1) + 0x54;
		auto v8 = 2i64;
		uint64_t nResult;
		auto v11 = (char *)&nResult - naddr;
		auto v10 = naddr ^ *(DWORD*)(naddr + 8);
		do
		{
			*(DWORD *)&v11[naddr] = v10 ^ *(DWORD*)(naddr);
			naddr += 4i64;
			--v8;
		} while (v8);

		return nResult;
	}
};

class Invoker
{
public:
	Invoker();
	~Invoker();

	struct CrossMappingEntry
	{
		uint64_t first;
		uint64_t second;
	};

	NativeHandler get_native_handler(uint64_t origHash);
	void native_init(UINT64 hash);
	void native_push64(UINT64 val);
	PUINT64 native_call();
	bool is_system_native(UINT64 nhash);
	bool search_map(nMap map, uint64_t inNative, uint64_t *outNative);
	void init_map();
	uint64_t map_native(uint64_t inNative);

private:
	NativeManagerContext g_context{};
	UINT64 g_hash{};
	void* g_exception_address{};
	nMap native_cache{};
	std::unordered_map<uint64_t, uint64_t> native_map{};
	std::vector<uint64_t> native_fail{};
};

inline std::unique_ptr<Invoker> g_invoker;