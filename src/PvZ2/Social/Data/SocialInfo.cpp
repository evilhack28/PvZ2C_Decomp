//
//  SocialInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "SocialInfo.h"

SocialInfo::SocialInfo()
{
}

SocialInfo::~SocialInfo()
{
}

std::vector<int32>& SocialInfo::GetBorrowedPlantList()
{
	return m_borrowedplantList;
}

void SocialInfo::AddBorrowedPlantList(int32 userId)
{
	m_borrowedplantList.push_back(userId);
}

std::vector<FriendInfo>& SocialInfo::GetFriendList()
{
	return m_friendList;
}

SexyString SocialInfo::GetFriendNameById(int32 i_userId)
{
	size_t i = 0;
	while (i < m_friendList.size())
	{
		FriendInfo& f = m_friendList[i];
		i++;
		if (f.userId == i_userId)
			return f.name;
	}
	return L"";
}

void SocialInfo::SetFriendLeftTime(int32 i_userId, int i_time)
{
	for (size_t i = 0; i < m_friendList.size(); i++)
	{
		if (m_friendList[i].userId == i_userId)
			m_friendList[i].giftLeftTime = i_time;
	}
}

std::vector<int32>& SocialInfo::GetReceivedSunList()
{
	return m_receivesunList;
}

void SocialInfo::RemoveUsedFriendSunList(int32 userId)
{
	m_receivesunList.erase(std::remove(m_receivesunList.begin(), m_receivesunList.end(), userId), m_receivesunList.end());
}

void SocialInfo::GetGameRank(std::vector<GameRankInfo> &i_info, int i_star)
{
	if ((unsigned)i_star < GAME_RANK_STAR_COUNT)
		i_info = m_gameRankList[i_star];
}

std::vector<int32> SocialInfo::getUsedSunList()
{
	return m_usedsunList;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SocialInfo);

void SocialInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FriendInfo);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, userId, ui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(SexyString, name, n);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, imageId, imgi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, star, s);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, giftLeftTime, glt);
	REFLECTION_CLASSBUILDER_END(FriendInfo);

	REFLECTION_CLASSBUILDER_BEGIN(SocialInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<FriendInfo>, m_friendList, fl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int32>, m_borrowedplantList, bl);
	REFLECTION_CLASSBUILDER_END(SocialInfo);
}
