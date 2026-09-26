//
//  PresentType.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PresentType.h"

PresentType::~PresentType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PresentType);

void PresentType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PresentType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

	REFLECTION_CLASSBUILDER_FIELD(float, Scale);

	REFLECTION_CLASSBUILDER_END(PresentType);
}
