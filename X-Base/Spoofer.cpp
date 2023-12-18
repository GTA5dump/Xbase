#include "pch.h"
#include "Spoofer.hpp"

bool hk_send_net_info_to_session(__int64 localPlayer, __int64 a2, __int64 a3, DWORD* a4)
{
	if (g_spoofer->m_enable_name_spoof) {
		auto len = min((g_spoofer->m_name_to_spoof).size(), (std::size_t)18);
		strncpy(g_pointers->get_player_name(PLAYER::PLAYER_ID()), &(g_spoofer->m_name_to_spoof)[0], (g_spoofer->m_name_to_spoof).size() + 1);
		std::memcpy((char*)(localPlayer + 0x64), (g_spoofer->m_name_to_spoof).data(), len);
		((char*)(localPlayer + 0x64))[len] = '\0';
	}
	else if (g_spoofer->m_name_spoof_ever_used) {
		auto len = min((g_spoofer->m_old_name).size(), (std::size_t)18);
		strncpy(g_pointers->get_player_name(PLAYER::PLAYER_ID()), &(g_spoofer->m_old_name)[0], (g_spoofer->m_old_name).size() + 1);
		std::memcpy((char*)(localPlayer + 0x64), (g_spoofer->m_old_name).data(), len);
		((char*)(localPlayer + 0x64))[len] = '\0';
		g_spoofer->m_name_spoof_ever_used = false;
	}
	if (g_spoofer->m_enable_rid_spoof) {
		*(uint64_t*)(localPlayer + 0x50) = g_spoofer->m_rid_to_spoof;
	}
	else if (g_spoofer->m_rid_spoof_ever_used) {
		*(uint64_t*)(localPlayer + 0x50) = g_spoofer->m_old_rid;
		g_spoofer->m_rid_spoof_ever_used = false;
	}
	if (g_spoofer->m_enable_ip_spoof) {
		if (!(g_spoofer->m_ip_spoof_ever_used)) {
			g_spoofer->m_old_ip[0] = (*(netAddress*)(localPlayer + 0x24)).m_field1;
			g_spoofer->m_old_ip[1] = (*(netAddress*)(localPlayer + 0x24)).m_field2;
			g_spoofer->m_old_ip[2] = (*(netAddress*)(localPlayer + 0x24)).m_field3;
			g_spoofer->m_old_ip[3] = (*(netAddress*)(localPlayer + 0x24)).m_field4;
			g_spoofer->m_ip_spoof_ever_used = true;
		}
		(*(netAddress*)(localPlayer + 0x24)).m_field1 = g_spoofer->m_ip_to_spoof[0];
		(*(netAddress*)(localPlayer + 0x24)).m_field2 = g_spoofer->m_ip_to_spoof[1];
		(*(netAddress*)(localPlayer + 0x24)).m_field3 = g_spoofer->m_ip_to_spoof[2];
		(*(netAddress*)(localPlayer + 0x24)).m_field4 = g_spoofer->m_ip_to_spoof[3];
	}
	else if (g_spoofer->m_ip_spoof_ever_used) {
		(*(netAddress*)(localPlayer + 0x24)).m_field1 = g_spoofer->m_old_ip[0];
		(*(netAddress*)(localPlayer + 0x24)).m_field2 = g_spoofer->m_old_ip[1];
		(*(netAddress*)(localPlayer + 0x24)).m_field3 = g_spoofer->m_old_ip[2];
		(*(netAddress*)(localPlayer + 0x24)).m_field4 = g_spoofer->m_old_ip[3];
		g_spoofer->m_ip_spoof_ever_used = false;
	}
	return g_hooking->detour_send_net_info_to_session->get_original<decltype(&hk_send_net_info_to_session)>()(localPlayer, a2, a3, a4);
}

void Spoofer::loop()
{
	if (m_level_spoof_ever_used && m_level_to_spoof)
		*StatBase(PLAYER::PLAYER_ID()).At(6).As<int*>() = m_level_to_spoof;
}

void Spoofer::spoof_rid(uint64_t rid, bool toggle)
{
	if (!m_rid_spoof_ever_used && toggle) {
		int handle[13];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::PLAYER_ID(), &handle[0], 13);
		m_old_rid = std::stoi(NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&handle[0]));
		m_rid_spoof_ever_used = true;
	}
	m_rid_to_spoof = rid;
	m_enable_rid_spoof = toggle;
}

void Spoofer::spoof_name(std::string name, bool toggle)
{
	if (!m_name_spoof_ever_used && toggle) {
		m_old_name = g_pointers->get_player_name(PLAYER::PLAYER_ID());
		m_name_spoof_ever_used = true;
	}
	m_name_to_spoof = name;
	m_enable_name_spoof = toggle;
}

void Spoofer::spoof_ip(uint8_t one, uint8_t two, uint8_t three, uint8_t four, bool toggle)
{
	m_ip_to_spoof[0] = one;
	m_ip_to_spoof[1] = two;
	m_ip_to_spoof[2] = three;
	m_ip_to_spoof[3] = four;
	m_enable_ip_spoof = toggle;
}

void Spoofer::spoof_level(int level, bool toggle)
{
	if (!m_level_spoof_ever_used && toggle) {
		m_old_level = *StatBase(PLAYER::PLAYER_ID()).At(6).As<int*>();
		m_level_spoof_ever_used = true;
	}
	m_level_to_spoof = level;
	m_enable_level_spoof = toggle;
}