//
//  PVZRemoteControl.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZRemoteControl.h"
#include "PvZ/LawnApp.h"
#include "PvZ/Board.h"
#include "PvZ/ProfileMgr.h"
#include "PvZ/ProfileUtils.h"
#include "PvZ/PlayerInfo.h"
#include "PvZ/TimeMgr.h"
#include "PvZ/CrazyNPCManager.h"
#include "PvZ/GameStateMgr.h"
#include "PvZ/AudioMgr.h"
#include "PvZ/SeedBank.h"
#include "PvZ/SeedPacket.h"
#include "PvZ/ConveyorSeedBank.h"
#include "PvZ/SeedChooser.h"
#include "PvZ/StageModule.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "PvZ/Zombie.h"
#include "PvZ/ZombieType.h"
#include "PvZ/PlantType.h"
#include "PvZ/ObjectTypeDirectory.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "PvZ/SunDropperModule.h"
#include "PvZ/LevelModuleManager.h"
#include "PvZ/Cheats.h"
#include "PvZ/WaveGenerator.h"

void PVZRemoteControl::Play()
{
}

PVZRemoteControl::PVZRemoteControl()
{
}

PVZRemoteControl::~PVZRemoteControl()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZRemoteControl);

void PVZRemoteControl::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZRemoteControl);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(PVZRemoteControl);
}

/////////////// Simple commands ///////////////

std::string PVZRemoteControl::mRsbUsed;

void PVZRemoteControl::SetRsbUsed(const std::string& inRsbUsed)
{
	mRsbUsed = inRsbUsed;
}

std::string PVZRemoteControl::GetRsbUsed()
{
	return mRsbUsed;
}

void PVZRemoteControl::AddSunMoney(int i_amt)
{
	gLawnApp->m_board->AddSunMoney(i_amt);
}

void PVZRemoteControl::SpawnAllPlants()
{
	if (gLawnApp && gLawnApp->m_board)
		gLawnApp->m_board->TestSpawnAllPlants();
}

void PVZRemoteControl::SpawnRandomPlants()
{
	if (gLawnApp && gLawnApp->m_board)
		gLawnApp->m_board->TestSpawnRandomPlants();
}

void PVZRemoteControl::KillAllPlants()
{
	if (gLawnApp && gLawnApp->m_board)
		gLawnApp->m_board->DestroyAllPlants();
}

void PVZRemoteControl::KillAllZombies()
{
	if (gLawnApp && gLawnApp->m_board)
		gLawnApp->m_board->DestroyAllZombies();
}

void PVZRemoteControl::PlantFoodAllPlants()
{
	if (gLawnApp && gLawnApp->m_board)
		gLawnApp->m_board->TestPlantFoodAllPlants();
}

void PVZRemoteControl::RemoveMowers()
{
	if (gLawnApp->m_board)
		gLawnApp->m_board->DestroyAllMowers();
}

void PVZRemoteControl::SetTestMode(bool i_mode)
{
	gLawnApp->m_testMode = i_mode;
}

void PVZRemoteControl::SetRecordingStrings(bool i_status)
{
	gLawnApp->m_recordStringsEnabled = i_status;
}

void PVZRemoteControl::ReadOnlyMode(bool i_status)
{
	ProfileMgr::GetInstance().SetReadOnlyMode(i_status);
}

void PVZRemoteControl::AddStars(int i_amt)
{
	ProfileMgr::GetInstance().GetCurrentProfile()->AddStars(i_amt);
}

void PVZRemoteControl::UnlockAllLevels()
{
	ProfileUtils::CompleteAllLevels(true);
}

void PVZRemoteControl::StartLevel()
{
	gLawnApp->m_board->StartLevel();
}

void PVZRemoteControl::MainMenu()
{
	gGameStateMgr->ShowMainMenu();
}

void PVZRemoteControl::ResetPlayer()
{
	ProfileUtils::ResetPlayerInfo(ProfileMgr::GetInstance().GetCurrentProfile());
	MainMenu();
}

