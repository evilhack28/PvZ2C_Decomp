//
//  CardGameBoardModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "CardGameBoardModule.h"

CardGameBoardModule::CardGameBoardModule()
{
}

CardGameBoardModule::~CardGameBoardModule()
{
}

CardGameBoardModuleProperties::CardGameBoardModuleProperties()
{
}

CardGameBoardModuleProperties::~CardGameBoardModuleProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardGameBoardModule);

void CardGameBoardModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardGameBoardModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(CardGameBoardModule);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardGameBoardModuleProperties);

void CardGameBoardModuleProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CardGameBoardModuleProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(float, BoardEntityScale);
	REFLECTION_CLASSBUILDER_END(CardGameBoardModuleProperties);
}
