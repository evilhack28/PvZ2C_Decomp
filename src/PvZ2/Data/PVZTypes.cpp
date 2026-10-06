//
//  PVZTypes.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVZTypes.h"

PVZTypes::PVZTypes()
{
}

PVZTypes::~PVZTypes()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PVZTypes);

void PVZTypes::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZTypes);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_END(PVZTypes);
}