void PVZRemoteControl::ToggleFPSPig()
{
	if (gLawnApp && gLawnApp->m_board)
		gLawnApp->m_board->ToggleShowPig();
}

bool PVZRemoteControl::IsPlaying()
{
	if (gLawnApp && gLawnApp->m_board)
		return gLawnApp->m_board->IsPlaying();
	return false;
}

void PVZRemoteControl::SetSkipNarration(bool i_status)
{
	gLawnApp->GetNarrationSystem()->SetSkipAllNarration(i_status);
}

void PVZRemoteControl::SetTimeScale(float i_scale)
{
	if (i_scale != 0.0f)
		Sexy::LazySingleton<TimeMgr>::GetInstancePtr()->SetTimeScale(i_scale);
}

bool PVZRemoteControl::GetPaused()
{
	if (gLawnApp && gLawnApp->m_board)
		return gLawnApp->m_board->IsPaused();
	return false;
}

void PVZRemoteControl::SetPaused(bool i_paused)
{
	if (gLawnApp && gLawnApp->m_board)
		gLawnApp->m_board->Pause(i_paused);
}

void PVZRemoteControl::AddCoins(int i_amt)
{
	PlayerInfo* info = ProfileMgr::GetInstance().GetCurrentProfile();
	if (info)
	{
		info->AM_SetCoins(info->AM_GetCoins() + i_amt);
		AudioMgr::GetInstancePtr()->SendEvent("Play_Buttonclick");
	}
}

void PVZRemoteControl::SaveStateTo(std::string& i_profileName)
{
	ProfileMgr::GetInstance().SaveAs(ProfileMgr::GetInstance().GetCurrentProfile(), Sexy::StringToWString(i_profileName));
}

void PVZRemoteControl::LoadProfile(std::string& i_profileName)
{
	MainMenu();
	ProfileMgr::GetInstance().LoadAndSetProfile(Sexy::StringToWString(i_profileName));
}

void PVZRemoteControl::NextWave()
{
	if (gLawnApp && gLawnApp->m_board)
	{
		WaveGenerator* waveGen = gLawnApp->m_board->GetWaveGenerator();
		if (waveGen)
		{
			if (waveGen->GetHugeWaveTime() < PVZ_EOT())
				waveGen->SetHugeWaveTime(PVZ_T());
			else
				waveGen->SpawnNextWaveIn(0.1f);
		}
	}
}

void PVZRemoteControl::ToggleHealthBars()
{
	CheatManager::GetInstancePtr()->ToggleCheat("HealthBars");
}

bool PVZRemoteControl::GetEasyPlantingMode()
{
	return CheatManager::GetInstancePtr()->GetToggleValue("FreePlanting");
}

void PVZRemoteControl::SetEasyPlantingMode(bool i_enabled)
{
	if (gLawnApp)
		CheatManager::GetInstancePtr()->SetToggleValue("FreePlanting", i_enabled);
}

std::string PVZRemoteControl::ToggleEasyPlanting()
{
	bool enabled = GetEasyPlantingMode();
	SetEasyPlantingMode(!enabled);
	if (!enabled)
		return "Easy planting turned on.";
	return "Easy planting turned off.";
}

std::string PVZRemoteControl::TogglePause()
{
	bool paused = GetPaused();
	SetPaused(!paused);
	if (!paused)
		return "Game has been paused";
	return "Game has been unpaused";
}

std::string PVZRemoteControl::ToggleWavePause()
{
	if (!gLawnApp->m_board)
		return "Unable to pause wave, not in a level";

	WaveGenerator* waveGen = gLawnApp->m_board->GetWaveGenerator();
	bool paused = !waveGen->IsZombieWaveSpawningPaused();
	waveGen->SetZombieWaveSpawningPaused(paused);
	if (paused)
		return "Waves have been paused";
	return "Waves have been unpaused";
}

std::string PVZRemoteControl::TogglePlantFoodMode()
{
	bool enabled = CheatManager::GetInstancePtr()->ToggleCheat("PlantfoodZombies");
	if (enabled)
		return "Plantfood Mode has been turned on.";
	return "Plantfood Mode has been turned off.";
}

