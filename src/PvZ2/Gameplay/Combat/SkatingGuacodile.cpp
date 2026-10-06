//
//  SkatingGuacodile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SkatingGuacodile.h"

SkatingGuacodile::SkatingGuacodile()
{
}

SkatingGuacodile::~SkatingGuacodile()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SkatingGuacodile);

void SkatingGuacodile::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SkatingGuacodile);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RiverEntity);

	REFLECTION_CLASSBUILDER_END(SkatingGuacodile);
}

void SkatingGuacodile::onZombieDropHead(class Zombie * i_arg)
{
}
