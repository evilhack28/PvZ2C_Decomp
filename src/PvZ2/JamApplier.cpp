//
//  JamApplier.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "AudioMgr.h"
#include "EntityFinder.h"
#include "GridItemJammable.h"
#include "PVZDB.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "JamApplier.h"

namespace BoardHelpers
{
	int GetLevelBasedZombieTypeIndexByType(ZombieTypePtr i_zombieType);
	float ApplyLevelBasedModifierValue(float i_originalValue, int i_type, int i_subType = -1, int i_index = 0);
}

/////////////// JamApplier ///////////////

JamApplier::~JamApplier()
{
}

MusicalJamProperties* JamApplier::getMusicalJamProps() const
{
	return (MusicalJamProperties*)PVZDB::GetInstance().FindObjectByAlias<MusicalJamProperties>(PVZDB::TABLE_LEVELMODULES, RtName(L"MusicalJams")).GetObject();
}

void JamApplier::ChangeMusicGenre(const std::string& i_jam) const
{
	const MusicalJamProperties* props = getMusicalJamProps();
	std::map<std::string, std::string>::const_iterator it = props->JamsToMusicSwitches.find(i_jam);
	if (it != props->JamsToMusicSwitches.end())
	{
		gAudioMgr->SetSwitch("Music_Genre_Eighties", it->second.c_str(), NULL);
	}
}

void JamApplier::ApplyJamToJammableGridItem(GridItemJammable *item, const std::string& i_oldJam, const std::string& i_newJam) const
{
	if (!(i_oldJam == i_newJam) && item != NULL)
	{
		if (item->GetJamStyle() == i_newJam)
		{
			item->StartJamming();
		}
		else
		{
			item->StopJamming();
		}
	}
}

void JamApplier::RemoveMusicConditionsFrom(const std::string& i_theJam, Zombie *i_zombie) const
{
	const MusicalJamProperties* props = getMusicalJamProps();
	std::map<std::string, ZombieConditions>::const_iterator it = props->JamsToZombieConditionApplied.find(i_theJam);
	if (it != props->JamsToZombieConditionApplied.end())
	{
		if (it->second != ZCONDITION_Invalid)
		{
			if (i_zombie->HasCondition(it->second))
			{
				i_zombie->EndCondition(it->second);
			}
			else
			{
				i_zombie->StopJamming();
			}
		}
	}
}

void JamApplier::ApplyJamToAllJammableGridItems(const std::string& i_oldJam, const std::string& i_newJam) const
{
	if (i_oldJam == i_newJam)
	{
		return;
	}

	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntities(entities, ENTITYTYPE_GRIDITEM);
	std::vector<BoardEntity*>::iterator it = entities.begin();
	std::vector<BoardEntity*>::iterator end = entities.end();
	for (; it != end; ++it)
	{
		GridItemJammable* item = (*it)->Cast<GridItemJammable>();
		if (item != NULL)
		{
			ApplyJamToJammableGridItem(item, i_oldJam, i_newJam);
		}
	}
}

void JamApplier::ApplyMusicConditionsToAllZombies(const std::string& i_oldJam, const std::string& i_newJam) const
{
	if (i_oldJam == i_newJam)
	{
		return;
	}

	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntities(entities, ENTITYTYPE_ZOMBIE);
	std::vector<BoardEntity*>::iterator it = entities.begin();
	std::vector<BoardEntity*>::iterator end = entities.end();
	for (; it != end; ++it)
	{
		Zombie* zombie = (*it)->Cast<Zombie>();
		if (zombie->IsOnTeam(TEAM_ZOMBIES) && !zombie->IsDying())
		{
			RemoveMusicConditionsFrom(i_oldJam, zombie);
			ApplyMusicConditionsTo(i_newJam, zombie);
		}
	}
}

void JamApplier::ApplyMusicConditionsTo(const std::string& i_theJam, Zombie *i_zombie) const
{
	const MusicalJamProperties* props = getMusicalJamProps();
	std::map<std::string, ZombieConditions>::const_iterator it = props->JamsToZombieConditionApplied.find(i_theJam);
	if (it != props->JamsToZombieConditionApplied.end() && it->second != ZCONDITION_Invalid)
	{
		i_zombie->ApplyCondition(it->second, PVZ_EOT(), 0.0f, true);
	}

	int typeIndex = BoardHelpers::GetLevelBasedZombieTypeIndexByType(i_zombie->GetType());
	if (i_zombie->GetJamStyle() == i_theJam || BoardHelpers::ApplyLevelBasedModifierValue(1.0f, 14, typeIndex, 1) == 0.0f)
	{
		i_zombie->StartJamming();
	}
}

void JamApplier::PlayMusicGenreEnterEvent(const std::string& i_jam) const
{
	const MusicalJamProperties* props = getMusicalJamProps();
	std::map<std::string, std::string>::const_iterator it = props->JamsToMusicEnterEvents.find(i_jam);
	if (it != props->JamsToMusicEnterEvents.end())
	{
		gAudioMgr->SendEvent(it->second, NULL);
	}
}
