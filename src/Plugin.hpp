namespace GOTHIC_NAMESPACE 
{
	bool EdgesFixAffectPlayer;
	bool EdgesFixAffectHumans;
	bool EdgesFixAffectOtherMonsters;

	int oCNpc::IsFlyingCreature_Union()
	{
		switch (this->GetTrueGuild())
		{
		case NPC_GIL_DEMON:
		case NPC_GIL_BLOODFLY:
	#if ENGINE >= Engine_G2A
		case NPC_GIL_HARPY:
		case NPC_GIL_SUMMONED_DEMON:
		case NPC_GIL_SKELETON_MAGE:
	#endif
			return TRUE;

		default:
			break;
		}
		
		return FALSE;
	}

	auto Hook_zCAIPlayer_CheckPhysics = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x004FE140, 0x00511520, 0x0050AE90, 0x0050DC40)), &zCAIPlayer::CheckPhysics_Union);
	void zCAIPlayer::CheckPhysics_Union()
	{
		oCNpc* npc = zDYNAMIC_CAST<oCNpc>(this->vob);

		if (player == this->vob)
		{
			(this->*Hook_zCAIPlayer_CheckPhysics)();
			return;
		}

		static int ZS_MM_ATTACK = parser->GetIndex("ZS_MM_ATTACK");
		if (ZS_MM_ATTACK == -1
			|| !(this->model && !this->model->isFlying && this->aboveFloor > 5.0f)
			|| !npc
			|| !npc->IsAIState(ZS_MM_ATTACK)
			|| !npc->GetEM()->IsEmpty(TRUE)
			|| npc->fight_waitForAniEnd != -1
			|| !npc->enemy
			)
		{
			(this->*Hook_zCAIPlayer_CheckPhysics)();
			return;
		}

		switch (npc->GetCurrentFightMove())
		{
		case oCNpc::NPC_FIGHTMOVE_TURN:
		case oCNpc::NPC_FIGHTMOVE_WAIT:
		case oCNpc::NPC_FIGHTMOVE_RUNBACK:

#if ENGINE >= Engine_G2
		case oCNpc::NPC_FIGHTMOVE_WAIT_EXT:
		case oCNpc::NPC_FIGHTMOVE_WAIT_LONG:
#endif
			break;

		default:
			(this->*Hook_zCAIPlayer_CheckPhysics)();
			return;
		}

		if (npc->bbox3D.mins[VY] <= npc->enemy->bbox3D.mins[VY]
			|| !(this->aboveFloor > 45.0f || !npc->IsSameHeight(npc->enemy) || !npc->enemy->IsSameHeight(npc))
			)
		{
			(this->*Hook_zCAIPlayer_CheckPhysics)();
			return;
		}

		auto aboveFlor_prev = this->aboveFloor;
		this->aboveFloor = this->config.zMV_STEP_HEIGHT + 1.0f;
		(this->*Hook_zCAIPlayer_CheckPhysics)();
		this->aboveFloor = aboveFlor_prev;
	}

	auto SlopeAddr = zSwitch(0x53d2b9, 0x55494b, 0x54c6e1, 0x551901);
	void __fastcall zCCollObjectCharacter_TestHardCollisions_Slope(::Union::Registers& reg)
	{
		zCCollObjectCharacter* This = nullptr;

#if ENGINE >= Engine_G2
		This = reinterpret_cast<zCCollObjectCharacter*>(reg.ebx);
#else
		This = reinterpret_cast<zCCollObjectCharacter*>(reg.ebp);
#endif

		if (!This)
		{
			return;
		}
		
		auto vob = static_cast<zCVob*>(This->m_pvClientData);
		auto npc = zDYNAMIC_CAST<oCNpc>(vob);

		if (!npc)
		{
			return;
		}

		if(npc == player)
		{
			if(!EdgesFixAffectPlayer)
			{
				return;
			}
		}
		else if(!npc->IsFlyingCreature_Union() && npc->IsHuman())
		{
			if(!EdgesFixAffectHumans)
			{
				return;
			}
		}
		else if(!npc->IsFlyingCreature_Union() && !npc->IsHuman())
		{
			if(!EdgesFixAffectOtherMonsters)
			{
				return;
			}
		}

		int EndOffset = 0;
#if ENGINE >= Engine_G2
		EndOffset = 0x1a4;
#elif ENGINE == Engine_G1
		EndOffset = 0x133;
#else
		EndOffset = 0x146;
#endif
		reg.eip = SlopeAddr + EndOffset;
	}
	auto PartialHook_zCCollObjectCharacter_TestHardCollisions_Slope = ::Union::CreatePartialHook(reinterpret_cast<void*>(SlopeAddr), &zCCollObjectCharacter_TestHardCollisions_Slope);

	auto AbyssAddr = zSwitch(0x53d4d0, 0x554b8a, 0x54c96d, 0x551b8d);
	void __fastcall zCCollObjectCharacter_TestHardCollisions_Abyss(::Union::Registers& reg)
	{
		zCCollObjectCharacter* This = nullptr;

#if ENGINE >= Engine_G2
		This = reinterpret_cast<zCCollObjectCharacter*>(reg.ebx);
#else
		This = reinterpret_cast<zCCollObjectCharacter*>(reg.ebp);
#endif

		if (!This)
		{
			return;
		}

		auto vob = static_cast<zCVob*>(This->m_pvClientData);
		auto npc = zDYNAMIC_CAST<oCNpc>(vob);

		if (!npc)
		{
			return;
		}

		if(npc == player)
		{
			if(!EdgesFixAffectPlayer)
			{
				return;
			}
		}
		else if(!npc->IsFlyingCreature_Union() && npc->IsHuman())
		{
			if(!EdgesFixAffectHumans)
			{
				return;
			}
		}
		else if(!npc->IsFlyingCreature_Union() && !npc->IsHuman())
		{
			if(!EdgesFixAffectOtherMonsters)
			{
				return;
			}
		}

		int EndOffset = 0;
#if ENGINE >= Engine_G2
		EndOffset = 0x41;
#else
		EndOffset = 0x40;
#endif
		reg.eip = AbyssAddr + EndOffset;
	}
	auto PartialHook_zCCollObjectCharacter_TestHardCollisions_Abyss = ::Union::CreatePartialHook(reinterpret_cast<void*>(AbyssAddr), &zCCollObjectCharacter_TestHardCollisions_Abyss);

	void Game_EntryPoint()
	{

	}

	void Game_Init()
	{

	}

	void Game_Exit()
	{

	}

	void Game_PreLoop()
	{

	}

	void Game_Loop()
	{

	}

	void Game_PostLoop()
	{

	}

	void Game_MenuLoop()
	{

	}

	void Game_SaveBegin()
	{

	}

	void Game_SaveEnd()
	{

	}

	void LoadBegin()
	{

	}

	void LoadEnd()
	{

	}

	void Game_LoadBegin_NewGame()
	{
		LoadBegin();
	}

	void Game_LoadEnd_NewGame()
	{
		LoadEnd();
	}

	void Game_LoadBegin_SaveGame()
	{
		LoadBegin();
	}

	void Game_LoadEnd_SaveGame()
	{
		LoadEnd();
	}

	void Game_LoadBegin_ChangeLevel()
	{
		LoadBegin();
	}

	void Game_LoadEnd_ChangeLevel()
	{
		LoadEnd();
	}

	void Game_LoadBegin_TriggerChangeLevel()
	{

	}

	void Game_LoadEnd_TriggerChangeLevel()
	{

	}

	void Game_Pause()
	{

	}

	void Game_Unpause()
	{

	}

	void Game_DefineExternals()
	{

	}

	void Game_ApplySettings()
	{
		EdgesFixAffectPlayer = zoptions->ReadBool("FlyingCreaturesFix", "EdgesFixAffectPlayer", false);
		EdgesFixAffectHumans = zoptions->ReadBool("FlyingCreaturesFix", "EdgesFixAffectHumans", false);
		EdgesFixAffectOtherMonsters = zoptions->ReadBool("FlyingCreaturesFix", "EdgesFixAffectOtherMonsters", false);
	}

	/*int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	auto Hook_WinMain = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x004F3E10, 0x00506810, 0x005000F0, 0x00502D70)), &WinMain, ::Union::HookType::Hook_Auto);
	int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
	{
		Game_EntryPoint();
		return Hook_WinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	}*/

	/*void __fastcall oCGame_Init(oCGame* self, void* vtable);
	auto Hook_oCGame_Init = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x00636F50, 0x0065D480, 0x006646D0, 0x006C1060)), &oCGame_Init, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_Init(oCGame* self, void* vtable)
	{
		Hook_oCGame_Init(self, vtable);
		Game_Init();
	}*/

	/*void __fastcall CGameManager_Done(CGameManager* self, void* vtable);
	auto Hook_CGameManager_Done = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x00424850, 0x00427310, 0x004251A0, 0x004254E0)), &CGameManager_Done, ::Union::HookType::Hook_Auto);
	void __fastcall CGameManager_Done(CGameManager* self, void* vtable)
	{
		Game_Exit();
		Hook_CGameManager_Done(self, vtable);
	}*/

	/*void __fastcall oCGame_Render(oCGame* self, void* vtable);
	auto Hook_oCGame_Render = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063DBE0, 0x006648F0, 0x0066B930, 0x006C86A0)), &oCGame_Render, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_Render(oCGame* self, void* vtable)
	{
		Game_PreLoop();
		Hook_oCGame_Render(self, vtable);
		Game_PostLoop();
	}*/

	/*void __fastcall zCWorld_Render(::Union::Registers& reg);
	auto Partial_zCWorld_Render = ::Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x005F409C, 0x00614F4C, 0x0061A1F0, 0x00621940)), &zCWorld_Render);
	void __fastcall zCWorld_Render(::Union::Registers& reg)
	{
		Game_Loop();
	}*/

	/*void __fastcall zCMenu_Render(zCMenu* self, void* vtable);
	auto Hook_zCMenu_Render = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x004D0DA0, 0x004E14E0, 0x004DB270, 0x004DDC20)), &zCMenu_Render, ::Union::HookType::Hook_Auto);
	void __fastcall zCMenu_Render(zCMenu* self, void* vtable)
	{
		Hook_zCMenu_Render(self, vtable);
		Game_MenuLoop();
	}*/

	/*void __fastcall oCGame_WriteSaveGame(oCGame* self, void* vtable, int slot, zBOOL saveGlobals);
	auto Hook_oCGame_WriteSaveGame = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063AD80, 0x00661680, 0x006685D0, 0x006C5250)), &oCGame_WriteSaveGame, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_WriteSaveGame(oCGame* self, void* vtable, int slot, zBOOL saveGlobals)
	{
		Game_SaveBegin();
		Hook_oCGame_WriteSaveGame(self, vtable, slot, saveGlobals);
		Game_SaveEnd();
	}*/

	/*void __fastcall oCGame_LoadGame(oCGame* self, void* vtable, int slot, const zSTRING& levelPath);
	auto Hook_oCGame_LoadGame = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063C070, 0x00662B20, 0x00669970, 0x006C65A0)), &oCGame_LoadGame, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_LoadGame(oCGame* self, void* vtable, int slot, const zSTRING& levelPath)
	{
		Game_LoadBegin_NewGame();
		Hook_oCGame_LoadGame(self, vtable, slot, levelPath);
		Game_LoadEnd_NewGame();
	}*/

	/*void __fastcall oCGame_LoadSaveGame(oCGame* self, void* vtable, int slot, zBOOL loadGlobals);
	auto Hook_oCGame_LoadSaveGame = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063C2A0, 0x00662D60, 0x00669BA0, 0x006C67D0)), &oCGame_LoadSaveGame, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_LoadSaveGame(oCGame* self, void* vtable, int slot, zBOOL loadGlobals)
	{
		Game_LoadBegin_SaveGame();
		Hook_oCGame_LoadSaveGame(self, vtable, slot, loadGlobals);
		Game_LoadEnd_SaveGame();
	}*/

	/*void __fastcall oCGame_ChangeLevel(oCGame* self, void* vtable, const zSTRING& levelpath, const zSTRING& startpoint);
	auto Hook_Game_Load_ChangeLevel = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063CD60, 0x00663950, 0x0066A660, 0x006C7290)), &oCGame_ChangeLevel, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_ChangeLevel(oCGame* self, void* vtable, const zSTRING& levelpath, const zSTRING& startpoint)
	{
		Game_LoadBegin_ChangeLevel();
		Hook_Game_Load_ChangeLevel(self, vtable, levelpath, startpoint);
		Game_LoadEnd_ChangeLevel();
	}*/

	/*void __fastcall oCGame_TriggerChangeLevel(oCGame* self, void* vtable, const zSTRING& levelpath, const zSTRING& startpoint);
	auto Hook_oCGame_TriggerChangeLevel = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063D480, 0x00664100, 0x0066AD80, 0x006C7AF0)), &oCGame_TriggerChangeLevel, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_TriggerChangeLevel(oCGame* self, void* vtable, const zSTRING& levelpath, const zSTRING& startpoint)
	{
		Game_LoadBegin_TriggerChangeLevel();
		Hook_oCGame_TriggerChangeLevel(self, vtable, levelpath, startpoint);
		Game_LoadEnd_TriggerChangeLevel();
	}*/

