#pragma once
#include "pch.h"

class integrityCheck
{
private:
	char* m_function;
	std::vector<BYTE> m_bytes;
public:
	integrityCheck(Any function, std::vector<BYTE> bytes)
		: m_function(getSignature(function)), m_bytes(bytes)
	{ }

	char* getSignature(Any function)
	{
		return (char*)function;
	}

	bool checkByte(int id)
	{
		if (m_bytes[id] == 0x00) return true;
		return m_bytes[id] == m_function[id];
	}

	bool check()
	{
		for (int i = 0; i < m_bytes.size(); i++)
			if (!checkByte(i))
				return false;
		return true;
	}
};