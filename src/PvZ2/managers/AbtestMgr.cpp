//
//  AbtestMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AbtestMgr.h"
#include "EASquared.h"
#include "SocialShareMgr.h"

void AbtestMgr::Update()
{
}

AbtestMgr::~AbtestMgr()
{
}

AbtestMgr::AbtestMgr()
{
	m_checkActivityInfosFinished = 0;
	m_timeout = PVZ_EOT();
}

int AbtestMgr::GetActivityInfos()
{
	return EASquared::Instance().GetActivityInfos(m_activityInfos);
}

void AbtestMgr::CheckActivityInfos()
{
	EASquared::Instance().CheckActivityInfos();
	m_timeout = PVZ_T() + 30.0f;
}

int AbtestMgr::GetActivityAbtestId(int i_activityId)
{
	int id = 0;
	if (m_activityInfos.size() != 0)
	{
		std::map<int, int>::iterator it = m_activityInfos.find(i_activityId);
		if (it != m_activityInfos.end())
			id = it->second;
	}
	return id;
}

void AbtestMgr::InitTestData()
{
	std::pair<ShareType, int> p = std::make_pair((ShareType)10752, 1);
	m_activityInfos.insert(reinterpret_cast<std::pair<int, int>&&>(p));
}
