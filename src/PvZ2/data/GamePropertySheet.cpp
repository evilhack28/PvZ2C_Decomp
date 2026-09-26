//
//  GamePropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GamePropertySheet.h"

GamePropertySheet::~GamePropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GamePropertySheet);

void GamePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GamePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_END(GamePropertySheet);
}
