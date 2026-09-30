//
//  JoustSchedule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustSchedule.h"

JoustSchedule::~JoustSchedule()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustSchedule);

void JoustSchedule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustTournamentDefinition);
		REFLECTION_CLASSBUILDER_FIELD(long, StartDate);
	REFLECTION_CLASSBUILDER_END(JoustTournamentDefinition);

	REFLECTION_CLASSBUILDER_BEGIN(JoustSchedule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<JoustTournamentDefinition>, TournamentDefinitions);
	REFLECTION_CLASSBUILDER_END(JoustSchedule);
}
