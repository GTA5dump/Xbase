#pragma once
#include "pch.h"
#include "Utility.hpp"

class sysMemAllocator;
struct tlsContext {
	char m_padding1[0xC8];          // 0x00
	sysMemAllocator *m_allocator;   // 0xC8
	char m_padding2[0x760];         // 0xD0
	scrThread *m_script_thread;     // 0x830
	bool m_is_script_thread_active; // 0x838
};

class Scripting
{
public:
	Scripting() = default;
	~Scripting() = default;

	GtaThread *findScriptThread(Hash hash)
	{
		for (auto thread : *(g_pointers->m_thread_list))
			if (thread && thread->m_context.ThreadID && thread->m_handler && thread->m_script_hash == hash)
				return thread;
		return nullptr;
	}

	void executeInScriptThread(Hash hash, Function func)
	{
		auto tls_ctx = *reinterpret_cast<tlsContext**>(__readgsqword(0x58));
		auto thread = findScriptThread(hash);
		if (!thread) return;
		auto og_thread = tls_ctx->m_script_thread;
		tls_ctx->m_script_thread = thread;
		tls_ctx->m_is_script_thread_active = true;
		func();
		tls_ctx->m_script_thread = og_thread;
		tls_ctx->m_is_script_thread_active = og_thread != nullptr;
	}
};

inline std::unique_ptr<Scripting> g_scripting;