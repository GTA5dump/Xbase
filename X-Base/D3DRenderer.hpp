#pragma once
#include "pch.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "pointers.hpp"
#include "Font.hpp"

static bool dummy = true;

class D3DRenderer
{
public:
	D3DRenderer() = default;
	~D3DRenderer() = default;

	inline void Init(IDXGISwapChain* m_swap, ID3D11Device*  pDevice, ID3D11DeviceContext* context)
	{
		m_SwapChain = m_swap; m_device = pDevice; m_d3d_device_context = context;
		ImGui::CreateContext();
		ImGui_ImplDX11_Init(m_device, m_d3d_device_context);
		ImGui_ImplWin32_Init(FindWindowW(L"grcWindow", nullptr));

		ImFontConfig font_cfg{};
		font_cfg.FontDataOwnedByAtlas = false;
		std::strcpy(font_cfg.Name, "Rubik");

		m_font = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(font_rubik), sizeof(font_rubik), 16.f, &font_cfg);
		m_monospace_font = ImGui::GetIO().Fonts->AddFontDefault();

		setup_imgui_style();
	}

	inline void pre_reset() {
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	inline void post_reset() {
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	inline std::mutex& getMutex() {
		return m_mutex;
	}

	void present();
	void wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void setup_imgui_style();
	void mouse_cursor(bool enable);
	void new_frame();
	void end_frame();
	void load_windows();

	bool m_opened{};
	bool mouse_enabled{};
	bool in_pause_menu{};
	bool never_used{};

	struct Window
	{
		ImVec2 pos;
		ImVec2 size;
		const char* title;
		Function args;
		bool* condition;
		bool init;
		Window(ImVec2 p, ImVec2 s, const char* t, Function a, bool* c) : 
			pos(p), size(s), title(t), args(a), condition(c), init(true)
		{ }
		Window(ImVec2 p, ImVec2 s, const char* t, Function a) : 
			pos(p), size(s), title(t), args(a), init(true)
		{
			condition = &dummy;
		}
		Window(ImVec2 p, ImVec2 s, Function a, bool* c) :
			pos(p), size(s), title(""), args(a), condition(c), init(true)
		{ }
		Window(ImVec2 p, ImVec2 s, Function a) :
			pos(p), size(s), title(""), args(a), init(true)
		{
			condition = &dummy;
		}
	};

	int AddWindow(Window* window);
	int AddWindow(ImVec2 position, ImVec2 size, const char* title, Function args, bool* condition = &dummy);

private:
	IDXGISwapChain* m_SwapChain{};
	ID3D11Device* m_device{};
	ID3D11DeviceContext* m_d3d_device_context{};
	ImFont *m_font{};
	ImFont *m_monospace_font{};
	std::mutex m_mutex;
	std::vector<Window*> m_windows;
	std::vector<Function> m_functions;
	int m_window_count;
};

inline std::unique_ptr<D3DRenderer> g_d3drenderer;