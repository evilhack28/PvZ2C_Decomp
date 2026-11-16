//
//  ZombieZoybeanPodBasic.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieZoybeanPodBasic.h"

ZombieZoybeanPodBasic::~ZombieZoybeanPodBasic()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieZoybeanPodBasic);

void ZombieZoybeanPodBasic::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieZoybeanPodBasic);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieBasic);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, m_plantFamilies);
	REFLECTION_CLASSBUILDER_END(ZombieZoybeanPodBasic);
}
