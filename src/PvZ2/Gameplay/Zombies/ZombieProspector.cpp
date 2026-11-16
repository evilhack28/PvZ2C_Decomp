//
//  ZombieProspector.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombiePropertySheet.h"
#include "ZombieProspector.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieProspector);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieProspectorProps);

void ZombieProspectorProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieProspectorProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

	REFLECTION_CLASSBUILDER_END(ZombieProspectorProps);
}
