//
//  Effect_GroundEffectTide.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Effect_GroundEffects.h"

Effect_GroundEffectTide::Effect_GroundEffectTide()
{
}

Effect_GroundEffectTide::~Effect_GroundEffectTide()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_GroundEffectTide);

void Effect_GroundEffectTide::onDraw(Graphics* i_g)
{
	updateAttachOffset();
	Effect_BeachWaterWave::onDraw(i_g);
}