void PVZRemoteControl::SetDroppingSunPaused(bool i_status)
{
	if (gLawnApp->m_board)
	{
		SunDropperModule* sunDropper = gLawnApp->m_board->m_levelModuleManager->GetModuleByClass<SunDropperModule>();
		if (sunDropper)
			sunDropper->SetPaused(i_status);
	}
}

void PVZRemoteControl::LoadLevel(std::string& i_level)
{
	gGameStateMgr->StartLevel("", i_level, -1, GAMETRANSITION_None, GAMETRANSITION_None, LEVELSOURCE_Arcade);
}

void PVZRemoteControl::SetDate(const std::string& i_date)
{
	if (i_date == "default")
	{
		TimeMgr::GetInstancePtr()->ClearDateOverride();
	}
	else
	{
		tm date;
		memset(&date, 0, sizeof(date));
		if (DateStringToTM(i_date, date))
			TimeMgr::GetInstancePtr()->SetDateOverride(Sexy::GetTimegm(&date) - Sexy::GetBJTimeOffset());
	}
}

bool PVZRemoteControl::RsbPatchFileExists()
{
	std::string path = GetFolder(Sexy::IFileDriver::PathType_LoadData) + "patch.rsbpatch";
	return gSexyAppBase->mFileDriver->FileExists(path, NULL);
}

bool PVZRemoteControl::RemoveNewRsb()
{
	std::string path = GetFolder(Sexy::IFileDriver::PathType_Cache) + "new.rsb";
	if (!gSexyAppBase->mFileDriver->FileExists(path, NULL))
		return false;
	return gSexyAppBase->mFileDriver->DeleteFile(path);
}

void PVZRemoteControl::ForceUnloadPlantType(std::string& i_plantType)
{
	if (gLawnApp && gLawnApp->m_board)
	{
		PlantTypePtr type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(i_plantType);
		if (type.IsValid())
			gLawnApp->m_board->DeleteResourceGroupForGameplay(type->PlantFramework);
	}
}

void PVZRemoteControl::SpawnAllZombies()
{
	if (gLawnApp && gLawnApp->m_board)
	{
		for (ObjectTypeDirectoryIterator<ZombieType> it; it; ++it)
		{
			const ZombieType* type = *it;
			if (type && type->Placeable)
				gLawnApp->m_board->AddZombie(*it, -1, 1, false, false);
		}
	}
}

std::string PVZRemoteControl::SpawnZombie(std::string& i_zombieType)
{
	if (gLawnApp && gLawnApp->m_board)
	{
		ZombieTypePtr type = gLawnApp->m_board->GetZombieType(i_zombieType);
		Zombie* zombie = gLawnApp->m_board->CheatAddZombie(type, -1, true);
		std::string result;
		zombie->GetPtr().GetId().ToString(result);
		return result;
	}
	return "";
}

std::string PVZRemoteControl::SpawnZombieAtRow(std::string& i_zombieType, int i_row)
{
	if (gLawnApp && gLawnApp->m_board)
	{
		ZombieTypePtr type = gLawnApp->m_board->GetZombieType(i_zombieType);
		Zombie* zombie = gLawnApp->m_board->CheatAddZombie(type, i_row, true);
		std::string result;
		zombie->GetPtr().GetId().ToString(result);
		return result;
	}
	return "";
}

std::string PVZRemoteControl::SpawnPlant(std::string& i_plantType, int i_col, int i_row)
{
	if (!gLawnApp || !gLawnApp->m_board)
		return "Could not spawn plant.";

	Plant* plant = gLawnApp->m_board->TestSpawnPlant(i_plantType, i_col, i_row);
	if (!plant)
		return "Could not spawn plant, invalid type.";

	std::string result;
	plant->GetPtr().GetId().ToString(result);
	return result;
}

