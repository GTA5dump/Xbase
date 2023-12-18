#pragma once
#include "pch.h"

class ptr_manage {
public:
	ptr_manage(void* hand = 0);
	ptr_manage(std::uintptr_t hand = 0);

	template <typename T>
	inline std::enable_if_t<std::is_pointer<T>::value, T> as()
	{
		return static_cast<T>(m_Ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_lvalue_reference<T>::value, T> as()
	{
		return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_same<T, std::uintptr_t>::value, T> as()
	{
		return reinterpret_cast<T>(m_Ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_pointer<T>::value, T> hook(void* detour, void** og)
	{
		auto func = static_cast<T>(m_Ptr);
		MH_STATUS status = MH_CreateHook(func, detour, og);
		if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(func) != MH_OK)
			return nullptr;
		return func;
	}

	template <typename T>
	inline std::enable_if_t<std::is_lvalue_reference<T>::value, T> hook(void* detour, void** og)
	{
		auto func = *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Ptr);
		MH_STATUS status = MH_CreateHook(func, detour, og);
		if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(func) != MH_OK)
			return nullptr;
		return func;
	}

	template <typename T>
	inline std::enable_if_t<std::is_same<T, std::uintptr_t>::value, T> hook(void* detour, void** og)
	{
		auto func = reinterpret_cast<T>(m_Ptr);
		MH_STATUS status = MH_CreateHook(func, detour, og);
		if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(func) != MH_OK)
			return nullptr;
		return func;
	}
	
	ptr_manage add(int offset);
	ptr_manage sub(int offset);
	ptr_manage rip(int offset = 4);
	ptr_manage call();
	ptr_manage jmp();
	ptr_manage eiweiss(int ei = 4);

	inline operator bool() { return m_Ptr != nullptr; }

private:
	void* m_Ptr;
};

class sModule {
public:
	sModule(HMODULE hMod);
	sModule(std::string name);

	ptr_manage get_begin();
	ptr_manage get_end();
	ptr_manage get_export(std::string proc_name);

private:
	ptr_manage m_begin;
	ptr_manage m_end;
	size_t m_size{};
	std::string m_name{};
};

class find_pattern {
public:
	struct Element
	{
		std::uint8_t m_Data{};
		bool m_Wildcard{};
		Element(uint8_t data, bool wildcard) :
			m_Data(data), m_Wildcard(wildcard)
		{ }
	};

	find_pattern(const char* pattern);
	ptr_manage Scan(sModule region = sModule(nullptr));

private:
	const char* m_pat;
	std::vector<Element> m_Elements;
};

struct pattern_hisnt
{
	std::string m_name;
	find_pattern m_pattern;
	std::function<void(ptr_manage)> m_callback;
	bool m_hooked;

	pattern_hisnt(std::string name, find_pattern pattern, std::function<void(ptr_manage)> callback, bool hook = false);
};

class pattern_batch {
public:
	void add(std::string name, find_pattern pattern, std::function<void(ptr_manage)> callback, bool hook = false);
	void run(std::string moduleName = nullptr, bool silent = false);
	void run(HMODULE hModule, bool silent = false);
private:
	std::vector<pattern_hisnt> m_patterns;
};
