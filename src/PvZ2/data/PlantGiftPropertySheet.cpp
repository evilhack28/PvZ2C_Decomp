//
//  PlantGiftPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PlantGiftPropertySheet.h"

PlantGiftPropertySheet::~PlantGiftPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantGiftPropertySheet);

void PlantGiftPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantGiftBaseData);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantName);
		REFLECTION_CLASSBUILDER_FIELD(int, Weight);
	REFLECTION_CLASSBUILDER_END(PlantGiftBaseData);

	REFLECTION_CLASSBUILDER_BEGIN(PlantGiftPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantGiftBaseData>, GiftDatas);
	REFLECTION_CLASSBUILDER_END(PlantGiftPropertySheet);
}
