//
//  ZombieExplorer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieExplorer.h"
#include "ZombiePropertySheet.h"

ZombieExplorerProps::~ZombieExplorerProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieExplorer);

void ZombieExplorer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieExplorer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Zombie);

	REFLECTION_CLASSBUILDER_END(ZombieExplorer);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieExplorerProps);

void ZombieExplorerProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieExplorerProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, MaxTorchReach);
	REFLECTION_CLASSBUILDER_END(ZombieExplorerProps);
}
