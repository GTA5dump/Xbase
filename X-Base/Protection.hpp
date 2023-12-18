#pragma once
#include "pch.h"

int64_t hk_rid_writer(int64_t rcx, int64_t rdx);
void hk_set_warning_message_2(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);
bool hk_scripted_game_event(__int64 thisptr, __int64 sender, __int64 receiver); 
void hk_received_event(__int64 thisptr, __int64 sender, __int64 receiver, unsigned __int16 eventId, int unk, int eventHash, __int64 bufferSize, __int64 bufferData);

class Protection
{
public:
	Protection() :
		m_protect_error(true),
		m_protect_ceo_kick(true),
		m_protect_kick(true),
		m_protect_weather(false),
		m_protect_weather_crash(true),
		m_protect_rid_crash(true),
		m_protect_freeze(false)
	{ }
	~Protection()
	{ }

	bool m_protect_error{};
	bool m_protect_ceo_kick{};
	bool m_protect_kick{};
	bool m_protect_weather{};
	bool m_protect_weather_crash{};
	bool m_protect_rid_crash{};
	bool m_protect_freeze{};
};

inline std::unique_ptr<Protection> g_protection;