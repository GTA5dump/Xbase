#pragma once
#include "pch.h"

class Spoofer
{
public:
	Spoofer() = default;
	~Spoofer() = default;

	bool m_rid_spoof_ever_used{};
	bool m_name_spoof_ever_used{};
	bool m_ip_spoof_ever_used{};
	bool m_level_spoof_ever_used{};

	bool m_enable_rid_spoof{};
	bool m_enable_name_spoof{};
	bool m_enable_ip_spoof{};
	bool m_enable_level_spoof{};

	uint64_t m_rid_to_spoof{};
	std::string m_name_to_spoof{};
	uint8_t m_ip_to_spoof[4]{};
	int m_level_to_spoof{};

	uint64_t m_old_rid{};
	std::string m_old_name{};
	uint8_t m_old_ip[4]{};
	int m_old_level{};

	void loop();

	void spoof_rid(uint64_t rid, bool toggle);
	void spoof_name(std::string name, bool toggle);
	void spoof_ip(uint8_t one, uint8_t two, uint8_t three, uint8_t four, bool toggle);
	void spoof_level(int level, bool toggle);
};

inline std::unique_ptr<Spoofer> g_spoofer;

bool hk_send_net_info_to_session(__int64 localPlayer, __int64 a2, __int64 a3, DWORD* a4);