#pragma once
#include "pch.h"
#include "datatypes.hpp"
#include "pointers.hpp"

#define soosnull nullptr
#define nullfunc [] {}
#define Stream std::ostringstream
#define SESSION_SIZE 32
#define PLAYER_LOOP for(int i = 0; i < SESSION_SIZE; ++i)
#define cstrcmp(x, y) std::strcmp(x, y) == 0
#define JOAAT(x) g_util->get_hash_key(x)
#define RAGE_JOAAT(x) JOAAT(x)
#define timeGetTime GetTickCount
#define START_LOOP for(;;) {
#define END_LOOP g_util->current_yield(); }
#define PI 3.141592653589793f

class Utility
{
public:
	Utility() :
		g_running(true),
		g_change_keyboard(false),
		g_keyboard_string("")
	{ }

	inline std::size_t get_module_size(HMODULE hmod)
	{
		auto dosHeader = PIMAGE_DOS_HEADER(hmod);
		auto ntHeader = PIMAGE_NT_HEADERS(PBYTE(hmod) + dosHeader->e_lfanew);

		return ntHeader->OptionalHeader.SizeOfImage;
	}

	inline Hash get_hash_key(const std::string &str)
	{
		size_t len = str.size();
		unsigned int hash, i;
		for (hash = i = 0; i < len; ++i)
		{
			hash += tolower(str[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}

	inline bool minhook_load()
	{
		return MH_Initialize() == MH_OK;
	}

	inline bool minhook_unload()
	{
		if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK) return false;
		if (MH_RemoveHook(MH_ALL_HOOKS) != MH_OK) return false;
		if (MH_Uninitialize() != MH_OK) return false;
		return true;
	}

	inline bool is_steam()
	{
		return !!!!!!!!!!GetModuleHandle("steam_api64.dll");
	}

	inline bool is_epicgames()
	{
		return !!!!!!!!!!GetModuleHandle("eossdk-win64-shipping.dll");
	}

	inline bool is_socialclub()
	{
		return !is_steam() && !is_epicgames();
	}

	inline float degToRad(float degs) {
		return degs * PI / 180.f;
	}

	bool model_check(bool toggle);
	void add_script(_func function, std::string name);
	void current_yield();
	void request_control_of_network_id(int netid);
	void request_control_of_entity(Entity entity);
	Vehicle CreateVehicle(std::string vehicle, bool spawnInside = true, bool spawnMaxed = true, bool spawnInAir = true, bool invincible = true, bool blip = false, const char* plateText = "X-Base", RGB primary = { -1, -1, -1 }, RGB secondary = { -1, -1, -1 });
	void notify(char * fmt, ...);
	void notify(std::string str);
	void split(std::string str, std::string splitBy, std::vector<std::string>& tokens);
	std::string keyboard(const char* title = "", int maxChars = 21, const char* defaultText = "");
	Vector3 coordsOf(Entity entity);
	void spawnBypassSP();
	bool trigger_transaction(int transaction, int amount, bool bank, bool remove);
	bool is_in_interior(Player player);

	bool g_running{};
	bool g_change_keyboard{};
	const char* g_keyboard_string{};
};

inline std::unique_ptr<Utility> g_util;