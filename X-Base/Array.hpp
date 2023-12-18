#pragma once
#include "pch.h"
template <typename T>
class datArray
{
private:
	T *m_data;
	std::uint16_t m_size;
	std::uint16_t m_capacity;
public:
	T *begin()
	{
		return m_data;
	}

	T *end()
	{
		return m_data + m_size;
	}

	const T *begin() const
	{
		return m_data;
	}

	const T *end() const
	{
		return m_data + m_size;
	}

	const T *data() const
	{
		return m_data;
	}

	std::uint16_t size() const
	{
		return m_size;
	}

	std::uint16_t capacity() const
	{
		return m_capacity;
	}

	T &at(UINT16 index) const
	{
		return m_data[index];
	}

	T &operator[](std::uint16_t index)
	{
		return m_data[index];
	}

	const T &operator[](std::uint16_t index) const
	{
		return m_data[index];
	}
};