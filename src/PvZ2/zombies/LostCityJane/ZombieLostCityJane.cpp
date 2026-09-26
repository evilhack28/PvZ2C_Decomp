//
//  ZombieLostCityJane.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieLostCityJane.h"

ZombieLostCityJaneProps::~ZombieLostCityJaneProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieLostCityJaneProps);

void ZombieLostCityJaneProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieLostCityJaneProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_FIELD(float, ProjectileBounceTime);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<ProjectilePropertySheet>>, BounceableProjectiles);

	REFLECTION_CLASSBUILDER_END(ZombieLostCityJaneProps);
}
