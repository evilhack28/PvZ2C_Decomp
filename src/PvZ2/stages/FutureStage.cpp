//
//  FutureStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FutureStage.h"

FutureStage::FutureStage()
{
}

FutureStage::~FutureStage()
{
}

FutureStageProperties::~FutureStageProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FutureStage);

void FutureStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LinkedTilePropagationInfo);
		REFLECTION_CLASSBUILDER_FIELD(LinkedTileClass, Group);
	REFLECTION_CLASSBUILDER_END(LinkedTilePropagationInfo);

	REFLECTION_CLASSBUILDER_BEGIN(FutureStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<LinkedTileEntry>, m_linkedTiles);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<LinkedTilePropagationInfo>, m_linkedTilePropagations);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isBossFight);
	REFLECTION_CLASSBUILDER_END(FutureStage);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FutureStageProperties);

void FutureStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FutureStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, FactoryArmZombieTypes);
	REFLECTION_CLASSBUILDER_END(FutureStageProperties);
}
