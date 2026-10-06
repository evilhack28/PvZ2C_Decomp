//
//  DinoYoungBrontosaurus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DinoYoungBrontosaurus.h"

DinoYoungBrontosaurus::DinoYoungBrontosaurus()
{
}

DinoYoungBrontosaurus::~DinoYoungBrontosaurus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinoYoungBrontosaurus);

void DinoYoungBrontosaurus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinoYoungBrontosaurus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(DinosaurYounger);

	REFLECTION_CLASSBUILDER_END(DinoYoungBrontosaurus);
}

bool DinoYoungBrontosaurus::shouldDestroyWhenOffScreen()
{
	return false;
}