class NullRsbPatchListener : public Sexy::IRSBPatcherListener
{
public:
	virtual void PatchStarted(const Sexy::RSBPatcher* inPatcher, void* inListenerContext) {}
	virtual void PatchComplete(const Sexy::RSBPatcher* inPatcher, void* inListenerContext) {}
	virtual void PatchError(const Sexy::RSBPatcher* inPatcher, void* inListenerContext) {}
	virtual void PatchCanceled(const Sexy::RSBPatcher* inPatcher, void* inListenerContext) {}
};

bool PVZRemoteControl::ApplyRsbPatch()
{
	char success = RsbPatchFileExists();
	if (success)
	{
		std::string patchPath = GetFolder(Sexy::IFileDriver::PathType_LoadData) + "patch.rsbpatch";
		std::string basePath = GetFolder(Sexy::IFileDriver::PathType_LoadData) + "main.rsb";
		std::string newPath = GetFolder(Sexy::IFileDriver::PathType_Cache) + "new.rsb";
		NullRsbPatchListener listener;
		Sexy::RSBPatcher patcher(gSexyAppBase, &listener);
		patcher.Start(basePath, patchPath, newPath);
		do
		{
			patcher.Update();
			Sexy::SexySleep(50);
		} while (patcher.IsFinished());
		if (patcher.GetStatus() != Sexy::RSBPatcher::Status_Complete)
			return false;
	}
	return success;
}

void PVZRemoteControl::SetDebug(std::string& i_debugType)
{
	if (gLawnApp->m_board)
	{
		std::string type = Sexy::StringToLower(i_debugType);
		if (type == "boxes")
			gLawnApp->m_board->m_debugTextMode = DEBUG_TEXT_COLLISION;
		else if (type == "life")
			gLawnApp->m_board->m_debugTextMode = DEBUG_TEXT_LIFEBARS;
		else if (type == "music")
			gLawnApp->m_board->m_debugTextMode = DEBUG_TEXT_MUSIC;
		else if (type == "spawn")
			gLawnApp->m_board->m_debugTextMode = DEBUG_TEXT_ZOMBIE_SPAWN;
		else if (type == "memory")
			gLawnApp->m_board->m_debugTextMode = DEBUG_TEXT_MEMORY;
		else if (type == "none")
			gLawnApp->m_board->m_debugTextMode = DEBUG_TEXT_NONE;
	}
}

void PVZRemoteControl::ForceUnloadResourcesForZombie(std::string& i_zombieType)
{
	if (gLawnApp && gLawnApp->m_board)
	{
		ZombieTypePtr type = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(i_zombieType);
		if (!type.IsValid())
			type = gLawnApp->m_board->GetStage()->ResolveZombieType(i_zombieType);

		if (type.IsValid())
		{
			gLawnApp->m_board->DeleteResourceGroupsForGameplay(type->GetArtResourceGroups());
			gLawnApp->m_board->DeleteResourceGroupsForGameplay(type->GetAudioGroups());
		}
	}
}

void PVZRemoteControl::GivePacket(std::string& i_packet)
{
	SeedBankNew* seedBank = gLawnApp->m_board ? gLawnApp->m_board->GetSeedBank() : NULL;
	if (!seedBank)
		return;

	ConveyorSeedBank* conveyor = seedBank->Cast<ConveyorSeedBank>();
	if (conveyor)
	{
		conveyor->ForceSpawn(i_packet);
		return;
	}

	PlantTypePtr type = ObjectTypeDirectory<PlantType>::GetInstancePtr()->GetTypeFromTypeName(i_packet);
	if (type.IsValid())
	{
		SeedChooser* chooser = gLawnApp->m_board->GetSeedChooser();
		if (!chooser)
		{
		for (int i = seedBank->GetPacketCount() - 1; i > 0; --i)
		{
			RtWeakPtr<SeedPacket> dst = seedBank->GetPacket(i);
			RtWeakPtr<SeedPacket> src = seedBank->GetPacket(i - 1);
			dst.Get()->SetPlantType(src.Get()->GetPlantType());
		}
		RtWeakPtr<SeedPacket> first = seedBank->GetPacket(0);
		first.Get()->SetPlantType(type);
			return;
		}
		chooser->ForceSelection(i_packet);
	}
}
