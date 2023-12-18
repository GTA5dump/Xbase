#include "pch.h"
#include "MenuUI.hpp"

bool godmode = false;
bool neverWanted = false;
bool superJump = false;
bool invisibility = false;
bool tpGun = false;
bool exploGun = false;
bool weaponsInInterior = false;

int alpha = 255;

int framelogoheader = 0;
bool reverse = false;

Player selectedPlayer;

bool freezed[32] = { 0 };

void neverwanted(bool toggle) {
	PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
	PLAYER::SET_MAX_WANTED_LEVEL(toggle ? 0 : 5);
	MISC::SET_FAKE_WANTED_LEVEL(0);
	PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), toggle);
}

void invisible(bool toggle) {
	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !toggle, 0);
}

void superjump() {
	MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
}

void freeze(Player player) {
	Ped ped = PLAYER::GET_PLAYER_PED(player);
	TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
	TASK::CLEAR_PED_TASKS(ped);
	TASK::CLEAR_PED_SECONDARY_TASK(ped);
}

void explosionGun() {
	Vector3 c;
	if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &c)) {
		FIRE::ADD_EXPLOSION(c.x, c.y, c.z, 1, 5.0f, 1, 0, 0.3f, 0);
	}
}

void teleportGun() {
	Vector3 c;
	if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &c)) {
		PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z);
	}
}

void MainLoop() 
{
	g_spoofer->loop();

	if (neverWanted)
		neverwanted(1);
	if (superJump)
		superjump();
	if (invisibility)
		invisible(1);
	if (exploGun)
		explosionGun();
	if (tpGun)
		teleportGun();
	for (int i = 0; i < 32; ++i) {
		if (freezed[i])
			freeze(i);
	}
}

void submenus::SelectedPlayerMenu()
{
	g_ui->Option("Teleport to Player", "Teleport to the Player", [] {
		Vector3 c = g_util->coordsOf(PLAYER::GET_PLAYER_PED(selectedPlayer));
		PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), c.x, c.y, c.z);
	});
	g_ui->BoolOption("Freeze", &freezed[selectedPlayer]);
	g_ui->Option("Explode", [] {
		Vector3 c = g_util->coordsOf(PLAYER::GET_PLAYER_PED(selectedPlayer));
		FIRE::ADD_EXPLOSION(c.x, c.y, c.z, 0, 5.0f, 1, 0, 0.3f, 0);
	});
	g_ui->Option("CEO Kick", [] {
		uint64_t args[4] = { -1775205375, PLAYER::GET_PLAYER_PED(selectedPlayer), 0, 0 };
		g_pointers->trigger_script_event(1, args, 4, 1 << selectedPlayer);
	});
	g_ui->Option("Kick", "Kick dat Nibba", [] {
		uint64_t args[3] = { -1169499038, PLAYER::GET_PLAYER_PED(selectedPlayer), 48 };
		g_pointers->trigger_script_event(1, args, 3, 1 << selectedPlayer);
	});
}

void submenus::PlayerlistMenu()
{
	for (int i = 0; i < 32; ++i) {
		if (!ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(i))) continue;
		g_ui->SubOption(g_pointers->get_player_name(i), &SelectedPlayerMenu, g_pointers->get_player_name(selectedPlayer), [&] { selectedPlayer = i; });
	}
}

void submenus::ProtectionMenu()
{
	g_ui->BoolOption("Kick", &g_protection->m_protect_kick);
	g_ui->BoolOption("CEO Kick", &g_protection->m_protect_ceo_kick);
	g_ui->BoolOption("Freeze", &g_protection->m_protect_freeze);
	g_ui->BoolOption("Weather", &g_protection->m_protect_weather);
	g_ui->BoolOption("Weather Crash", &g_protection->m_protect_weather_crash);
	g_ui->BoolOption("Rockstar Id Crash", &g_protection->m_protect_rid_crash);
	g_ui->BoolOption("Transaction Error", &g_protection->m_protect_error);
}

void submenus::SelfMenu()
{
	g_ui->BoolOption("Godmode", &godmode, [] { PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), godmode); });
	g_ui->BoolOption("Never Wanted", &neverWanted, [] { neverwanted(neverWanted); });
	g_ui->Option("Clear Wanted Level", [] {
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
	});
	g_ui->IntOption("Alpha", &alpha, 0, 255, 1, [] { ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), alpha, 0); });
	g_ui->BoolOption("Super Jump", &superJump);
	g_ui->BoolOption("Invisibility", &invisibility, [] { invisible(invisibility); });
}

void submenus::VehicleMenu()
{
	g_ui->Option("Spawn Vehicle", [] {
		std::string veh = g_util->keyboard("Enter Vehicle");
		g_util->CreateVehicle(veh);
	});
	g_ui->Option("Spawn Adder", [] {
		g_util->CreateVehicle("adder");
	});
	g_ui->Option("Vehicle Godmode", [] {
		ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 1);
	});
}

void submenus::WeaponMenu()
{
	g_ui->BoolOption("Teleport Gun", &tpGun);
	g_ui->BoolOption("Explosion Gun", &exploGun);
	g_ui->BoolOption("Weapons in Interior", &weaponsInInterior);
}

void submenus::SettingsMenu()
{
	g_ui->BoolOption("Enable Info Box", &g_ui->infoBoxEnabled);
	g_ui->IntOption("Options per Page", &g_ui->maxVisOptions, 1, 30);
	g_ui->BoolOption("Mouse", &g_d3drenderer->mouse_enabled, [] { g_cursor->m_enabled = g_d3drenderer->mouse_enabled; });
	g_ui->BoolOption("DirectX Window", &g_d3drenderer->m_opened);
	//g_ui->Option("Unload", "Unload the Menu", [] {
	//	g_Running = false;
	//	});
}

void submenus::MainMenu()
{
	g_ui->SubOption("Protection", &ProtectionMenu, "This is a nice Info", "Protection");
	g_ui->SubOption("Self", &SelfMenu, "This is a nice Info", "Self");
	g_ui->SubOption("Network", &PlayerlistMenu, "This is a nice Info", "Online Players");
	g_ui->SubOption("Vehicle", &VehicleMenu, "This is a nice Info", "Vehicle");
	g_ui->SubOption("Weapon", &WeaponMenu, "This is a nice Info", "Weapon");
	g_ui->SubOption("Settings", &SettingsMenu, "This is a nice Info", "Settings");
}

void Headerchanger()
{
	static int timer;

	if ((GetTickCount() - timer) > 0.005)
	{
		if (!reverse)
			framelogoheader++;
		else
			framelogoheader--;
		timer = GetTickCount();
	}

	if (framelogoheader == 170)
		reverse = true;
	if (framelogoheader == 0)
		reverse = false;
}

void MenuScript()
{
	START_LOOP
		g_cursor->tick();
		g_ui->controller();
		g_ui->setOptionCount(0);
		if (g_ui->isMenuOpen()) {/*
			g_ui->Header(g_ui->getMenuTitle());*/
			g_ui->Header("Gravity", "C:\\Gravity\\gravity.ytd", "Gravity", "LogoHeader", framelogoheader, true);
			g_ui->SubBanner(g_ui->getSubTitle());
			g_ui->disableControls();
			if (g_ui->getCurrentMenu() != nullptr)
				g_ui->getCurrentMenu()();
			g_ui->Bar("commonmenu", "shop_arrows_upanddown", "arrowleft", "arrowright");
		}
		MainLoop();
		g_callbackThread->tickNative();
		g_d3drenderer->in_pause_menu = HUD::IS_PAUSE_MENU_ACTIVE();
	END_LOOP
}