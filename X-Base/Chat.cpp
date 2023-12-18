#include "pch.h"

void hk_get_chat_data(void* thisptr, __int64 a2, __int64 a3, char *message, BOOL team)
{
	g_chat->chat_hook(message, g_chat->get_sender_id(a3, a2));
	g_hooking->detour_get_chat_data->get_original<decltype(&hk_get_chat_data)>()(thisptr, a2, a3, message, team);
}

const char* Chat::get_sender_name(__int64 a2, __int64 a3)
{
	return g_pointers->get_chat_sender(a2, a3, a2)->get_name();
}

Player Chat::get_sender_id(__int64 a2, __int64 a3)
{
	const char* name = get_sender_name(a2, a3);
	for (int i = 0; i < 32; ++i) {
		if (cstrcmp(name, g_pointers->get_player_name(i)))
			return i;
	}
	return 0;
}

void Chat::chat_hook(const char* message, Player sender)
{
	std::vector<std::string> words;
	std::string sName = g_pointers->get_player_name(sender);
	m_messages.push_back(sName + ": " + message);
	m_senders.push_back(sName);
	m_message_count++;
	g_util->split(message, " ", words);
	//Add Chat Commands or something here
}