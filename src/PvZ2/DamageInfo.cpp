//
//  DamageInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "DamageInfo.h"

DamageInfo::DamageInfo()
	: Amount(0.f)
	, Instigator(NULL)
	, Flags(DAMAGE_NONE)
	, DamageGrid(Sexy::Point{-1, -1})
	, ResilienceDamage(ResilienceDamageInfo{1.0f, 0.0f})
	, Reserved58(false)
{
}

DamageInfo::DamageInfo(float i_amount, Sexy::Point dp, bool i_reserved58, ResilienceDamageInfo info)
	: Amount(i_amount)
	, Instigator(NULL)
	, Flags(DAMAGE_NONE)
	, DamageGrid(dp)
	, ResilienceDamage(info)
	, Reserved58(i_reserved58)
{
}

DamageInfo::DamageInfo(float i_amount, class BoardEntity* i_instigator, Sexy::Point dp, bool i_reserved58, ResilienceDamageInfo info)
	: Amount(i_amount)
	, Instigator(i_instigator)
	, Flags(DAMAGE_NONE)
	, DamageGrid(dp)
	, ResilienceDamage(info)
	, Reserved58(i_reserved58)
{
}

DamageInfo::DamageInfo(float i_amount, DamageTypeFlags i_flags, Sexy::Point dp, bool i_reserved58, ResilienceDamageInfo info)
	: Amount(i_amount)
	, Instigator(NULL)
	, Flags(i_flags)
	, DamageGrid(dp)
	, ResilienceDamage(info)
	, Reserved58(i_reserved58)
{
}

DamageInfo::DamageInfo(float i_amount, DamageTypeFlags i_flags, class BoardEntity* i_instigator, Sexy::Point dp, bool i_reserved58, ResilienceDamageInfo info)
	: Amount(i_amount)
	, Instigator(i_instigator)
	, Flags(i_flags)
	, DamageGrid(dp)
	, ResilienceDamage(info)
	, Reserved58(i_reserved58)
{
}

DamageInfo::DamageInfo(const DamageInfo&) = default;

DamageInfo::DamageInfo(DamageInfo&&) = default;

DamageInfo& DamageInfo::operator=(const DamageInfo&) = default;

DamageInfo& DamageInfo::operator=(DamageInfo&&) = default;

DamageInfo::~DamageInfo() = default;

int DamageInfo::GetFrostAmount() const
{
	if (!TestFlag(Flags, DAMAGE_ANY_FROST))
		return 0;

	if (TestFlag(Flags, DAMAGE_THAW_TINY))
		return -10;
	if (TestFlag(Flags, DAMAGE_THAW_MODERATE))
		return -25;
	if (TestFlag(Flags, DAMAGE_THAW_STAGE))
		return -100;
	if (TestFlag(Flags, DAMAGE_FROST_TINY))
		return 10;
	if (TestFlag(Flags, DAMAGE_FROST_MODERATE))
		return 25;
	if (TestFlag(Flags, DAMAGE_FROST_STAGE))
		return 100;

	if (!TestFlag(Flags, DAMAGE_FROST_FREEZE))
		return 0;
	return 350;
}


bool DamageInfo::ObtainZombieCondition(ZombieConditions zcValue) const
{
	for (auto& e : Conditions)
	{
		const auto& info = e.first;
		if (info.Condition == zcValue)
		{
			return true;
		}
	}

	return false;
}

void DamageInfo::AddCondition(ZombieConditions i_condition, float i_duration)
{
	ZombieConditionInfo conditionInfo;
	conditionInfo.Condition = i_condition;
	Conditions.push_back(std::pair<ZombieConditionInfo, float>(conditionInfo, i_duration));
}

void DamageInfo::AddCondition(ZombieConditionInfo i_condition, float i_duration)
{
	Conditions.push_back(std::pair<ZombieConditionInfo, float>(i_condition, i_duration));
}

void DamageInfo::AddCondition(GridItemConditions i_condition, float i_duration)
{
	RemoveGridItemCondition(i_condition);
	GridItem_Conditions.push_back(std::pair<GridItemConditions, float>(i_condition, i_duration));
}

void DamageInfo::RemoveZombieCondition(ZombieConditions zcValue)
{
	std::vector<std::pair<ZombieConditionInfo, float> >::iterator itr = Conditions.begin();
	for (; itr != Conditions.end(); )
	{
		const auto& info = itr->first;
		if (info.Condition == zcValue)
			Conditions.erase(itr);
		else
			++itr;
	}
}

void DamageInfo::RemoveGridItemCondition(GridItemConditions zcValue)
{
	std::vector<std::pair<GridItemConditions, float> >::iterator itr = GridItem_Conditions.begin();
	for (; itr != GridItem_Conditions.end(); )
	{
		const auto& info = itr->first;
		if (info == zcValue)
			GridItem_Conditions.erase(itr);
		else
			++itr;
	}
}
