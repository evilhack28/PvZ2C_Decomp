//
//  ArtifactBoost.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArtifactBoost.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

ArtifactBoostPropertySheet::~ArtifactBoostPropertySheet()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(ArtifactBoostPropertySheet);

void ArtifactBoostPropertySheet::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(ArtifactBoostType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, Boost_None);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_dmg, Improved_Damage);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_duration, Improved_Duration);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_control, Improved_Control);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_trigger_cd, Improved_TriggerCD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_usetimes, Improved_UseTimes);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_passive2_cd, Improved_Passive2CD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_passive1, Improved_Passive1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(global_passive1, Global_Passive1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(bonus_starting_sun, Bonus_Starting_Sun);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(start_free_plant, Start_No_CD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(start_free_plant_new, Start_Free_Plant);
	REFLECTION_ENUMBUILDER_END(ArtifactBoostType);

	REFLECTION_CLASSBUILDER_BEGIN(ArtifactBoostValueInfo);
		REFLECTION_CLASSBUILDER_FIELD(float, Min);
		REFLECTION_CLASSBUILDER_FIELD(float, Max);
	REFLECTION_CLASSBUILDER_END(ArtifactBoostValueInfo);

	REFLECTION_CLASSBUILDER_BEGIN(ArtifactBoostPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, Name);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Description);
		REFLECTION_CLASSBUILDER_FIELD(ArtifactBoostType, Type);
		REFLECTION_CLASSBUILDER_FIELD(int, Rare);
		REFLECTION_CLASSBUILDER_FIELD(int, Id);
		REFLECTION_CLASSBUILDER_FIELD(ArtifactBoostValueInfo, ValueRange);
	REFLECTION_CLASSBUILDER_END(ArtifactBoostPropertySheet);

}

/////////////// Logic ///////////////

void ArtifactBoostPropertySheet::Sync(const NetworkArtifactBoostData& i_info)
{
	Id = i_info.Id;
	Type = i_info.Type;
	Rare = i_info.Rare;
	ValueRange = i_info.Value;
}
