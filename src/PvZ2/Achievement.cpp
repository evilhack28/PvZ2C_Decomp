//
//  Achievement.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//
/////////////// Achievement ///////////////

#include "PvZ/Achievement.h"
#include "PvZ/GameCenterProxy.h"
#include "PvZ/AchievementDriverMgr.h"
#include "PvZ/Board.h"
#include "PvZ/LawnApp.h"
#include "PvZ/LevelDefinition.h"
#include "PvZ/Zombie.h"
#include "PvZ/ZombieExplorer.h"
#include "PvZ/Plant.h"
#include "PvZ/Plant_Peapod.h"
#include "PvZ/PlayerInfo.h"
#include "PvZ/GameEventMgr.h"
#include "PvZ/DamageInfo.h"
#include "PvZ/PVZDB.h"
#include "PvZ/ProfileMgr.h"
#include "PvZ/WorldData.h"
#include "PvZ/WorldMapUtils.h"
#include "PvZ/MapEventItem.h"

static GameCenterProxy* s_gcp;

void Achievement::Queue(const std::string& i_achievement, float i_percent)
{
	s_gcp->QueueAchievement(i_achievement, i_percent);
}

void Achievement::SubmitAll()
{
	s_gcp->SubmitAchievements();
}

void Achievement::ResetAll()
{
	s_gcp->ResetAchievements();
}

void Achievement::ShowAll()
{
	s_gcp->ShowAchievementView();
}

void Achievement::SubmitOneShotAchievement(const std::string& i_achievement)
{
	AchievementDriverMgr::GetInstance().SubmitOneShotAchievement(i_achievement);
}

bool Achievement::IsNewAchievement(const std::string& i_achievement)
{
	return i_achievement == "king_nut" || i_achievement == "yarr_matey" || i_achievement == "giddyup";
}

/////////////// Callbacks ///////////////

static void OnGameWon()
{
	const LevelDefinition* level = gLawnApp->m_board->GetLevelDefinition();
	if (level && level->CompletionAchievement.size())
	{
		Achievement::Queue(level->CompletionAchievement, 100.0f);
		Achievement::ShowAll();
		if (Achievement::IsNewAchievement(level->CompletionAchievement))
			Achievement::SubmitOneShotAchievement(level->CompletionAchievement);
	}
}

static void OnExplorerTorchExtinguished(Zombie*)
{
	Achievement::Queue("no_smoking_ch", 100.0f);
	Achievement::ShowAll();
	Achievement::SubmitOneShotAchievement("no_smoking_ch");
}

#define AWARD(name) 	do { 		Achievement::Queue(name, 100.0f); 		Achievement::ShowAll(); 		Achievement::SubmitOneShotAchievement(name); 	} while (0)

// stand-in for a folded float(float) identity the game calls here
__attribute__((noinline)) static float PassThrough(float i_value)
{
	return i_value;
}

static void OnZombieDamageTaken(Zombie* i_zombie, const DamageInfo& i_damage)
{
	if (!i_damage.Instigator || !i_damage.Instigator->IsA<Plant>())
		return;
	Plant* plant = i_damage.Instigator->CastChecked<Plant>();
	if (plant->GetType()->TypeName == "lightningreed" && i_zombie->GetType()->TypeName == "chicken")
	{
		AWARD("fried_chicken_ch");
	}
	else if (plant->GetType()->TypeName == "potatomine" && PassThrough(*(float*)((char*)i_zombie + 0x280 /* m_hitpoints, private */)) == 0.0f)
	{
		AWARD("spudow_ch");
	}
	else if (i_zombie->GetType()->TypeName == "seagull")
	{
		for (size_t i = 0; i < i_damage.Conditions.size();)
		{
			const ZombieConditionInfo& condition = i_damage.Conditions[i].first;
			++i;
			if (condition.Condition == ZCONDITION_Buttered)
			{
				AWARD("pat_the_birdy_ch");
				break;
			}
		}
	}
}

static void OnZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow)
{
	if (i_zombie->GetType()->TypeName == "treasureyeti")
		AWARD("sasquash_ch");
}

static void OnPlantPlantfooded(Plant* i_plant)
{
	if (i_plant->GetType()->TypeName == "tallnut")
	{
		int count = 0;
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTS); it; ++it)
		{
			PlantPtr plant = *it;
			if (plant->GetType()->TypeName == "tallnut")
			{
				PlantFramework* framework = plant->GetPlantFramework<PlantFramework>();
				if (framework && PassThrough(*(float*)((char*)framework + 0x28 /* not in header */)) > 0.0f)
					count++;
			}
		}
		if (count > 3)
			AWARD("high_five_ch");
	}
}

