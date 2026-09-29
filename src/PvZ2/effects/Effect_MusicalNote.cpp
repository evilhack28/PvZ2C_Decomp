//
//  Effect_MusicalNote.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactGuitarTools.h"

Effect_MusicalNote::Effect_MusicalNote()
{
}

Effect_MusicalNote::~Effect_MusicalNote()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_MusicalNote);

void Effect_MusicalNote::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_MusicalNote);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_MusicalNote);
}

void Effect_MusicalNote::cancelTouch()
{
}
