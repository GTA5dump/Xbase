#include "pch.h"

bool hk_is_dlc_present(Hash dlchash)
{
	g_hooking->mainhook_tick();
	return g_hooking->detour_is_dlc_present->get_original<decltype(&hk_is_dlc_present)>()(dlchash);
}

bool hk_does_cam_exist(Cam cam)
{
	g_hooking->mainhook_tick();
	return g_hooking->detour_does_cam_exist->get_original<decltype(&hk_does_cam_exist)>()(cam);
}

int hk_get_number_of_events(int unk)
{
	g_hooking->mainhook_tick();
	return g_hooking->detour_get_number_of_events->get_original<decltype(&hk_get_number_of_events)>()(unk);
}

bool hk_get_current_ped_weapon(Ped ped, DWORD* hash, bool unk)
{
	g_hooking->mainhook_tick();
	return g_hooking->detour_get_current_ped_weapon->get_original<decltype(&hk_get_current_ped_weapon)>()(ped, hash, unk);
}

const char* hk_get_label_text(void* thisptr, const char* label)
{
	for (int i = 0; i < g_label->get_vector().size(); i++)
		if (cstrcmp(label, g_label->get_vector()[i].label_))
			return g_label->get_vector()[i].text;
	if (cstrcmp(label, "FMMC_KEY_TIP8FS") && g_util->g_change_keyboard) return g_util->g_keyboard_string;
	return g_hooking->detour_get_label_text->get_original<decltype(&hk_get_label_text)>()(thisptr, label);
}

void* hk_get_networked_script_handler()
{
	return g_pointers->get_script_handler();
}

int hk_ntqueryvirtualmemory(HANDLE ProcessHandle, PVOID BaseAddress, int MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength)
{
	uintptr_t _module = uintptr_t(g_hooking->get_module());
	uintptr_t _module_end = _module + g_util->get_module_size(g_hooking->get_module());
	if (MemoryInformationClass == 0 && ProcessHandle == GetCurrentProcess() && uintptr_t(BaseAddress) >= _module && uintptr_t(BaseAddress) <= _module_end)
		return STATUS_INVALID_PARAMETER;
	return g_hooking->iat_ntqueryvirtualmemory->get_original<decltype(&hk_ntqueryvirtualmemory)>()(ProcessHandle, BaseAddress, MemoryInformationClass, MemoryInformation, MemoryInformationLength, ReturnLength);
}

HRESULT hk_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	g_d3drenderer->wndproc(hwnd, uMsg, wParam, lParam);
	return g_hooking->detour_wndproc->get_original<decltype(&hk_wndproc)>()(hwnd, uMsg, wParam, lParam);
}

bool hk_set_cursor_pos(int x, int y)
{
	if (g_d3drenderer->mouse_enabled)
		return true;
	return g_hooking->iat_setcursorpos->get_original<decltype(&hk_set_cursor_pos)>()(x, y);
}

std::once_flag m_present_flag;
HRESULT hk_swapchain_present(IDXGISwapChain *pSwap, UINT sync_interval, UINT flags)
{
	std::call_once(m_present_flag, [&] {
		void* m_device{};
		ID3D11DeviceContext* m_d3d_device_context{};
		pSwap->GetDevice(__uuidof(ID3D11Device), &m_device);
		ID3D11Device* m_device_real = (ID3D11Device*)m_device;
		m_device_real->GetImmediateContext(&m_d3d_device_context);
		g_d3drenderer->Init(pSwap, m_device_real, m_d3d_device_context);
	});
	g_d3drenderer->present();
	return g_hooking->vmt_swapchain->get_original<decltype(&hk_swapchain_present)>(8)(pSwap, sync_interval, flags);
}

HRESULT hk_swapchain_resize_buffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
{
	g_d3drenderer->pre_reset();
	auto result = g_hooking->vmt_swapchain->get_original<decltype(&hk_swapchain_resize_buffers)>(13)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	if (SUCCEEDED(result)) {
		g_d3drenderer->post_reset();
		return result;
	}
	return g_hooking->vmt_swapchain->get_original<decltype(&hk_swapchain_resize_buffers)>(13)(dis, bufferCount, width, height, newFormat, swapChainFlags);
}

