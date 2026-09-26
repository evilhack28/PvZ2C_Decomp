//
//  ZombiesDeadWinCon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombiesDeadWinCon.h"

ZombiesDeadWinCon::ZombiesDeadWinCon()
{
}

ZombiesDeadWinCon::~ZombiesDeadWinCon()
{
}

ZombiesDeadWinConProperties::~ZombiesDeadWinConProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombiesDeadWinConProperties);

void ZombiesDeadWinConProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombiesDeadWinConProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(ZombiesDeadWinConProperties);
}

#include "ZombiesDeadWinCon.h"
bool ZombiesDeadWinCon::checkWin()
{
	return ZombiesDeadWinCon::Check();
}
