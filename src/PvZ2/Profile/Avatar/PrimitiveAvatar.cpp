//
//  PrimitiveAvatar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "PlantNewAvatar.h"

PrimitiveAvatar::PrimitiveAvatar()
{
}

PrimitiveAvatar::~PrimitiveAvatar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PrimitiveAvatar);

void PrimitiveAvatar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PrimitiveAvatar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantName);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantBoost>, Boosts);
	REFLECTION_CLASSBUILDER_END(PrimitiveAvatar);
}