/*#if ENGINE <= Engine_G1A
	void __fastcall oCGame_Pause_G1(oCGame* self, void* vtable);
	auto Hook_oCGame_Pause = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063DF50, 0x00664CD0, 0, 0)), &oCGame_Pause_G1, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_Pause_G1(oCGame* self, void* vtable)
	{
		Hook_oCGame_Pause(self, vtable);
		Game_Pause();
	}
#else
	void __fastcall oCGame_Pause_G2(oCGame* self, void* vtable, zBOOL sessionPaused);
	auto Hook_oCGame_Pause = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0, 0, 0x0066BD50, 0x006C8AD0)), &oCGame_Pause_G2, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_Pause_G2(oCGame* self, void* vtable, zBOOL sessionPaused)
	{
		Hook_oCGame_Pause(self, vtable, sessionPaused);
		Game_Pause();
	}
#endif*/

	/*void __fastcall oCGame_Unpause(oCGame* self, void* vtable);
	auto Hook_oCGame_Unpause = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0063E1D0, 0x00664F80, 0x0066BFD0, 0x006C8D50)), &oCGame_Unpause, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_Unpause(oCGame* self, void* vtable)
	{
		Hook_oCGame_Unpause(self, vtable);
		Game_Unpause();
	}*/

	/*void __fastcall oCGame_DefineExternals_Ulfi(oCGame* self, void* vtable, zCParser* parser);
	auto Hook_oCGame_DefineExternals_Ulfi = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x006495B0, 0x006715F0, 0x00677A00, 0x006D4780)), &oCGame_DefineExternals_Ulfi, ::Union::HookType::Hook_Auto);
	void __fastcall oCGame_DefineExternals_Ulfi(oCGame* self, void* vtable, zCParser* parser)
	{
		Hook_oCGame_DefineExternals_Ulfi(self, vtable, parser);
		Game_DefineExternals();
	}*/

	void __fastcall CGameManager_ApplySomeSettings(CGameManager* self, void* vtable);
	auto Hook_CGameManager_ApplySomeSettings = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x004267C0, 0x004291E0, 0x00427370, 0x004276B0)), &CGameManager_ApplySomeSettings, ::Union::HookType::Hook_Auto);
	void __fastcall CGameManager_ApplySomeSettings(CGameManager* self, void* vtable)
	{
		Hook_CGameManager_ApplySomeSettings(self, vtable);
		Game_ApplySettings();
	}
}