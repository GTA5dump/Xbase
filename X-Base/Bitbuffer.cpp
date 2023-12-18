#include "pch.h"

bool datBitBuffer::ReadDword(DWORD* dword, int bits) {
	return g_pointers->read_bitbuffer_dword(this, dword, bits);
}

bool datBitBuffer::ReadWord(WORD* word, int bits) {
	return g_pointers->read_bitbuffer_word(this, word, bits);
}