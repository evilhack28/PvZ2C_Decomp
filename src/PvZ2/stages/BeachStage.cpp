//
//  BeachStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "BeachStage.h"

#include "Board.h"
#include "BoardConstants.h"
#include "DamageInfo.h"
#include "EntityFinder.h"
#include "GameEventMgr.h"
#include "LawnApp.h"
#include "LevelModuleManager.h"
#include "ObjectTypeDirectory.h"
#include "ReflectionBuilder.h"
#include "Renderable.h"
#include "RenderQueue.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieType.h"

RT_CLASS_IMPLEMENT(BeachStage);
void BeachStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BeachStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(BeachStage);
}

RT_CLASS_IMPLEMENT(BeachStageProperties);
void BeachStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BeachStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(BeachStageProperties);
}

RT_CLASS_IMPLEMENT(BeachStageEventZombieSpawner);
void BeachStageEventZombieSpawner::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BeachStageEventZombieSpawner);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSpawnerAction);

	REFLECTION_CLASSBUILDER_END(BeachStageEventZombieSpawner);
}

RT_CLASS_IMPLEMENT(BeachStageEventZombieSpawnerProps);
void BeachStageEventZombieSpawnerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BeachStageEventZombieSpawnerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieSpawnerActionProps);

	REFLECTION_CLASSBUILDER_END(BeachStageEventZombieSpawnerProps);
}


void BeachStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &BeachStage::addForegroundToRenderQueue));
	getManager()->RegisterOnUpdate(Sexy::MakeDelegate(*this, &BeachStage::onUpdate));
}


void BeachStage::addForegroundToRenderQueue(RenderQueue* i_queue)
{
	i_queue->Add(RENDER_LAYER_STAGE_FOREGROUND, Sexy::MakeDelegate(*this, &BeachStage::renderForeground));
}


void BeachStage::SetLemonRainDelayTime(int iDelay)
{
	bool wasRunning = IsLemonRainEffectRuning();
	if (iDelay > 0 && !wasRunning)
		gMessageRouter->Post(Message::BeachWaveChangeColor, false);

	m_tLemonRainEffectRemainTime = iDelay;
}


void BeachStage::UpdateLemonRainEffect()
{
	if (!IsLemonRainEffectRuning())
		return;

	m_tLemonRainEffectRemainTime -= PVZ_Dt();
	m_tDtTime += PVZ_Dt();

	if (m_tLemonRainEffectRemainTime < 0.0f)
	{
		m_tLemonRainEffectRemainTime = 0.0f;
		m_tDtTime = 0.0f;
		gMessageRouter->Post(Message::BeachWaveChangeColor, true);
	}

	WaterDamge();
}


void BeachStage::onUpdate()
{
	UpdateLemonRainEffect();
}


void BeachStage::WaterDamge()
{
	if (m_tDtTime >= 2.0f)
	{
		m_tDtTime = 0.0f;

		std::vector<BoardEntity*> entities;
		EntityFinder::GetEntitiesTouchingRectangle(entities, ENTITYTYPE_ZOMBIE, gLawnApp->m_board->GetGridBoundingRect());

		for (BoardEntity*& entity : entities)
		{
			if (!entity)
				continue;

			Zombie* zombie = entity->GetPtr().IsValid() ? entity->Cast<Zombie>() : NULL;
			if (!zombie)
				continue;

			if (!zombie->IsInWater())
				continue;
			if (zombie->IsDying())
				continue;

			bool bleedingOut = zombie->IsBleedingOut();
			if (bleedingOut)
				continue;

			if (!zombie->IsOnScreen())
				continue;
			if (!zombie->IsOnOpposingTeam(TEAM_PLANTS))
				continue;

			DamageInfo damage(m_iWaterAcidDamge, DAMAGE_ACID, zombie->CalcGridPosition(), bleedingOut);
			zombie->TakeDamage(damage);
		}
	}
}

/////////////// BeachStageEventZombieSpawner ///////////////

