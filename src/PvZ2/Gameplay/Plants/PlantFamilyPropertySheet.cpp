//
//  PlantFamilyPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantFamilyPropertySheet.h"

PlantFamilyPropertySheet::PlantFamilyPropertySheet()
{
}

PlantFamilyPropertySheet::~PlantFamilyPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantFamilyPropertySheet);

void PlantFamilyPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantFamilyPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PlantList);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<SexyVector2>, PlantPosition);
	REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantBoost>, EnableFamilyBoost);
	REFLECTION_CLASSBUILDER_FIELD(PlantBoost, DefaultFamilyBoost);

	REFLECTION_CLASSBUILDER_END(PlantFamilyPropertySheet);
}
