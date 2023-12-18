#pragma once
#include "pch.h"

void MenuScript();
extern Player selectedPlayer;
extern bool weaponsInInterior;

namespace submenus
{
	void MainMenu();
	void PlayerlistMenu();
	void SelectedPlayerMenu();
	void ProtectionMenu();
	void SelfMenu();
	void VehicleMenu();
	void WeaponMenu();
	void SettingsMenu();
}