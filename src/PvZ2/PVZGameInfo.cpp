//
//  PVZGameInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PVZGameInfo.h"

PVZGameInfo::~PVZGameInfo()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZGameInfo);

void PVZGameInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZGameInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(PVZGameInfo);
}
