//
//  EffectAnimRig_IceHole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemIceHole.h"

EffectAnimRig_IceHole::EffectAnimRig_IceHole()
{
}

EffectAnimRig_IceHole::~EffectAnimRig_IceHole()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_IceHole);

void EffectAnimRig_IceHole::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_IceHole);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_IceHole);
}
