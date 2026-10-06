//
//  LightningCloud.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LightningCloud.h"

LightningCloud::~LightningCloud()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(LightningCloud);

void LightningCloud::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LightningCloud);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CloudBase);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_finishTime);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_canMove);
	REFLECTION_CLASSBUILDER_END(LightningCloud);
}
