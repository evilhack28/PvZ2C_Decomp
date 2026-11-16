//
//  ZombiePumpkinKnightGhost.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePumpkinKnightGhost.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiePumpkinKnightGhost);

bool ZombiePumpkinKnightGhost::moveToDestination(const float i_destX, const float i_destY)
{
	return true;
}

void ZombiePumpkinKnightGhost::onZombieInitialize()
{
}

#include "Zombie.h"
void ZombiePumpkinKnightGhost::onDestroy()
{
	 Zombie::onDestroy();
}
