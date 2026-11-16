//
//  CardGameBoardConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CardGameBoardConfig.h"

CardGameBoardConfig::CardGameBoardConfig()
{
}

CardGameBoardConfig::~CardGameBoardConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CardGameBoardConfig);

void CardGameBoardConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(TagColorValue);
	REFLECTION_CLASSBUILDER_END(TagColorValue);

	REFLECTION_CLASSBUILDER_BEGIN(TagData);
		REFLECTION_CLASSBUILDER_FIELD(TagColorValue, Color);
	REFLECTION_CLASSBUILDER_END(TagData);

	REFLECTION_CLASSBUILDER_BEGIN(CardGameBoardConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA std::string>, StringMaps);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<TagData>, Tags);
	REFLECTION_CLASSBUILDER_END(CardGameBoardConfig);
}
