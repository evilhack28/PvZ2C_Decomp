//
//  ProbabilityTypeContainer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ProbabilityTypeContainer.h"

ProbabilityTypeContainer::~ProbabilityTypeContainer()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ProbabilityTypeContainer);

void ProbabilityTypeContainer::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ProbabilityTypeContainer);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<ProbabilityTypeRecord>, Entries);

	REFLECTION_CLASSBUILDER_END(ProbabilityTypeContainer);
}
