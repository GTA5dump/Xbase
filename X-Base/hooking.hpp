#pragma once
#include "pch.h"

using namespace Hook;

class hooking 
{
public: 
	explicit hooking(HMODULE hmod);
	~hooking();

	HMODULE get_module();
	void mainhook_tick();

	Detour* detour_is_dlc_present;
	Detour* detour_does_cam_exist;
	Detour* detour_get_current_ped_weapon;
	Detour* detour_get_number_of_events;
	Detour* detour_get_label_text;
	Detour* detour_get_networked_script_handler;
	Detour* detour_wndproc;
	Detour* detour_send_net_info_to_session;
	Detour* detour_received_event;
	Detour* detour_scripted_game_event;
	Detour* detour_set_warning_message_2;
	Detour* detour_rid_writer;
	Detour* detour_get_chat_data;
	Detour* detour_set_current_ped_weapon;
	Detour* detour_disable_control_action;

	IAT* iat_ntqueryvirtualmemory;
	IAT* iat_setcursorpos;

	VMT* vmt_swapchain;

private:
	HMODULE ourModule;
	uint64_t last_tick;
};

inline std::unique_ptr<hooking> g_hooking;