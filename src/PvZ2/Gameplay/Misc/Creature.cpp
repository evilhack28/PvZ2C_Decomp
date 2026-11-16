//
//  Creature.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Creature.h"

void Creature::updateOverlayEffects()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Creature);

void Creature::registerForEvents()
{
}

#include "Creature.h"
void Creature::onIdleAnimationCycle(const std::string& i_animLabel, const std::string& i_nextAnimLabel, int i_cycleCount)
{
	 Creature::playIdleSound();
}

#include "Creature.h"
void Creature::onWalkAnimationCycle(const std::string& i_animLabel, const std::string& i_nextAnimLabel, int i_cycleCount)
{
	 Creature::playWalkSound();
}

#include "Creature.h"
void Creature::forceApplyConditionEffects()
{
	 Creature::updateSpeed();
}

#include "Creature.h"
void Creature::onDestroy()
{
	 Creature::ClearConditions();
}

#include "RealObject.h"
bool Creature::ShouldDrawShadow() const
{
	return RealObject::ShouldDrawShadow();
}
