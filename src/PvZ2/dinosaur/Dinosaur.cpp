//
//  Dinosaur.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Dinosaur.h"

Dinosaur::~Dinosaur()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurPropertySheet);

void DinosaurPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinosaurPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CreaturePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(int, ActivationGridX);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, Timeout);
	REFLECTION_CLASSBUILDER_END(DinosaurPropertySheet);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Dinosaur);

void Dinosaur::activate()
{
}
