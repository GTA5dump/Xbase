#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

#ifdef DEBUG
#pragma comment(lib, "MinHook-Debug.lib")
#else
#pragma comment(lib, "MinHook-Release.lib")
#endif

#include <Windows.h>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <memory>
#include <psapi.h>
#include <functional>
#include <filesystem>
#include <optional>
#include <thread>
#include <chrono>
#include <mutex>
#include <d3d11.h>
#include <dxgi.h>
#include <fstream>
#include <timeapi.h>
#include <iosfwd>

#include "MinHook/MinHook.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "framework.h"
#include "format.h"
#include "logger.hpp"
#include "hook_helper.hpp"
#include "pattern_scan.hpp"
#include "pointers.hpp"
#include "hooking.hpp"
#include "Array.hpp"
#include "Crossmap.hpp"
#include "datatypes.hpp"
#include "Label.hpp"
#include "SmartPointer.hpp"
#include "Utility.hpp"
#include "Invoker.hpp"
#include "Bitbuffer.hpp"
#include "natives.hpp"
#include "Caller.hpp"
#include "Crossmap.hpp"
#include "Drawing.hpp"
#include "MainScript.hpp"
#include "MenuUI.hpp"
#include "ScriptThread.hpp"
#include "D3DRenderer.hpp"
#include "lists.hpp"
#include "Handle.hpp"
#include "Classes.hpp"
#include "Scripting.hpp"
#include "Integrity.hpp"
#include "Spoofer.hpp"
#include "Protection.hpp"
#include "Chat.hpp"

#endif //PCH_H
