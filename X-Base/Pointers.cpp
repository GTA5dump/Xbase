#include "pch.h"

pointers::pointers() {

	pattern_batch m_pattern;
	LOG_INFO("Running Pattern Scanner");

	m_pattern.add("IDP", "48 89 5C 24 ? 57 48 83 EC 20 81 F9", [this](ptr_manage ptr) {
		is_dlc_present = ptr.as<fpIsDlcPresent>();
	});
	m_pattern.add("DCE", "40 53 48 83 EC 20 33 DB 85 C9 78 10", [this](ptr_manage ptr) {
		does_cam_exist = ptr.as<fpDoesCamExist>();
	});
	m_pattern.add("GNOE", "48 83 EC 28 33 D2 85 C9", [this](ptr_manage ptr) {
		get_number_of_events = ptr.as<fpGetNumberOfEvents>();
	});
	m_pattern.add("GCPW", "40 53 48 83 EC 20 48 8B DA E8 ? ? ? ? 33 C9", [this](ptr_manage ptr) {
		get_current_ped_weapon = ptr.as<fpGetCurrentPedWeapon>();
	});
	m_pattern.add("RST", "45 33 F6 8B E9 85 C9 B8", [this](ptr_manage ptr) {
		run_script_thread = ptr.sub(0x1F).as<fpRunScriptThread>();
	});	
	m_pattern.add("GLT", "48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8", [this](ptr_manage ptr) {
		get_label_text = ptr.as<fpGetLabelText>();
	});
	m_pattern.add("SWPCH", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](ptr_manage ptr) {
		swap_chain = ptr.add(3).rip().as<IDXGISwapChain**>();
	});
	m_pattern.add("WPC", "48 8B 0D ? ? ? ? 48 8D 55 EF FF 15", [this](ptr_manage ptr) {
		m_wndproc = ptr.sub(0x355).as<fpWndproc>();
	});
	m_pattern.add("NRT", "76 32 48 8B 53 40 48 8D 0D", [this](ptr_manage ptr) {
		m_registrationTable = ptr.add(9).rip().as<NativeRegistrationNew**>();
	});
	m_pattern.add("SVR", "83 79 18 00 48 8B D1 74 4A FF 4A 18", [this](ptr_manage ptr) {
		set_vector_results = ptr.as<fpSetVectorResults>();
	});
	m_pattern.add("GNSH", "40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 12 48 8B 10 48 8B C8", [this](ptr_manage ptr) {
		get_networked_script_handler = ptr.as<fpSetThisScriptIsNetworkScript>();
	});
	m_pattern.add("GSH", "48 83 EC 28 E8 ? ? ? ? 33 C9 48 85 C0 74 0C E8 ? ? ? ? 48 8B 88", [this](ptr_manage ptr) {
		get_script_handler = ptr.as<fpSetThisScriptIsNetworkScript>();
	});
	m_pattern.add("JRBX", "FF 23", [this](ptr_manage ptr) {
		jmp_rbx = ptr.as<void*>();
	});
	m_pattern.add("JRDI", "FF 27", [this](ptr_manage ptr) {
		jmp_rdi = ptr.as<void*>();
	});
	m_pattern.add("TSE", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9", [this](ptr_manage ptr) {
		trigger_script_event = ptr.as<fpTriggerScriptEvent>();
	});
	m_pattern.add("FR", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9", [this](ptr_manage ptr) {
		file_register = ptr.as<fpFileRegister>();
	});
	m_pattern.add("FRC", "03 05 ? ? ? ? 89 81 ? ? ? ? E9", [this](ptr_manage ptr) {
		m_frame_count = ptr.add(2).rip().as<uint64_t*>();
	});
	m_pattern.add("GLHN", "4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0", [this](ptr_manage ptr) {
		m_globalBase = ptr.add(7).rip().as<uint64_t**>();
	});
	m_pattern.add("GPN", "40 53 48 83 EC 20 80 3D ? ? ? ? ? 8B D9 74 22", [this](ptr_manage ptr) {
		get_player_name = ptr.as<fpGetPlayerName>();
	});
	m_pattern.add("MCP", "CE 33 C1 0F BA F0 1D 8B C8 33 4D 67", [=](ptr_manage ptr) {
		model_check_ptr = ptr.add(0x28).as<twentyfourBytes*>();
	});
	m_pattern.add("GS", "83 3D ? ? ? ? ? 8A D9 74 0A", [=](ptr_manage ptr) {
		m_gameState = ptr.add(2).rip(5).as<eGameState*>();
	});
	m_pattern.add("WAC", "80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 08 48 39 0D ? ? ? ? 0F 85", [this](ptr_manage ptr) {
		winapi_check = ptr.as<fpWinapiCheck>();
	});
	m_pattern.add("SNITS", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 33 FF 48 8B F1 48 8D 4C 24 ?", [=](ptr_manage ptr) {
		send_net_info_to_session = ptr.add(13).rip().as<fpSendNetInfoToSession>();
	});
	m_pattern.add("CC", "40 53 48 83 EC 50 44 8A C2 48", [=](ptr_manage ptr) {
		create_cam = ptr.as<fpCreateCam>();
	});
	m_pattern.add("SCC", "48 8B C4 48 89 58 08 57 48 83 EC 60 0F 29 70 E8 F3 0F 10 32 0F 29 78 D8 F3 0F 10 7A ? 8B F9 44 0F 29 40", [=](ptr_manage ptr) {
		set_cam_coord = ptr.as<fpSetCamCoord>();
	});
	m_pattern.add("SCR", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 70 41 8B E8", [=](ptr_manage ptr) {
		set_cam_rot = ptr.as<fpSetCamRot>();
	});
	m_pattern.add("RF", "32 C0 C3", [=](ptr_manage ptr) {
		return_false = ptr.as<fpReturnFalse>();
	});
	m_pattern.add("EPA", "4C 8B 0D ? ? ? ? 44 8B C1 49 8B 41 08", [=](ptr_manage ptr) {
		_entityPoolAddress = ptr.add(3).rip().as<UINT64*>();
	});
	m_pattern.add("VPA", "48 8B 05 ? ? ? ? F3 0F 59 F6 48 8B 08", [=](ptr_manage ptr) {
		_vehiclePoolAddress = ptr.add(3).rip().as<UINT64*>();
	});
	m_pattern.add("PPA", "48 8B 05 ? ? ? ? 41 0F BF C8 0F BF 40 10", [=](ptr_manage ptr) {
		_pedPoolAddress = ptr.add(3).rip().as<UINT64*>();
	});
	m_pattern.add("OPA", "48 8B 05 ? ? ? ? 8B 78 10 85 FF", [=](ptr_manage ptr) {
		_objectPoolAddress = ptr.add(3).rip().as<UINT64*>();
	});
	m_pattern.add("CCT", "E8 ? ? ? ? 83 F8 FF 75 B9", [=](ptr_manage ptr) {
		censor_chat_text = ptr.add(1).rip().as<fpCensorChatText>();
	});
	m_pattern.add("EP", "48 8B DA E8 ? ? ? ? F3 0F 10 44 24", [=](ptr_manage ptr) {
		entity_position = ptr.sub(6).as<fpEntityPosition>();
	});
	m_pattern.add("EMO", "0F 85 ? ? ? ? 48 8B 4B 20 E8 ? ? ? ? 48 8B C8", [=](ptr_manage ptr) {
		entity_model_1 = ptr.add(11).rip().as<fpEntityModel1>();
		entity_model_2 = ptr.sub(0x46).as<fpEntityModel2>();
	});
	m_pattern.add("PJH", "4C 8D 45 D8 48 8D 0D ? ? ? ? 41", [=](ptr_manage ptr) {
		player_join_handler = ptr.add(0x28).as<fpPlayerJoinHandler>();
	});
	m_pattern.add("RWR", "48 8B 47 60 4C 8B C7", [=](ptr_manage ptr) {
		rid_writer = ptr.as<fpRidWriter>();
	});
	m_pattern.add("CREOB", "48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 60 20 55 41 55 41 56 48 8D 68 D9", [=](ptr_manage ptr) {
		create_object = ptr.as<fpCreateObject>();
	});
	m_pattern.add("CV", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 50 F3 0F 10 02", [=](ptr_manage ptr) {
		create_vehicle = ptr.as<fpCreateVehicle>();
	});
	m_pattern.add("CPTI", "40 53 48 83 EC 30 E8 ? ? ? ? 48 8B D8 48 85 C0 0F 84", [=](ptr_manage ptr) {
		clear_ped_tasks_immediately = ptr.as<fpClearPedTasksImmediately>();
	});
	m_pattern.add("AOE", "48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 70 20 55 48 8D 68 B9 48 81 EC ? ? ? ? 0F 29 70 E8 41 8B D8", [=](ptr_manage ptr) {
		add_owned_explosion = ptr.as<fpAddOwnedExplosion>();
	});
	m_pattern.add("SLW", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 40 8A E9", [=](ptr_manage ptr) {
		set_session_weather = ptr.as<fpSetSessionWeather>();
	});
	m_pattern.add("OEB", "3B F8 40 0F 94 C7", [=](ptr_manage ptr) {
		m_ownedExplosionBypass = ptr.as<twoBytes*>();
	});
	m_pattern.add("SMREDG", "40 53 48 83 EC 20 8A D9 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 8B D0 E8 ? ? ? ? 48 85 C0 74 10", [=](ptr_manage ptr) {
		set_mobile_radio_enabled_during_gameplay = ptr.as<fpSetMobileRadioEnabledDuringGameplay>();
	});
	m_pattern.add("AETP", "48 F7 F9 49 8B 48 08 48 63 D0 C1 E0 08 0F B6 1C 11 03 D8", [=](ptr_manage ptr) {
		add_entity_to_pool = ptr.sub(0x68).as<fpAddEntityToPool>();
	});
	m_pattern.add("CAP", "48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D 68 C1 48 81 EC ? ? ? ? 45 8B F9 41 8B F0 4C 8B EA E8 ? ? ? ? 0F B7 0D ? ? ? ? 33 FF 44 8B C7 44 8B D7 44 8B E0 85 C9 7E 1C 48 8B 1D", [=](ptr_manage ptr) {
		create_ambient_pickup = ptr.as<fpCreateAmbientPickup>();
	});
	m_pattern.add("RDW", "89 07 E8 ? ? ? ? B1", [=](ptr_manage ptr) {
		read_bitbuffer_dword = ptr.sub(0x59).as<fpReadDword>();
	});
	m_pattern.add("RW", "7F 2D 44 8B 4B", [=](ptr_manage ptr) {
		read_bitbuffer_word = ptr.sub(0x37).as<fpReadWord>();
	});
	m_pattern.add("IPD", "48 83 EC 28 B2 01 E8 ? ? ? ? 48 85 C0 74 1A", [=](ptr_manage ptr) {
		is_player_dead = ptr.as<fpIsPlayerDead>();
	});
	m_pattern.add("NHFP", "48 89 5C 24 ? 57 48 83 EC 20 80 3D ? ? ? ? ? 41 8B D8 48 8B FA", [=](ptr_manage ptr) {
		network_handle_from_player = ptr.as<fpNetworkHandleFromPlayer>();
	});
	m_pattern.add("GWP", "48 89 5C 24 08 57 48 83 EC 20 8B 15 ? ? ? ? 65 48 8B 04 25 ? ? ? ? 48 8B F9 48 8B 04 D0 B9 B4", [=](ptr_manage ptr) {
		get_waypoint_position = ptr.as<fpGetWaypointPosition>();
	});
	m_pattern.add("NIHV", "40 53 48 83 EC 50 8B C2", [=](ptr_manage ptr) {
		network_is_handle_valid = ptr.as<fpNetworkIsHandleValid>();
	});
	m_pattern.add("SMWL", "45 33 C0 85 C9 0F 84", [=](ptr_manage ptr) {
		set_max_wanted_level = ptr.as<fpSetMaxWantedLevel>();
	});
	m_pattern.add("SCP", "48 8B C4 53 48 81 EC ? ? ? ? F3 0F 10 02 F3 0F 10 4A ? F3 0F 10 52", [=](ptr_manage ptr) {
		set_cam_params = ptr.as<fpSetCamParams>();
	});
	m_pattern.add("SCF", "48 89 5C 24 ? 57 48 83 EC 30 0F 29 74 24 ? 8B F9 0F 28 F1 85 C9 78 13 8B D1 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 EB 02 33 DB 48 85 DB 74 4F", [=](ptr_manage ptr) {
		set_cam_fov = ptr.as<fpSetCamFov>();
	});
	m_pattern.add("PPI", "48 8B 05 ? ? ? ? 48 8B 40 08 C3", [=](ptr_manage ptr) {
		player_ped_id = ptr.as<fpPlayerPedId>();
	});
	m_pattern.add("CCA", "40 53 48 83 EC 50 44 8A C2 8B D1 48 8D 4C 24 ? E8", [=](ptr_manage ptr) {
		create_camera = ptr.as<fpCreateCamera>();
	});
	m_pattern.add("DECA", "40 53 48 83 EC 30 8B D9 84 D2 74 19 44 8B C1 48 8D 0D ? ? ? ? BA ? ? ? ? 48 83 C4 30 5B E9", [=](ptr_manage ptr) {
		destroy_cam = ptr.as<fpDestroyCam>();
	});
	m_pattern.add("DAC", "40 53 48 83 EC 20 84 C9 74 16 48 8D 0D ? ? ? ? BA ? ? ? ? 48 83 C4 20 5B E9", [=](ptr_manage ptr) {
		destroy_all_cams = ptr.as<fpDestroyAllCams>();
	});
	m_pattern.add("ICA", "40 53 48 83 EC 20 8B D9 85 C9 78 10 8B D1 48 8B 0D ? ? ? ? E8 ? ? ? ? EB 02", [=](ptr_manage ptr) {
		is_cam_active = ptr.as<fpIsCamActive>();
	});
	m_pattern.add("GCC", "40 53 48 83 EC 50 0F 29 74 24 ? F3 0F 10 35 ? ? ? ? 0F 29 7C 24 ? F3 0F 10 3D ? ? ? ? 48 8B D9 44 0F 29 44 24 ? F3 44 0F 10 05 ? ? ? ? 85 D2 78 11 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 EB 02", [=](ptr_manage ptr) {
		get_cam_coord = ptr.as<fpGetCamCoord>();
	});
	m_pattern.add("GCR", "48 8B C4 48 89 58 08 57 48 83 EC 60 0F 29 70 E8 F3 0F 10 35 ? ? ? ? 0F 29 78 D8 F3 0F 10 3D ? ? ? ? 41 8B F8 48 8B D9 44 0F 29 40 ? F3 44 0F 10 05 ? ? ? ? 85 D2 78 11 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D0 EB 02", [=](ptr_manage ptr) {
		get_cam_rot = ptr.as<fpGetCamRot>();
	});
	m_pattern.add("TSCCOP", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 3D ? ? ? ? ? 41 8B F0 8B", [=](ptr_manage ptr) {
		trigger_script_crc_check_on_player = ptr.as<fpTriggerScriptCrcCheckOnPlayer>();
	});
	m_pattern.add("GMI", "0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54", [=](ptr_manage ptr) {
		get_model_info = ptr.as<fpGetModelInfo>();
	});
	m_pattern.add("SVEO", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A E9 41 8A F8", [=](ptr_manage ptr) {
		set_vehicle_engine_on = ptr.as<fpSetVehicleEngineOn>();
	});
	m_pattern.add("SECL", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A F1 41 8A E8 40 8A FA", [=](ptr_manage ptr) {
		set_entity_collision = ptr.as<fpSetEntityCollision>();
	});
	m_pattern.add("GGCR", "48 89 5C 24 ? 57 48 83 EC 30 8B DA 48 8B F9 E8 ? ? ? ? 48 8D 4C 24 ? 48 8D 90", [=](ptr_manage ptr) {
		get_gameplay_cam_rot = ptr.as<fpGetGameplayCamRot>();
	});
	m_pattern.add("GGCC", "40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 8B 90", [=](ptr_manage ptr) {
		get_gameplay_cam_coord = ptr.as<fpGetGameplayCamCoord>();
	});
	m_pattern.add("GDWTP", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8A E9 41 8B F0 8B FA E8 ? ? ? ? 48 8B D8 48 85 C0 74 63", [=](ptr_manage ptr) {
		give_delayed_weapon_to_ped = ptr.as<fpGiveDelayedWeaponToPed>();
	});
	m_pattern.add("RAPW", "48 83 EC 28 8B 05 ? ? ? ? 89 05 ? ? ? ? E8", [=](ptr_manage ptr) {
		remove_all_ped_weapons = ptr.as<fpRemoveAllPedWeapons>();
	});
	m_pattern.add("RWFP", "48 89 5C 24 ? 57 48 83 EC 20 8B FA E8 ? ? ? ? 33 DB", [=](ptr_manage ptr) {
		remove_weapon_from_ped = ptr.as<fpRemoveWeaponFromPed>();
	});
	m_pattern.add("IACA", "48 89 5C 24 ? 57 48 83 EC 20 E8 ? ? ? ? 33 D2 48 8B C8 48 8B F8", [=](ptr_manage ptr) {
		is_aim_cam_active = ptr.as<fpIsAimCamActive>();
	});
	m_pattern.add("DRCT", "48 8B C4 48 89 58 08 57 48 83 EC 70 48 63 0D ? ? ? ? 0F", [=](ptr_manage ptr) {
		draw_rect = ptr.as<fpDrawRect>();
	});
	m_pattern.add("DSPR", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 48 81 EC ? ? ? ? 0F 29 70 E8 0F 29 78 D8 48 8B F2 48 8B D9 0F 28 FA 0F 28 F3 E8 ? ? ? ? 80 BC 24", [=](ptr_manage ptr) {
		draw_sprite = ptr.as<fpDrawSprite>();
	});
	m_pattern.add("DPLY", "48 83 EC 58 F3 0F 10 09 F3 0F 10 41", [=](ptr_manage ptr) {
		draw_poly = ptr.as<fpDrawPoly>();
	});
	m_pattern.add("ITMAP", "40 53 48 83 EC 20 48 8D 54 24 ? 33 DB C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B C8 48 85 C0 74 1D 8A 80 ? ? ? ? 24 1F 3C 05 75 11 BA", [=](ptr_manage ptr) {
		is_this_model_a_plane = ptr.as<fpIsThisModelAPlane>();
	});
	m_pattern.add("ITMAH", "40 53 48 83 EC 20 48 8D 54 24 ? 33 DB C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B C8 48 85 C0 74 1E 8A 80 ? ? ? ? 24 1F 3C 05 75 12 83 B9 ? ? ? ? 08", [=](ptr_manage ptr) {
		is_this_model_a_heli = ptr.as<fpIsThisModelAHeli>();
	});
	m_pattern.add("NCB", "E8 ? ? ? ? 84 C0 74 14 44 8B CB", [=](ptr_manage ptr) {
		network_can_bail = ptr.add(1).rip().add(1).rip().add(1).rip().as<fpNetworkCanBail>();
	});
	m_pattern.add("RCE", "66 41 83 F9 ? 0F 83", [=](ptr_manage ptr) {
		received_event = ptr.as<fpReceivedEvent>();
	});
	m_pattern.add("SVUD", "40 53 48 83 EC 20 8A DA E8 ? ? ? ? 48 85 C0 74 20 84 DB", [=](ptr_manage ptr) {
		set_vehicle_undrivable = ptr.as<fpSetVehicleUndrivable>();
	});
	m_pattern.add("SVDB", "48 89 5C 24 ? 57 48 83 EC 20 40 8A FA E8 ? ? ? ? 48 8B D8 48 85 C0 74 36", [=](ptr_manage ptr) {
		set_vehicle_drivable = ptr.as<fpSetVehicleDrivable>();
	});
	m_pattern.add("GDNFV", "48 83 EC 28 48 8D 54 24 ? C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 85 C0 74 16", [=](ptr_manage ptr) {
		get_display_name_from_vehicle = ptr.as<fpGetDisplayNameFromVehicle>();
	});
	m_pattern.add("TVMD", "48 89 5C 24 ? 57 48 83 EC 20 41 8A F8 8B DA 83 FA 0A", [=](ptr_manage ptr) {
		toggle_vehicle_mod = ptr.as<fpToggleVehicleMod>();
	});
	m_pattern.add("DCA", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A F0 8B DA 8B F9", [=](ptr_manage ptr) {
		disable_control_action = ptr.as<fpDisableControlAction>();
	});
	m_pattern.add("SCPW", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8A F0 8B FA E8 ? ? ? ? 48 8B D8 48 85 C0 0F 84", [=](ptr_manage ptr) {
		set_current_ped_weapon = ptr.as<fpSetCurrentPedWeapon>();
	});
	m_pattern.add("TL", "48 8B C8 EB 03 48 8B CB 48 8B 05", [=](ptr_manage ptr) {
		m_thread_list = ptr.add(11).rip().as<datArray<GtaThread*>*>();
	});
	m_pattern.add("SGE", "40 53 48 81 EC ? ? ? ? 44 8B 81", [=](ptr_manage ptr) {
		scripted_game_event = ptr.as<fpNetworkEventType7>();
	});
	m_pattern.add("SWM", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 60 4C 8B F2 48 8B 94 24 ? ? ? ? 33 DB", [=](ptr_manage ptr) {
		set_warning_message_2 = ptr.as<fpSetWarningMessage2>();
	});
	m_pattern.add("ES", "66 83 FA ? 73 13 0F B7 C2 4C 89 84 C1 ? ? ? ? 4C 89 8C C1", [=](ptr_manage ptr) {
		event_struct = ptr.as<char*>();
	});
	m_pattern.add("GCD", "4D 85 C9 0F 84 ? ? ? ? 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 48 20", [=](ptr_manage ptr) {
		get_chat_data = ptr.as<fpGetChatData>();
	});
	m_pattern.add("GCS", "E8 ? ? ? ? 83 BD ? ? ? ? ? 48 8B D8 0F 8D", [=](ptr_manage ptr) {
		get_chat_sender = ptr.add(1).rip().as<fpGetChatSender>();
	});
	m_pattern.add("SMANLN", "40 53 48 83 EC 30 48 8D 54 24 ? 8B D9", [=](ptr_manage ptr) {
		set_model_as_no_longer_needed = ptr.as<fpSetModelAsNoLongerNeeded>();
	});
	m_pattern.add("RM", "48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC 50 8B 45 18", [=](ptr_manage ptr) {
		request_model = ptr.as<fpRequestModel>();
	});
	m_pattern.add("HML", "48 89 7C 24 ? 55 48 8B EC 48 83 EC 20 8B 45 18 BF", [=](ptr_manage ptr) {
		has_model_loaded = ptr.as<fpHasModelLoaded>();
	});
	m_pattern.add("IMV", "48 83 EC 28 8B 44 24 38 48 8D 54 24 ? C7 44 24 ? ? ? ? ? 0D ? ? ? ? 25 ? ? ? ? 89 44 24 38 E8 ? ? ? ? 0F B7 44 24 ? 66 89 44 24 ? 8B 44 24 38 0D ? ? ? ? 0F BA F0 1C 0F B7 C8", [=](ptr_manage ptr) {
		is_model_valid = ptr.as<fpIsModelValid>();
	});
	m_pattern.add("SISM", "48 89 5C 24 ? 57 48 83 EC 20 41 8A F8 84 C9", [=](ptr_manage ptr) {
		set_in_spectator_mode = ptr.as<fpNetworkSetInSpectatorMode>();
	});
	m_pattern.add("IF", "0F B6 D0 48 8B 03 89 10 48 83 C4 20 48 8D 64 24 08 48 8B 5C 24 F8 48 8D 64 24 08", [=](ptr_manage ptr) {
		is_friend = ptr.as<fpIsFriend>();
	});
	m_pattern.add("GEAI", "40 53 48 83 EC 20 4C 8D 05 ? ? ? ? 83 CB FF", [=](ptr_manage ptr) {
		get_event_at_index = ptr.as<fpGetEventAtIndex>();
	});
	m_pattern.add("HTP", "83 F9 FF 74 31 4C 8B 0D", [=](ptr_manage ptr) {
		handle_to_pointer = ptr.as<fpHandleToPointer>();
	});
	m_pattern.add("PTH", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB", [=](ptr_manage ptr) {
		pointer_to_handle = ptr.as<fpPointerToHandle>();
	});
	if (!g_util->is_steam()) {
		m_pattern.add("POPA", "4C 8B 05 ? ? ? ? 40 8A F2 8B E9", [=](ptr_manage ptr) {
			_pickupObjectPoolAddress = ptr.add(3).rip().as<UINT64*>();
		});
	}
	else {
		m_pattern.add("POPA", "8B F0 48 8B 05 ? ? ? ? F3 0F 59 F6", [=](ptr_manage ptr) {
			_pickupObjectPoolAddress = ptr.add(5).rip().as<UINT64*>();
		});
	}
	m_pattern.run("GTA5.exe");
}

pointers::~pointers() {

}