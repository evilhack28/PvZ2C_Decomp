//
//  BronzeModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "BronzeModule.h"

void BronzeModule::unregisterForEvents()
{
}

BronzeModule::~BronzeModule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(BronzeModule);

void BronzeModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(BronzeModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_bronzeStumpCount);
		REFLECTION_CLASSBUILDER_FIELD(float, m_leftTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<class UIWidget>, m_counterWidget);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<class GridItemBronze> >, m_bronzeStumpList);
	REFLECTION_CLASSBUILDER_END(BronzeModule);
}
