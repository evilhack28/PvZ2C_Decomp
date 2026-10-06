//
//  ZombieModifierModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModifierModule.h"
#include "Board.h"
#include "GameEventMgr.h"
#include "Zombie.h"

ZombieModifierModule::ZombieModifierModule()
{
}

ZombieModifierModule::~ZombieModifierModule()
{
}

void ZombieModifierModule::initializeModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieModifierModule);

void ZombieModifierModule::registerForEvents()
{
	gMessageRouter->Subscribe(Message::ZombieAddedToBoard, Sexy::MakeDelegate(*this, &ZombieModifierModule::onZombieSpawned));
}

void ZombieModifierModule::onZombieSpawned(Zombie* i_zombie)
{
	if (!getProps<ZombieModifierProperties>()->Speedy)
		return;

	i_zombie->ApplyCondition(ZCONDITION_SpeedUp4, PVZ_EOT(), 0.0f, true);
}
