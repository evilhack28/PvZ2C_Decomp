//
//  UnchartedBoost.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "UnchartedBoost.h"

#include "ReflectionBuilder.h"
#include "TodLib/TodStringFile.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(UnchartedBoostPropertySheet);

void UnchartedBoostPropertySheet::StaticClassInit()
{
	REFLECTION_ENUMBUILDER_BEGIN(UnchartedBoostType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(none, U_Boost_None);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_sun_reduced, U_Boost_Sun_Reduced);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_plant_cd_reduced, U_Boost_Plant_CD_Reduced);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_hp, U_Boost_HP);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_atk_speed, U_Boost_ATK_Speed);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_damage, U_Boost_Damage);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_sun_add, U_Boost_Sun_Add);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_hero_plant_material, U_Boost_Hero_Plant_Material);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_bonus_damage, U_Boost_Bonus_Damage);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_die_explode, U_Boost_Die_Explode);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_global_damage, U_Boost_Global_Damage);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_die_reset_cd, U_Boost_Die_Reset_CD);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_damage_by_sun, U_Boost_Damage_By_Sun);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_plantfood_atk_speed, U_Boost_Plantfood_ATK_Speed);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_damage_multiplier, U_Boost_Damage_Multiplier);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_take_damage_plantfood, U_Boost_Take_Damage_Plantfood);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_multiplier_sun, U_Boost_Multiplier_Sun);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_hero_plant, U_Boost_Hero_Plant);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_hero_plant_execute, U_Boost_Hero_Plant_Execute);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_hero_plant_energy, U_Boost_Hero_Plant_Energy);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_hero_plant_kill_explode, U_Boost_Hero_Plant_Kill_Explode);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(boost_plant_packet_add, U_Boost_Plant_Packet_Add);
	REFLECTION_ENUMBUILDER_END(UnchartedBoostType);

	REFLECTION_ENUMBUILDER_BEGIN(ValidBoostType);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(instant_kill, ValidBoostType_InstantKill);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(physical, ValidBoostType_Physical);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(poison, ValidBoostType_Poison);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(lightning, ValidBoostType_Lightning);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(magic, ValidBoostType_Magic);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(frost, ValidBoostType_Frost);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(flame, ValidBoostType_Flame);
		REFLECTION_ENUMBUILDER_MEMBER_RENAME(all, ValidBoostType_All);
	REFLECTION_ENUMBUILDER_END(ValidBoostType);

	REFLECTION_CLASSBUILDER_BEGIN(UnchartedBoostPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::string, TypeName);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Description);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Name);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, Values);
		REFLECTION_CLASSBUILDER_FIELD(UnchartedBoostType, Type);
		REFLECTION_CLASSBUILDER_FIELD(ValidBoostType, ValidType);
		REFLECTION_CLASSBUILDER_FIELD(int, UseCount);
	REFLECTION_CLASSBUILDER_END(UnchartedBoostPropertySheet);
}

/////////////// Accessors ///////////////

SexyString UnchartedBoostPropertySheet::GetDescription()
{
	return TodStringTranslate(Sexy::StringToSexyString(Description));
}

SexyString UnchartedBoostPropertySheet::GetName()
{
	return TodStringTranslate(Sexy::StringToSexyString(Name));
}
