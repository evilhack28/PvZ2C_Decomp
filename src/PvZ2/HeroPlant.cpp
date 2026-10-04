//
//  HeroPlant.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "PvZ/HeroPlantConfig.h"

HeroPlantPropertySheet::HeroPlantPropertySheet()
	: SunCondtion(9999)
	, TimeCondtion(999)
	, RechargeTime(999)
	, RespawnTime(999)
	, RespawnSun(999)
{
}

HeroPlantPropertySheet::~HeroPlantPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HeroPlantPropertySheet);

void HeroPlantPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HeroPlantGradeUp);
		REFLECTION_CLASSBUILDER_FIELD(float, AttackUP);
		REFLECTION_CLASSBUILDER_FIELD(float, HealthUP);
		REFLECTION_CLASSBUILDER_FIELD(int, TalentPoints);
		REFLECTION_CLASSBUILDER_FIELD(int, ExpRequired);
	REFLECTION_CLASSBUILDER_END(HeroPlantGradeUp);

	REFLECTION_CLASSBUILDER_BEGIN(HeroPlantGradeRange);
		REFLECTION_CLASSBUILDER_FIELD(int, MinGrade);
		REFLECTION_CLASSBUILDER_FIELD(int, MaxGrade);
	REFLECTION_CLASSBUILDER_END(HeroPlantGradeRange);

	REFLECTION_CLASSBUILDER_BEGIN(HeroPlantTalent);
		REFLECTION_CLASSBUILDER_FIELD(std::string, TalentName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, TalentIcon);
		REFLECTION_CLASSBUILDER_FIELD(std::string, TalentDescription);
		REFLECTION_CLASSBUILDER_FIELD(int, MaxLevel);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, LevelUpCost);
	REFLECTION_CLASSBUILDER_END(HeroPlantTalent);

	REFLECTION_CLASSBUILDER_BEGIN(HeroPlantPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PlantName);
		REFLECTION_CLASSBUILDER_FIELD(int, SunCondtion);
		REFLECTION_CLASSBUILDER_FIELD(float, TimeCondtion);
		REFLECTION_CLASSBUILDER_FIELD(float, RechargeTime);
		REFLECTION_CLASSBUILDER_FIELD(float, RespawnTime);
		REFLECTION_CLASSBUILDER_FIELD(int, RespawnSun);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<HeroPlantGradeUp>, GradeUP);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<HeroPlantGradeRange>, GradeRange);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<HeroPlantTalent>, Talent);
	REFLECTION_CLASSBUILDER_END(HeroPlantPropertySheet);
}
