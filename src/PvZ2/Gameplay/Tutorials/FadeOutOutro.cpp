//
//  FadeOutOutro.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "FadeOutOutro.h"

FadeOutOutroProperties::~FadeOutOutroProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FadeOutOutroProperties);

void FadeOutOutroProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FadeOutOutroProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(OutroModuleProperties);

	REFLECTION_CLASSBUILDER_FIELD(std::string, DefaultMessage);
	REFLECTION_CLASSBUILDER_FIELD(Color, FadeColor);

	REFLECTION_CLASSBUILDER_END(FadeOutOutroProperties);
}
