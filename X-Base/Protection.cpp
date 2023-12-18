#include "pch.h"
#include "Protection.hpp"

int64_t hk_rid_writer(int64_t rcx, int64_t rdx)
{
	if (g_protection->m_protect_rid_crash) {
		if (!rdx) return g_hooking->detour_rid_writer->get_original<decltype(&hk_rid_writer)>()(rcx, rdx);
		if (*(int64_t*)(rdx + 0x48) == 0)
			*(int64_t*)(rdx + 0x48) = 1337;
	}
	return g_hooking->detour_rid_writer->get_original<decltype(&hk_rid_writer)>()(rcx, rdx);
}

void hk_set_warning_message_2(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background) {
	if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("shop_controller") && g_protection->m_protect_error) return;
	g_hooking->detour_set_warning_message_2->get_original<decltype(&hk_set_warning_message_2)>()(entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, p6, p7, background);
}

bool hk_scripted_game_event(__int64 thisptr, __int64 sender, __int64 receiver)
{
	uint64_t* args = reinterpret_cast<uint64_t*>(thisptr + 0x70);
	uint64_t eventId = args[0];
	int8_t player = *reinterpret_cast<int8_t*>(sender + 0x35);
	uint64_t argCount = *(uint32_t*)(((uintptr_t)thisptr) + 0x224) / sizeof(int64_t);

	if (g_protection->m_protect_ceo_kick && eventId == -1775205375) {
		LOG_INFO("CEO Kick blocked from {}", g_pointers->get_player_name(player));
		return true;
	}

	if (g_protection->m_protect_kick && eventId == -1169499038 && args[2] == 48) {
		LOG_INFO("Kick blocked from {}", g_pointers->get_player_name(player));
		return true;
	}

	//Add more events

	return g_hooking->detour_scripted_game_event->get_original<decltype(&hk_scripted_game_event)>()(thisptr, sender, receiver);
}

void hk_received_event(__int64 thisptr, __int64 sender, __int64 receiver, unsigned __int16 eventId, int unk, int eventHash, __int64 bufferSize, __int64 bufferData)
{
	datBitBuffer* buffer = new datBitBuffer((void*)bufferData, (size_t)bufferSize);
	int8_t player = *reinterpret_cast<int8_t*>(sender + 0x35);
	uint8_t eventCount = *reinterpret_cast<uint8_t*>(g_pointers->event_struct + 3);
	auto eventName = reinterpret_cast<char*>(*reinterpret_cast<__int64*>(thisptr + 8 * eventId + *reinterpret_cast<int*>(g_pointers->event_struct + 0x15)));
	DWORD weather1{}, weather2{}, weatherResult{};
	switch (eventId) {
	case GAME_WEATHER_EVENT:
		buffer->ReadDword(&weather1, 1);
		buffer->ReadDword(&weatherResult, 5);
		if (!weather1)
			buffer->ReadDword(&weather2, 9);
		if (g_protection->m_protect_weather) {
			LOG_INFO("Weather Change blocked: Id {}", weatherResult);
			buffer->Seek(0);
			return;
		}
		else if (g_protection->m_protect_weather_crash && (weatherResult < 0 || weatherResult > 14)) {
			LOG_INFO("Weather Crash blocked");
			buffer->Seek(0);
			return;
		}
		break;
	case NETWORK_CLEAR_PED_TASKS_EVENT:
		if (g_protection->m_protect_freeze) {
			LOG_INFO("Freeze blocked from {}", g_pointers->get_player_name(player));
			buffer->Seek(0);
			return;
		}
		break;
	//Add more events
	}

	buffer->Seek(0);
	g_hooking->detour_received_event->get_original<decltype(&hk_received_event)>()(thisptr, sender, receiver, eventId, unk, eventHash, bufferSize, bufferData);
}