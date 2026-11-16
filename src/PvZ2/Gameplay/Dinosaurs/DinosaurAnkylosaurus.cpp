//
//  DinosaurAnkylosaurus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DinosaurAnkylosaurus.h"

DinosaurAnkylosaurus::~DinosaurAnkylosaurus()
{
}

DinosaurAnkylosaurusPropertySheet::~DinosaurAnkylosaurusPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurAnkylosaurus);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurAnkylosaurusPropertySheet);

void DinosaurAnkylosaurusPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinosaurAnkylosaurusPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(DinosaurPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, PauseBetweenAttacks);
	REFLECTION_CLASSBUILDER_END(DinosaurAnkylosaurusPropertySheet);
}

bool DinosaurAnkylosaurus::ShouldDrawShadow() const
{
	return false;
}
