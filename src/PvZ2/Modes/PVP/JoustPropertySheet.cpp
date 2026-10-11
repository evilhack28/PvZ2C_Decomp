//
//  JoustPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "JoustPropertySheet.h"
#include "PVZDB.h"

JoustPropertySheet::~JoustPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(JoustPropertySheet);

void JoustPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PredefinedLoadoutEntry);
		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantType);
		REFLECTION_CLASSBUILDER_FIELD(int, PlantLevel);
		REFLECTION_CLASSBUILDER_FIELD(bool, IsImitater);
	REFLECTION_CLASSBUILDER_END(PredefinedLoadoutEntry);

	REFLECTION_CLASSBUILDER_BEGIN(JoustPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<PredefinedLoadoutEntry>>, PredefinedLoadouts);
		REFLECTION_CLASSBUILDER_FIELD(JoustHowToPlayScreenData, HowToPlayData);
	REFLECTION_CLASSBUILDER_END(JoustPropertySheet);
}

/////////////// Logic ///////////////

JoustPropertySheet* JoustPropertySheet::GetProperties()
{
	return (JoustPropertySheet*)PVZDB::GetInstance().FindObjectByAlias<JoustPropertySheet>(PVZDB::TABLE_JOUST_CONFIG, RtName(L"JoustConfig")).GetObject();
}
