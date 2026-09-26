//
//  Collection.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Collection.h"

CollectionType::CollectionType()
{
}

CollectionType::~CollectionType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectionType);

void CollectionType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectionType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<std::string>>, DesStuff);
	REFLECTION_CLASSBUILDER_FIELD(int, MaxRare);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<PlantBoost>>, Boosts);

	REFLECTION_CLASSBUILDER_END(CollectionType);
}
