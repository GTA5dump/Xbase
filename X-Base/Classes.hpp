#pragma once
#include "datatypes.hpp"
#include "lists.hpp"
#include "pch.h"

class CPlayerInfoNew
{
public:
	char pad_0000[52]; //0x0000
	int32_t internal_ip; //0x0034
	int16_t internal_port; //0x0038
	char pad_003A[2]; //0x003A
	int32_t relay_ip; //0x003C
	uint16_t relay_port; //0x0040
	char pad_0042[2]; //0x0042
	int32_t external_ip; //0x0044
	int16_t external_port; //0x0048
	char pad_004A[50]; //0x004A
	char name[20]; //0x007C
	char pad_0090[4]; //0x0090
	int32_t current_team; //0x0094
	char pad_0098[76]; //0x0098
	float swim_speed; //0x00E4 dont work
	float run_speed; //0x00E8 dont work
	char pad_00EC[220]; //0x00EC
	class CPed* entity_pointer; //0x01C8
	char pad_01D0[40]; //0x01D0
	bool N0000077A; //0x01F8
	uint32_t frame_flags; //0x01F8
	char pad_01FA[1566]; //0x01FA
	uint32_t wanted_level; //0x0818
	char pad_0819[1775]; //0x0819
}; //Size: 0x0EA0

union netAddress
{
	std::uint32_t m_raw;
	struct
	{
		std::uint8_t m_field4;
		std::uint8_t m_field3;
		std::uint8_t m_field2;
		std::uint8_t m_field1;
	};
};

class netPlayerData
{
public:
	std::uint64_t m_unk1;         // 0x00
	std::uint64_t m_unk2;         // 0x08
	std::uint32_t m_sec_key_time; // 0x10
	netAddress    m_lan_ip;       // 0x14
	std::uint16_t m_lan_port;     // 0x18
	char          m_pad1[0x02];   // 0x1A
	netAddress    m_relay_ip;     // 0x1C
	std::uint16_t m_relay_port;   // 0x20
	char          m_pad2[0x02];   // 0x22
	netAddress    m_online_ip;    // 0x24
	std::uint16_t m_online_port;  // 0x26
	char          m_pad3[0x1E];   // 0x28
	std::uint64_t m_rockstar_id;  // 0x48
	bool          m_id_flag;      // 0x50
	char          m_pad4[0x0B];   // 0x51
	char          m_name[0x14];   // 0x5C
};

class netPlayer
{
public:
	virtual ~netPlayer() = default;            // 0 (0x00)
	virtual void reset() = 0;                  // 1 (0x08)
	virtual bool is_valid() const = 0;         // 2 (0x10)
	virtual const char *get_name() const = 0;  // 3 (0x18)
	virtual void _0x20() = 0;                  // 4 (0x20)
	virtual bool is_host() = 0;                // 5 (0x28)
	virtual netPlayerData *get_net_data() = 0; // 6 (0x30)
	virtual void _0x38() = 0;                  // 7 (0x38)
};

class CNetGamePlayer : public netPlayer
{
public:
	virtual ~CNetGamePlayer() = 0;
	char m_Pad1[0x08];                               // 0x08
	void* m_NonPhysicalPlayerData;                   // 0x10
	char m_Pad2[0x15];                               // 0x18
	std::uint8_t m_player_id;                        // 0x2D
	char m_Pad3[0x7A];                               // 0x2E
	CPlayerInfoNew* playerInfo;                      // 0xA8
	char m_Pad4[0xF1];                               // 0xB0
	bool m_IsRockstarDev;                            // 0x1A1
	char m_Pad5[0x01];                               // 0x1A2
	bool m_IsCheater;                                // 0x1A3
	char m_Pad6[0xFC];                               // 0x1A4
};

class scrThreadContext
{
public:
	int ThreadID;
	int ScriptHash;
	eThreadState State;
	int _IP;
	int FrameSP;
	int _SPP;
	float TimerA;
	float TimerB;
	int TimerC;
	int _mUnk1;
	int _mUnk2;
	int _f2C;
	int _f30;
	int _f34;
	int _f38;
	int _f3C;
	int _f40;
	int _f44;
	int _f48;
	int _f4C;
	int _f50;
	int pad1;
	int pad2;
	int pad3;
	int _set1;
	int pad[17];
};

class scrThread
{
public:
	virtual ~scrThread() = default;                                                                 // 0 (0x00)
	virtual void reset(std::uint32_t script_hash, void *args, std::uint32_t arg_count) = 0;         // 1 (0x08)
	virtual eThreadState run() = 0;                                                                 // 2 (0x10)
	virtual eThreadState tick(std::uint32_t ops_to_execute) = 0;                                    // 3 (0x18)
	virtual void kill() = 0;                                                                        // 4 (0x20)

public:
	scrThreadContext m_context;                 // 0x08
	void *m_stack;                              // 0xB0
	char m_padding[0x10];                       // 0xB8
	const char *m_exit_message;                 // 0xC8
	char m_name[0x40];                          // 0xD0
	void** m_handler;							// 0x110
};

class ScriptThread : scrThread
{
public:
	const char Name[64];
	void *m_pScriptHandler;
	const char gta_pad2[40];
	const char flag1;
	const char m_networkFlag;
	bool bool1;
	bool bool2;
	bool bool3;
	bool bool4;
	bool bool5;
	bool bool6;
	bool bool7;
	bool bool8;
	bool bool9;
	bool bool10;
	bool bool11;
	bool bool12;
	const char gta_pad3[10];
};

class GtaThread : public scrThread
{
public:
	void *m_stack;
	uint32_t m_script_hash;						// 0x120
	char m_padding3[0x14];                      // 0x124
	std::int32_t m_instance_id;                 // 0x138
	char m_padding4[0x04];                      // 0x13C
	std::uint8_t m_flag1;                       // 0x140
	bool m_safe_for_network_game;               // 0x141
	char m_padding5[0x02];                      // 0x142
	bool m_is_minigame_script;                  // 0x144
	char m_padding6[0x02];                      // 0x145
	bool m_can_be_paused;                       // 0x147
	bool m_can_remove_blips_from_other_scripts; // 0x148
	char m_padding7[0x0F];                      // 0x149
};