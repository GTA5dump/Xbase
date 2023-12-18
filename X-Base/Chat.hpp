#pragma once
#include "pch.h"

void hk_get_chat_data(void* thisptr, __int64 a2, __int64 a3, char *message, BOOL team);

class Chat
{
public:
	Chat() = default;
	~Chat() = default;

	const char* get_sender_name(__int64 a2, __int64 a3);
	Player get_sender_id(__int64 a2, __int64 a3);
	void chat_hook(const char* message, Player sender);

private:
	std::vector<std::string> m_messages;
	std::vector<std::string> m_senders;
	int m_message_count;
};

inline std::unique_ptr<Chat> g_chat;