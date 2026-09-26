//
//  GridItemCardGameZombieActionData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemCardGameZombie.h"

GridItemCardGameZombieActionData::~GridItemCardGameZombieActionData()
{
}

GridItemCardGameZombieActionData::GridItemCardGameZombieActionData()
{
	IntentionType = ZombieIntention_Invalid;
	Ratio = 100;
	IntentionRound = 0;
	CoolDownRound = 0;
	Desc = "";
	ShowIntention = false;
}

GridItemCardGameZombieActionData::GridItemCardGameZombieActionData(const GridItemCardGameZombieActionData& i_other)
	: IntentionType(i_other.IntentionType)
	, Ratio(i_other.Ratio)
	, IntentionRound(i_other.IntentionRound)
	, CoolDownRound(i_other.CoolDownRound)
	, Desc(i_other.Desc)
	, ShowIntention(i_other.ShowIntention)
{
}

GridItemCardGameZombieActionData::GridItemCardGameZombieActionData(GridItemCardGameZombieActionData&& i_other)
	: IntentionType(i_other.IntentionType)
	, Ratio(i_other.Ratio)
	, IntentionRound(i_other.IntentionRound)
	, CoolDownRound(i_other.CoolDownRound)
	, Desc(static_cast<std::string&&>(i_other.Desc))
	, ShowIntention(i_other.ShowIntention)
{
}

GridItemCardGameZombieActionData& GridItemCardGameZombieActionData::operator=(const GridItemCardGameZombieActionData& i_other)
{
	IntentionType = i_other.IntentionType;
	Ratio = i_other.Ratio;
	IntentionRound = i_other.IntentionRound;
	CoolDownRound = i_other.CoolDownRound;
	Desc = i_other.Desc;
	ShowIntention = i_other.ShowIntention;
	return *this;
}
