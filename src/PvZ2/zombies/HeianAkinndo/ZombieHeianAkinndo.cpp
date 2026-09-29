//
//  ZombieHeianAkinndo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAkinndo.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHeianAkinndo);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieHeianAkinndoProps);

void ZombieHeianAkinndoProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieHeianAkinndoProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, ProjectileBounceTime);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<ProjectilePropertySheet>>, BounceableProjectiles);
	REFLECTION_CLASSBUILDER_END(ZombieHeianAkinndoProps);
}
