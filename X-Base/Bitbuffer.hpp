#pragma once
#include "pch.h"
#include "pointers.hpp"

class datBitBuffer
{
public:

	inline datBitBuffer(void* data, std::size_t size) {
		m_data = data;
		m_f8 = 0;
		m_maxBit = size * 0x08;
		m_unkBit = 0;
		m_curBit = 0;
		m_unk2Bit = 0;
		m_f1C = 0;
	}

	inline std::uint32_t GetPosition() {
		return m_unkBit;
	}

	inline bool Seek(int bits) {
		if (bits >= 0) {
			std::uint32_t length = (m_f1C & 1) ? m_maxBit : m_curBit;
			if (bits <= length) m_unkBit = bits;
		}
		return false;
	}

	inline std::size_t GetDataLength() {
		char leftoverBit = (m_curBit % 8) ? 1 : 0;
		return (m_curBit / 8) + leftoverBit;
	}

	bool ReadDword(DWORD* dword, int bits);
	bool ReadWord(WORD* word, int bits);

public:
	void* m_data;                              //0x0000
	std::uint32_t m_f8;                        //0x0008
	std::uint32_t m_maxBit;                    //0x000C
	std::uint32_t m_unkBit;                    //0x0010
	std::uint32_t m_curBit;                    //0x0014
	std::uint32_t m_unk2Bit;				   //0x0018
	std::uint8_t m_f1C;                        //0x001C
};