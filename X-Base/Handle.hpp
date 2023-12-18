#pragma once
#include "pch.h"
#include "pointers.hpp"
#include "Classes.hpp"
#include <xtr1common>

class localHandle
{
private:
	int m_index;
	PVOID m_stack;

public:
	localHandle(scrThread* thread, int index)
		: m_stack(thread->m_stack), m_index(index)
	{ }

	localHandle(PVOID stack, int index)
		: m_stack(stack), m_index(index)
	{ }

	localHandle(const localHandle& copy)
		: m_stack(copy.m_stack), m_index(copy.m_index)
	{ }

	localHandle At(int index)
	{
		return localHandle(m_stack, m_index + index);
	}

	localHandle At(int index, int size)
	{
		return localHandle(m_stack, m_index + 1 + (index * size));
	}

	template <typename T>
	T* Get()
	{
		return reinterpret_cast<T*>((T)m_stack + (m_index * sizeof(T)));
	}

	template <typename T>
	std::enable_if_t<std::is_pointer<T>::value, T> As()
	{
		return static_cast<T>(Get());
	}

	template <typename T>
	std::enable_if_t<std::is_lvalue_reference<T>::value, T> As()
	{
		return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(Get());
	}
};

class globalHandle
{
private:
	PVOID m_index;

public:
	globalHandle(int index)
		: m_index(&(g_pointers->m_globalBase)[index >> 0x12 & 0x3F][index & 0x3FFFF])
	{ }

	globalHandle(void* p)
		: m_index(p)
	{ }

	globalHandle(const globalHandle& copy)
		: m_index(copy.m_index)
	{ }

	globalHandle At(int index)
	{
		return globalHandle(reinterpret_cast<PVOID*>(m_index) + (index));
	}

	globalHandle At(int index, int size)
	{
		return At(1 + (index * size));
	}

	template <typename T>
	T* Get()
	{
		return reinterpret_cast<T*>(m_index);
	}

	template <typename T>
	T& As()
	{
		return *Get<T>();
	}
};

inline globalHandle StatBase(Player player) {
	return globalHandle(0x184507 + 1 + player * 0x36C + 0xD3);
}

inline globalHandle TunableBase() {
	return globalHandle(0x40001);
}