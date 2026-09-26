//
//  CollectableNote.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableNote.h"

CollectableNoteType::~CollectableNoteType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableNoteType);

void CollectableNoteType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectableNoteType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_END(CollectableNoteType);
}
