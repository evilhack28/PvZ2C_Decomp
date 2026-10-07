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
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, (ArtifactBoostType)0);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_dmg, (ArtifactBoostType)1);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_duration, (ArtifactBoostType)2);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_control, (ArtifactBoostType)3);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_trigger_cd, (ArtifactBoostType)4);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_usetimes, (ArtifactBoostType)5);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_passive2_cd, (ArtifactBoostType)6);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(improved_passive1, (ArtifactBoostType)7);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(global_passive1, (ArtifactBoostType)8);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(bonus_starting_sun, (ArtifactBoostType)9);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(start_free_plant, (ArtifactBoostType)10);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(start_free_plant_new, (ArtifactBoostType)11);
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
