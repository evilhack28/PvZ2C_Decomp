//
//  ZombieAction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieAction.h"
#include "ZombiePropertySheet.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieActionHandler);

void ZombieActionHandler::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieActionHandler);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_done);
	REFLECTION_CLASSBUILDER_END(ZombieActionHandler);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieActionDefinition);

bool ZombieActionDefinition::TryStartAction(ZombieActionDefinitionPtr i_arg0, class ZombieWithActions* i_arg1) const
{
	return false;
}