void hk_disable_control_action(int padIndex, int control, bool disable)
{
	if (weaponsInInterior && g_util->is_in_interior(PLAYER::PLAYER_ID())) return;
	g_hooking->detour_disable_control_action->get_original<decltype(&hk_disable_control_action)>()(padIndex, control, disable);
}

void hk_set_current_ped_weapon(Ped ped, Hash weapon, bool equipNow)
{
	if (weaponsInInterior && g_util->is_in_interior(PLAYER::PLAYER_ID())) return;
	g_hooking->detour_set_current_ped_weapon->get_original<decltype(&hk_set_current_ped_weapon)>()(ped, weapon, equipNow);
}


hooking::hooking(HMODULE hmod)
{
	last_tick = 0;
	ourModule = hmod;
	if (g_pointers->is_dlc_present != soosnull) {
		detour_is_dlc_present = new Detour(g_pointers->is_dlc_present, hk_is_dlc_present, "IDP");
	}
	else if (g_pointers->does_cam_exist != soosnull) {
		detour_does_cam_exist = new Detour(g_pointers->does_cam_exist, hk_does_cam_exist, "DCE");
	}
	else if (g_pointers->get_number_of_events != soosnull) {
		detour_get_number_of_events = new Detour(g_pointers->get_number_of_events, hk_get_number_of_events, "GNOE");
	}
	else if (g_pointers->get_current_ped_weapon != soosnull) {
		detour_get_current_ped_weapon = new Detour(g_pointers->get_current_ped_weapon, hk_get_current_ped_weapon, "GCPW");
	}
	else LOG_INFO("Failed to create Main Hook");

	detour_get_label_text = new Detour(g_pointers->get_label_text, hk_get_label_text, "GLT");
	detour_get_networked_script_handler = new Detour(g_pointers->get_networked_script_handler, hk_get_networked_script_handler, "GNSH");
	detour_send_net_info_to_session = new Detour(g_pointers->send_net_info_to_session, hk_send_net_info_to_session, "SNITS");
	detour_rid_writer = new Detour(g_pointers->rid_writer, hk_rid_writer, "RWR");
	detour_scripted_game_event = new Detour(g_pointers->scripted_game_event, hk_scripted_game_event, "SGE");
	detour_received_event = new Detour(g_pointers->received_event, hk_received_event, "RCE");
	detour_set_warning_message_2 = new Detour(g_pointers->set_warning_message_2, hk_set_warning_message_2, "SWM");
	detour_get_chat_data = new Detour(g_pointers->get_chat_data, hk_get_chat_data, "GCD");
	detour_set_current_ped_weapon = new Detour(g_pointers->set_current_ped_weapon, hk_set_current_ped_weapon, "SCPW");
	detour_disable_control_action = new Detour(g_pointers->disable_control_action, hk_disable_control_action, "DCA");
	detour_wndproc = new Detour(g_pointers->m_wndproc, hk_wndproc, "WPC");
	iat_ntqueryvirtualmemory = new IAT("ntdll.dll", "NtQueryVirtualMemory", (BYTE*)&hk_ntqueryvirtualmemory);
	iat_setcursorpos = new IAT("user32.dll", "SetCursorPos", (BYTE*)&hk_set_cursor_pos);
	vmt_swapchain = new VMT(*g_pointers->swap_chain, 19, "SWCH");
	vmt_swapchain->hook(8, &hk_swapchain_present);
	vmt_swapchain->hook(13, &hk_swapchain_resize_buffers);

	Sleep(5000);

	MH_EnableHook(MH_ALL_HOOKS);
	iat_ntqueryvirtualmemory->enable();
	iat_setcursorpos->enable();
	vmt_swapchain->enable();
}

hooking::~hooking() {

}

HMODULE hooking::get_module() {
	return ourModule;
}

void hooking::mainhook_tick() {
	if (last_tick != g_pointers->get_frame_count()) {
		last_tick = g_pointers->get_frame_count();
		g_scriptThread->tick();
	}
}