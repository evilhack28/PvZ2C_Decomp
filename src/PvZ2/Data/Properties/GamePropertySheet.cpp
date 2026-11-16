//
//  GamePropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GamePropertySheet.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

GamePropertySheet::~GamePropertySheet()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(GamePropertySheet);

void GamePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GamePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_END(GamePropertySheet);
}
