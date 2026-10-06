//
//  PVZ1ModePropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/ReflectionBuilder.h"

#include "PVZ1ModePropertySheet.h"
#include "PVZDB.h"

/////////////// PVZ1ModePropertySheet ///////////////

RT_CLASS_IMPLEMENT(PVZ1ModePropertySheet);

void PVZ1ModePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PVZ1ModePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, HowToPlayData1);
		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, HowToPlayData2);
		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, HowToPlayData3);
		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, NewPvPHowToPlayData);
		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, NewPvPArmyHowToPlayData);
		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, UnchartedHowToPlayData);
		REFLECTION_CLASSBUILDER_FIELD(HowToPlayScreenData, PlantWarsHowToPlayData);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PlantBannedList);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, PvZ1PlantList);
	REFLECTION_CLASSBUILDER_END(PVZ1ModePropertySheet);
}

PVZ1ModePropertySheet* PVZ1ModePropertySheet::GetProperties()
{
	return (PVZ1ModePropertySheet*)PVZDB::GetInstance().FindObjectByAlias<PVZ1ModePropertySheet>(PVZDB::TABLE_PVZ1_CONFIG, RtName(_S("PVZ1Config"))).GetObject();
}