static void OnPlantPlanted(Plant* i_plant)
{
	if (i_plant->GetType()->TypeName == "snapdragon")
	{
		int count = 0;
		for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTS); it; ++it)
		{
			PlantPtr plant = *it;
			if (plant->GetType()->TypeName == "snapdragon")
				count++;
		}
		if (count > 9)
		{
			Achievement::Queue("dragon_age_ch", 100.0f);
			Achievement::ShowAll();
		}
	}
	else if (i_plant->GetType()->TypeName == "wallnut")
	{
		if (gLawnApp->m_board->GetGridItemAt("railcart", i_plant->m_column, i_plant->m_row))
			AWARD("shell_on_wheels_ch");
	}
}

static void OnPlantUpgraded(Plant* i_plant, int i_level)
{
	if (i_plant->GetType()->TypeName == "peapod" && i_level == 4)
	{
		if (gLawnApp->m_board->GetGridItemAt("railcart", i_plant->m_column, i_plant->m_row))
			AWARD("pod_squad_ch");
	}
}

static void OnStarCompleted(const std::string& i_eventName)
{
	PlayerInfo* info = ProfileMgr::GetInstance().GetCurrentProfile();
	MapEventItem* event = WorldMapUtils::GetWorldDataForEdit()->FindEventByLevelName(i_eventName);
	if (info && event)
	{
		std::string world = event->m_worldDataPtr->m_worldName;
		if (info->GetStarsCompletedInWorld(world) >= info->GetStarsAvailableInWorld(world))
		{
			if (world == "egypt")
			{
				AWARD("eygpt_stars_ch");
			}
			else if (world == "pirate")
			{
				Achievement::Queue("pirate_stars_ch", 100.0f);
				Achievement::ShowAll();
			}
			else if (world == "cowboy")
			{
				AWARD("cowboy_stars_ch");
			}
		}
	}
}

/////////////// Init / Shutdown ///////////////

void Achievement::Init(GameCenterProxy* i_gcp)
{
	s_gcp = i_gcp;
	gMessageRouter->Subscribe(Message::GameWon, Sexy::MakeDelegate(OnGameWon));
	gMessageRouter->Subscribe(Message::ZombieDamageTaken, Sexy::MakeDelegate(OnZombieDamageTaken));
	gMessageRouter->Subscribe(Message::ZombieDied, Sexy::MakeDelegate(OnZombieDied));
	gMessageRouter->Subscribe(Message::ExplorerTorchExtinguished, Sexy::MakeDelegate(OnExplorerTorchExtinguished));
	gMessageRouter->Subscribe(Message::PlantPlantfooded, Sexy::MakeDelegate(OnPlantPlantfooded));
	gMessageRouter->Subscribe(Message::PlantPlanted, Sexy::MakeDelegate(OnPlantPlanted));
	gMessageRouter->Subscribe(Message::PlantUpgraded, Sexy::MakeDelegate(OnPlantUpgraded));
	gMessageRouter->Subscribe(Message::StarCompleted, Sexy::MakeDelegate(OnStarCompleted));
}

void Achievement::Shutdown()
{
	gMessageRouter->Unsubscribe(Message::GameWon, Sexy::MakeDelegate(OnGameWon));
	gMessageRouter->Unsubscribe(Message::ZombieDamageTaken, Sexy::MakeDelegate(OnZombieDamageTaken));
	gMessageRouter->Unsubscribe(Message::ZombieDied, Sexy::MakeDelegate(OnZombieDied));
	gMessageRouter->Unsubscribe(Message::ExplorerTorchExtinguished, Sexy::MakeDelegate(OnExplorerTorchExtinguished));
	gMessageRouter->Unsubscribe(Message::PlantPlantfooded, Sexy::MakeDelegate(OnPlantPlantfooded));
	gMessageRouter->Unsubscribe(Message::PlantPlanted, Sexy::MakeDelegate(OnPlantPlanted));
	gMessageRouter->Unsubscribe(Message::PlantUpgraded, Sexy::MakeDelegate(OnPlantUpgraded));
	gMessageRouter->Unsubscribe(Message::StarCompleted, Sexy::MakeDelegate(OnStarCompleted));
	s_gcp = nullptr;
}
