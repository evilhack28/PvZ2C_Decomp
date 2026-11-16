//
//  PennyPerkBossBusterCannon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PennyPerkBossBusterCannon.h"

PennyPerkBossBusterCannon::PennyPerkBossBusterCannon()
{
}

PennyPerkBossBusterCannon::~PennyPerkBossBusterCannon()
{
}

PennyPerkBossBusterCannonProperties::PennyPerkBossBusterCannonProperties()
{
}

PennyPerkBossBusterCannonProperties::~PennyPerkBossBusterCannonProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkBossBusterCannon);

void PennyPerkBossBusterCannon::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkBossBusterCannon);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkTimedEffect);

	REFLECTION_CLASSBUILDER_END(PennyPerkBossBusterCannon);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkBossBusterCannonProperties);

void PennyPerkBossBusterCannonProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkBossBusterCannonProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, TimesBetweenStrikes);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ProjectilePropertySheet>, Projectile);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, Resources);
	REFLECTION_CLASSBUILDER_END(PennyPerkBossBusterCannonProperties);
}

#include "PennyPerkBossBusterCannon.h"
void PennyPerkBossBusterCannon::onUpdate()
{
	 PennyPerkBossBusterCannon::fireProjectiles();
}
