//
//  ProtectTheGridItemChallenge.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ProtectTheGridItemChallenge.h"

ProtectTheGridItemChallengeProperties::~ProtectTheGridItemChallengeProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ProtectTheGridItemChallengeProperties);

void ProtectTheGridItemChallengeProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ProtectedGridItemEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, GridItemType);
	REFLECTION_CLASSBUILDER_END(ProtectedGridItemEntry);

	REFLECTION_CLASSBUILDER_BEGIN(ProtectTheGridItemChallengeProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(int, MustProtectCount);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ProtectedGridItemEntry>, GridItems);
	REFLECTION_CLASSBUILDER_END(ProtectTheGridItemChallengeProperties);
}
