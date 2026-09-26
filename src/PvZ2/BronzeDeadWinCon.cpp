//
//  BronzeDeadWinCon.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BronzeDeadWinCon.h"

BronzeDeadWinCon::BronzeDeadWinCon()
{
}

BronzeDeadWinCon::~BronzeDeadWinCon()
{
}

BronzeDeadWinConProperties::~BronzeDeadWinConProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BronzeDeadWinConProperties);

void BronzeDeadWinConProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BronzeDeadWinConProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

	REFLECTION_CLASSBUILDER_END(BronzeDeadWinConProperties);
}
