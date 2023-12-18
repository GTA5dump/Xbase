#include "Utility.hpp"
#include "pch.h"

bool Utility::model_check(bool toggle) 
{
	twentyfourBytes patched = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	twentyfourBytes restore = { 0x48, 0x85, 0xC0, 0x0F, 0x84, 0x99, 0x02, 0x00, 0x00, 0x8B, 0x48, 0x50, 0xC1, 0xE9, 0x04, 0xF6, 0xC1, 0x01, 0x0F, 0x84, 0x8A, 0x02, 0x00, 0x00 };
	if (g_pointers->model_check_ptr == soosnull) return false;
	*g_pointers->model_check_ptr = toggle ? patched : restore;
	return true;
}

void Utility::add_script(_func function, std::string name) 
{
	g_scriptThread->add(std::make_unique<game_script>(function, name), name);
}

void Utility::current_yield() 
{
	game_script::get_current_script()->yield(0, false);
}

void Utility::request_control_of_network_id(int netid)
{
	for (int i = 0; i < 32; i++) {
		if (NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid)) break;
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
	}
}

void Utility::request_control_of_entity(Entity entity)
{
	for (int i = 0; i < 25; i++) {
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity)) break;
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int networkId = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		for (int i = 0; i < 32; i++) {
			if (NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(networkId)) break;
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(networkId);
		}
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(networkId, 1);
	}
}

Vehicle Utility::CreateVehicle(std::string vehicle, bool spawnInside, bool spawnMaxed, bool spawnInAir, bool invincible, bool blip, const char* plateText, RGB primary, RGB secondary)
{
	Hash model = RAGE_JOAAT(vehicle);
	if (!STREAMING::IS_MODEL_VALID(model)) return 0;
	STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model)) game_script::get_current_script()->yield();
	Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	float forward = 5.f;
	float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	float xVector = forward * sin(g_util->degToRad(heading)) * -1.f;
	float yVector = forward * cos(g_util->degToRad(heading));
	float zVector = ourCoords.z;
	if (spawnInAir)
		if (g_pointers->is_this_model_a_heli(model) || g_pointers->is_this_model_a_plane(model))
			zVector += 222.0f;
	Vehicle veh = g_pointers->create_vehicle(model, ourCoords, heading, 1, 1);
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(veh, 0);
	g_util->request_control_of_entity(veh);
	VEHICLE::SET_VEHICLE_ENGINE_ON(veh, 1, 1, 1);
	VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 5.0f);
	DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
	auto networkId = NETWORK::VEH_TO_NET(veh);
	ENTITY::_SET_ENTITY_CLEANUP_BY_ENGINE(veh, 1);
	if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, 1);
	if (spawnInside)
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
	if (spawnMaxed)
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		for (int i = 0; i < 50; i++)
			VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, 0);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, plateText);
	}
	if (primary.r != -1 && primary.g != -1 && primary.b != -1)
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, primary.r, primary.g, primary.b);
	if (secondary.r != -1 && secondary.g != -1 && secondary.b != -1)
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, secondary.r, secondary.g, secondary.b);
	if (blip)
	{
		HUD::SET_BLIP_COLOUR(225, 67);
		HUD::SET_BLIP_COORDS(225, coords.x, coords.y, coords.z);
	}
	if (invincible)
		ENTITY::SET_ENTITY_INVINCIBLE(veh, 1);
	game_script::get_current_script()->yield(150);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	return veh;
}

void Utility::notify(char * fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	char buff2[2048] = { 0 };
	sprintf_s(buff2, "%s", buf);
	HUD::SET_TEXT_OUTLINE();
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
	HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(0, 0);
}

void Utility::notify(std::string str)
{ 
	notify(&str[0]); 
}

void Utility::split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
	tokens.push_back(str);
	size_t splitAt;
	size_t splitLen = splitBy.size();
	std::string frag;
	while (true)
	{
		frag = tokens.back();
		splitAt = frag.find(splitBy);
		if (splitAt == std::string::npos) break;
		tokens.back() = frag.substr(0, splitAt);
		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
}

std::string Utility::keyboard(const char* title, int maxChars, const char* defaultText) 
{
	bool failed = false;
	if (strcmp(title, "") == 0) {
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "", "", "", "", "", "", 16);
	}
	else {
		g_change_keyboard = true;
		g_keyboard_string = title;
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "FMMC_KEY_TIP8FS", "", "", "", "", "", 16);
	}
	while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) game_script::get_current_script()->yield();
	if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT()) {
		if (g_change_keyboard) g_change_keyboard = false;
		return "0";
	}
	if (g_change_keyboard) g_change_keyboard = false;
	return MISC::GET_ONSCREEN_KEYBOARD_RESULT();
}

Vector3 Utility::coordsOf(Entity entity) 
{
	return ENTITY::GET_ENTITY_COORDS(entity, 1);
}

void Utility::spawnBypassSP()
{
	bool *value = globalHandle(0x412134).As<bool*>();
	if (!(*value)) *value = true;
}

bool Utility::trigger_transaction(int transaction, int amount, bool bank, bool remove)
{
	bool output[2] = { 0, 0 };
	int transactionId;
	g_scripting->executeInScriptThread(RAGE_JOAAT("shop_controller"), [&] {
		output[0] = NETSHOPPING::NET_GAMESERVER_BEGIN_SERVICE(&transactionId, 0x57DE404E, transaction, remove ? 0x2005D9A9 : 0x562592BB, amount, bank ? 4 : 1);
		output[1] = NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(transactionId);
	});
	return output[0] && output[1];
}

bool Utility::is_in_interior(Player player)
{
	int interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::GET_PLAYER_PED(player));
	if (!interior) interior = *globalHandle(2425662).At(player, 421).At(235).As<int*>();
	return interior != 0;
}