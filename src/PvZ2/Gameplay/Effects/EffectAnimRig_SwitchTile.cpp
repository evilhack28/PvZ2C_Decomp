//
//  EffectAnimRig_SwitchTile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "EffectAnimRig_SwitchTile.h"

EffectAnimRig_SwitchTile::EffectAnimRig_SwitchTile()
{
}

EffectAnimRig_SwitchTile::~EffectAnimRig_SwitchTile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(EffectAnimRig_SwitchTile);

void EffectAnimRig_SwitchTile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EffectAnimRig_SwitchTile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(EffectAnimRig_SwitchTile);
}