void BeachStageEventZombieSpawner::WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random)
{
	const BeachStageEventZombieSpawnerProps* props = GetProps<BeachStageEventZombieSpawnerProps>();

	spawnWaveEffect();
	spawnZombies(props->GroupSize, i_waveNumber, i_random);

	m_nextGroupTime = PVZ_T() + props->TimeBetweenGroups;
	m_fullSpawnTime = PVZ_T() + props->TimeBeforeFullSpawn;

	if (!i_isFinal)
	{
		gLawnApp->m_board->ClearAdviceImmediately();
		gLawnApp->m_board->DisplayAdviceAgain(props->GetWaveStartMessage(), MESSAGE_STYLE_HUGE_WAVE, ADVICE_PRIORITY_MEDIUM);
	}

	notifyWaveEvents();
}


void BeachStageEventZombieSpawner::WaveUpdate(int i_waveNumber, MTRand& i_random)
{
	const BeachStageEventZombieSpawnerProps* props = GetProps<BeachStageEventZombieSpawnerProps>();

	if (m_zombiesSpawned < props->ZombieCount)
	{
		if (PVZ_T() > m_nextGroupTime)
		{
			spawnZombies(props->GroupSize, i_waveNumber, i_random);
			m_nextGroupTime = PVZ_T() + props->TimeBetweenGroups;
		}

		if (PVZ_T() > m_fullSpawnTime)
			WaveEnd(i_waveNumber, i_random);
	}
}


void BeachStageEventZombieSpawner::WaveEnd(int i_waveNumber, MTRand& i_random)
{
	const BeachStageEventZombieSpawnerProps* props = GetProps<BeachStageEventZombieSpawnerProps>();

	int remaining = props->ZombieCount - m_zombiesSpawned;
	if (remaining > 0)
		spawnZombies(remaining, i_waveNumber, i_random);
}


void BeachStageEventZombieSpawner::AddResourceRequirements(std::set<std::string>& io_resGroupNames)
{
	const BeachStageEventZombieSpawnerProps* props = GetProps<BeachStageEventZombieSpawnerProps>();

	const ZombieType* zombie = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(props->GetZombieName());
	zombie->AddInGameResourceRequirements(io_resGroupNames);
}


void BeachStageEventZombieSpawner::GetZombies(std::vector<const ZombieType*>& o_zombies)
{
	const BeachStageEventZombieSpawnerProps* props = GetProps<BeachStageEventZombieSpawnerProps>();

	const ZombieType* zombie = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(props->GetZombieName());
	for (int i = 0; i < props->ZombieCount; i++)
		o_zombies.push_back(zombie);
}


void BeachStageEventZombieSpawner::SetLoot(const std::vector<Loot>& i_loot)
{
	m_zombieLoot = i_loot;
}


void BeachStageEventZombieSpawner::initializeAction(MTRand& i_random, int i_waveNumber)
{
	m_fullSpawnTime = m_nextGroupTime = PVZ_EOT();
	m_zombiesSpawned = 0;
	m_nextRowToSpawnIn = i_random.Next() % BoardConstants::NUMBER_OF_ROWS();
}


int BeachStageEventZombieSpawner::calculateNextRowToSpawnIn()
{
	int row = m_nextRowToSpawnIn;
	m_nextRowToSpawnIn = (m_nextRowToSpawnIn + 17) % BoardConstants::NUMBER_OF_ROWS();
	return row;
}

/////////////// BeachStageEventZombieSpawnerProps ///////////////

std::string BeachStageEventZombieSpawnerProps::GetZombieName() const
{
	std::string name = ZombieName;
	if (name.empty())
		name = "beach";

	return name;
}


SexyString BeachStageEventZombieSpawnerProps::GetWaveStartMessage() const
{
	return ToWString(WaveStartMessage);
}


void BeachStageEventZombieSpawnerProps::GatherSpawnedZombieTypes(std::set<const ZombieType*>& o_zombies)
{
	o_zombies.insert(ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(GetZombieName()));
}
