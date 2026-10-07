//
//  DinosaurRunner.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DinosaurRunner.h"

DinosaurRunner::~DinosaurRunner()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurRunner);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurRunnerPropertySheet);

void DinosaurRunnerPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinosaurRunnerPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(DinosaurPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(float, MovementSpeed);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, IdleDuration);
	REFLECTION_CLASSBUILDER_END(DinosaurRunnerPropertySheet);
}

#include "DinosaurRunner.h"
void DinosaurRunner::ScaredAway(BoardEntity* i_instigator)
{
	 DinosaurRunner::TurnLeftToRight();
}

bool DinosaurRunner::CanBeCharmed()
{
	return false;
}

void DinosaurRunner::Charm()
{
}
