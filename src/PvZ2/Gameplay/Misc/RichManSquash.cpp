//
//  RichManSquash.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RichManSquash.h"

void RichManSquash::InitView()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RichManSquash);

void RichManSquash::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RichManSquash);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RealObject);

	REFLECTION_CLASSBUILDER_END(RichManSquash);
}
