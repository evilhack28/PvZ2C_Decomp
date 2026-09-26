//
//  CreaturePropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CreaturePropertySheet.h"

CreaturePropertySheet::~CreaturePropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CreaturePropertySheet);

void CreaturePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CreaturePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_FIELD(int32, GridHeight);
	REFLECTION_CLASSBUILDER_FIELD(SexyVector3, ShadowOffset);
	REFLECTION_CLASSBUILDER_FIELD(Point, GridExtents);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<BoardEntityStat>, ZombieStats);

	REFLECTION_CLASSBUILDER_END(CreaturePropertySheet);
}
