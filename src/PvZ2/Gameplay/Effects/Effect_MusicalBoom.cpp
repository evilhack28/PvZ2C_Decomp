//
//  Effect_MusicalBoom.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactGuitarTools.h"

Effect_MusicalBoom::Effect_MusicalBoom()
{
}

Effect_MusicalBoom::~Effect_MusicalBoom()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_MusicalBoom);

void Effect_MusicalBoom::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_MusicalBoom);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_MusicalBoom);
}
