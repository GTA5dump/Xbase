#include "pch.h"
#include "MenuUI.hpp"

std::string menu_version = "1.0.0";
std::once_flag m_main_flag;
HMODULE dll;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	dll = hModule;
	switch (ul_reason_for_call)
	{
	case DLL_THREAD_ATTACH:
		std::call_once(m_main_flag, [&] {
			DisableThreadLibraryCalls(hModule);
			CreateThread(nullptr, 0, [](LPVOID)->DWORD
			{
				g_logger = std::make_unique<Log>();

				g_util->minhook_load();

				LOG_INFO("Menu Initialized");
				LOG_INFO("Menu Version: {}", menu_version);

				g_pointers = std::make_unique<pointers>();
				g_util = std::make_unique<Utility>();
				g_label = std::make_unique<LabelEditor>();
				g_invoker = std::make_unique<Invoker>();
				g_scriptThread = std::make_unique<script_manager>();
				g_ui = std::make_unique<gui>();
				g_drawing = std::make_unique<Drawing>();
				g_d3drenderer = std::make_unique<D3DRenderer>();
				g_cursor = std::make_unique<Cursor>();
				g_scripting = std::make_unique<Scripting>();
				g_spoofer = std::make_unique<Spoofer>();
				g_callbackThread = std::make_unique<CallbackThread>();
				g_protection = std::make_unique<Protection>();
				g_chat = std::make_unique<Chat>();

				g_util->add_script(&MenuScript, "Menu");

				g_d3drenderer->load_windows();
				LOG_INFO("Loaded DirectX Windows");

				if (g_util->model_check(true))
					LOG_INFO("Patched ModelCheck");

				g_label->setLabel("HUD_TRANSP", "Pocakking: Very good!");
				g_label->setLabel("HUD_LOADING", "Pocakking: Very good!");
				LOG_INFO("Changed Text Labels");

				LOG_INFO("Waiting for GTAV");
				while (*(g_pointers->m_gameState) != GameStatePlaying)
					Sleep(69);
				LOG_INFO("GTAV loaded");

				LOG_INFO("Initializing Hooks");
				g_hooking = std::make_unique<hooking>(dll);
				LOG_INFO("Hooks initialized");

				while (g_util->g_running) {
					if (GetAsyncKeyState(VK_F10) & 0x1) g_util->g_running = false;
					std::this_thread::sleep_for(std::chrono::seconds(1));
					std::this_thread::yield();
				}

				std::this_thread::yield();
				LOG_INFO("Unloading Menu");

				if (g_util->model_check(false))
					LOG_INFO("Restored ModelCheck");

				g_hooking->iat_ntqueryvirtualmemory->unhook();
				g_hooking->iat_setcursorpos->unhook();
				g_hooking->vmt_swapchain->disable();
				g_hooking->vmt_swapchain->unhook(8);
				g_hooking->vmt_swapchain->unhook(13);
				g_util->minhook_unload();
				LOG_INFO("Hooks Unloaded");

				g_scriptThread->remove_all();
				LOG_INFO("Removed All Scripts");

				g_pointers.reset();
				g_drawing.reset();
				g_ui.reset();
				g_util.reset();
				g_cursor.reset();
				g_label.reset();
				g_invoker.reset();
				g_scripting.reset();
				g_scriptThread.reset();
				g_spoofer.reset();
				g_callbackThread.reset();
				g_protection.reset();
				g_chat.reset();
				LOG_INFO("Deleted Pointers");

				g_hooking.reset();
				LOG_INFO("Hooking Class Removed");
				g_d3drenderer.reset();
				LOG_INFO("DirectX Class Removed");

				LOG_INFO("Menu Unloaded");
				g_logger.reset();				

				FreeLibraryAndExitThread(dll, TRUE);
				return 0;
			}, nullptr, 0, nullptr);
		});
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

