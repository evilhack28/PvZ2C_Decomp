//
//  NetworkCacheQueue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "NetworkCacheQueue.h"

#include "ReflectionBuilder.h"
#include <algorithm>
#include "GameEventMgr.h"
#include "Plant.h"
#include "Board.h"
#include "LawnApp.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"

static bool operator==(const NetworkItemInfo& a, const NetworkItemInfo& b)
{
	return a.m_count == b.m_count && a.m_objectId == b.m_objectId;
}

RT_CLASS_IMPLEMENT(NetworkCacheQueue);

/////////////// Reflection ///////////////

void NetworkCacheQueue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NetworkCacheFragement);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, fragmentId, pi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, fragmentCount, fc);
	REFLECTION_CLASSBUILDER_END(NetworkCacheFragement);

	REFLECTION_CLASSBUILDER_BEGIN(NetworkCachePendant);
		REFLECTION_CLASSBUILDER_FIELD(int32, id);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, objectId, oi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, level, lv);
	REFLECTION_CLASSBUILDER_END(NetworkCachePendant);

	REFLECTION_CLASSBUILDER_BEGIN(NetworkCacheObjects);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, objectId, oi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, quantity, q);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, source, src);
	REFLECTION_CLASSBUILDER_END(NetworkCacheObjects);

	REFLECTION_CLASSBUILDER_BEGIN(NetworkCacheQueue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NetworkCacheObjects>, m_cachedObjects, chojs);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NetworkCacheFragement>, m_vecPlantFragments, vfts);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NetworkCacheFragement>, m_vecDressFragments, vpds);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NetworkCacheFragement>, m_vecPendantFragments, vpfs);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NetworkCachePendant>, m_vecPendants, vps);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<NetworkItemInfo>, m_vecItemFragments, vits);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<int>, m_vecAddFreeGemIds, vafg);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<std::string>, m_vecFreeGemMarks, vfgm);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_iPlayerId, pi);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int64, m_llReqSeq, rs);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_isFlushing, fl);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sUserID, ui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sSK, cqsk);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sDefineID, cqdfid);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sSinaAccessToken, sat);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sSinaUserID, sui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sSinaExpireDate, sed);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sWechatAccessToken, wat);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sWechatUserID, wui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sWechatExpireDate, wed);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sTencentAccessToken, tat);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sTencentUserID, tui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sTencentExpireDate, ted);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_isSyncProfile, sp);
	REFLECTION_CLASSBUILDER_END(NetworkCacheQueue);

}


/////////////// Accessors ///////////////

std::vector<NetworkCacheObjects>& NetworkCacheQueue::getCachedObjects() { return m_cachedObjects; }
std::vector<NetworkCacheFragement>& NetworkCacheQueue::getPlantFragmentCache() { return m_vecPlantFragments; }
std::vector<NetworkCacheFragement>& NetworkCacheQueue::getDressFragmentCache() { return m_vecDressFragments; }
std::vector<NetworkCacheFragement>& NetworkCacheQueue::getPendantFragmentCache() { return m_vecPendantFragments; }
std::vector<NetworkCachePendant>& NetworkCacheQueue::getPendantCache() { return m_vecPendants; }
std::vector<NetworkItemInfo>& NetworkCacheQueue::getItemFragmentCache() { return m_vecItemFragments; }

void NetworkCacheQueue::setUserID(const std::string& userID) { m_sUserID = userID; }
std::string NetworkCacheQueue::getUserID() { return m_sUserID; }
void NetworkCacheQueue::setSessionKey(const std::string& sessionKey) { m_sSK = sessionKey; }
std::string NetworkCacheQueue::getSessionKey() { return m_sSK; }
void NetworkCacheQueue::setDefineID(const std::string& defineID) { m_sDefineID = defineID; }
std::string NetworkCacheQueue::getDefineID() { return m_sDefineID; }
std::string NetworkCacheQueue::getSinaAccessToken() { return m_sSinaAccessToken; }
void NetworkCacheQueue::setSinaUserID(const std::string& userID) { m_sSinaUserID = userID; }
std::string NetworkCacheQueue::getSinaUserID() { return m_sSinaUserID; }
std::string NetworkCacheQueue::getWechatAccessToken() { return m_sWechatAccessToken; }
void NetworkCacheQueue::setWechatUserID(const std::string& userID) { m_sWechatUserID = userID; }
std::string NetworkCacheQueue::getWechatUserID() { return m_sWechatUserID; }
std::string NetworkCacheQueue::getTencentAccessToken() { return m_sTencentAccessToken; }
void NetworkCacheQueue::setTencentUserID(const std::string& userID) { m_sTencentUserID = userID; }
std::string NetworkCacheQueue::getTencentUserID() { return m_sTencentUserID; }

void NetworkCacheQueue::clearItemFragmentCache() { m_vecItemFragments.clear(); }
void NetworkCacheQueue::clearPlantFragmentCache() { m_vecPlantFragments.clear(); }


/////////////// Flush ///////////////

bool NetworkCacheQueue::isItemCacheEmpty()
{
	return m_vecItemFragments.size() == 0 && m_vecPlantFragments.size() == 0;
}

void NetworkCacheQueue::insertPendantCache(int pendantId, int objectId, int level)
{
	NetworkCachePendant p;
	p.id = pendantId;
	p.objectId = objectId;
	p.level = level;
	m_vecPendants.push_back(p);
}

void NetworkCacheQueue::onFlushPlantFinish(int needFlush)
{
	if (m_isFlushing && needFlush == 1)
		m_vecPlantFragments.clear();
	if (isNetCacheEmpty())
		m_isFlushing = false;
}

void NetworkCacheQueue::onFlushAddFreeGemFinish(bool success)
{
	if (m_isFlushing)
		m_vecAddFreeGemIds.clear();
	if (isNetCacheEmpty())
		m_isFlushing = false;
}

void NetworkCacheQueue::onFlushedCachedObjects(bool success)
{
	if (m_isFlushing)
		m_cachedObjects.clear();
	if (isNetCacheEmpty())
		m_isFlushing = false;
}

bool NetworkCacheQueue::isNetCacheEmpty()
{
	return m_cachedObjects.size() == 0 && m_vecPlantFragments.size() == 0 && m_vecDressFragments.size() == 0
		&& m_vecAddFreeGemIds.size() == 0 && m_vecPendantFragments.size() == 0 && m_vecPendants.size() == 0;
}

void NetworkCacheQueue::onFlushAvatarFinish(int needFlush)
{
	if (m_isFlushing && needFlush == 1)
		m_vecDressFragments.clear();
	if (isNetCacheEmpty())
		m_isFlushing = false;
}

void NetworkCacheQueue::onFlushPendantFinish(int needFlush)
{
	if (m_isFlushing && needFlush == 1)
	{
		m_vecPendantFragments.clear();
		m_vecPendants.clear();
	}
	if (isNetCacheEmpty())
		m_isFlushing = false;
}

/////////////// Insert ///////////////

void NetworkCacheQueue::insertAddFreeGemId(int actid)
{
	for (std::vector<int>::iterator it = m_vecAddFreeGemIds.begin(); it != m_vecAddFreeGemIds.end(); ++it)
	{
		if (*it == actid)
			return;
	}
	m_vecAddFreeGemIds.push_back(actid);
}

void NetworkCacheQueue::insertPlantFragmentCache(int fragmentId, int count)
{
	std::vector<NetworkCacheFragement>::iterator it;
	for (it = m_vecPlantFragments.begin(); it != m_vecPlantFragments.end(); ++it)
	{
		if (it->fragmentId == fragmentId)
		{
			it->fragmentCount += count;
			return;
		}
	}
	NetworkCacheFragement f;
	f.fragmentId = fragmentId;
	f.fragmentCount = count;
	m_vecPlantFragments.push_back(f);
}

void NetworkCacheQueue::insertDressFragmentCache(int fragmentId, int count)
{
	std::vector<NetworkCacheFragement>::iterator it;
	for (it = m_vecDressFragments.begin(); it != m_vecDressFragments.end(); ++it)
	{
		if (it->fragmentId == fragmentId)
		{
			it->fragmentCount += count;
			return;
		}
	}
	NetworkCacheFragement f;
	f.fragmentId = fragmentId;
	f.fragmentCount = count;
	m_vecDressFragments.push_back(f);
}

void NetworkCacheQueue::insertPendantFragmentCache(int fragmentId, int count)
{
	std::vector<NetworkCacheFragement>::iterator it;
	for (it = m_vecPendantFragments.begin(); it != m_vecPendantFragments.end(); ++it)
	{
		if (it->fragmentId == fragmentId)
		{
			it->fragmentCount += count;
			return;
		}
	}
	NetworkCacheFragement f;
	f.fragmentId = fragmentId;
	f.fragmentCount = count;
	m_vecPendantFragments.push_back(f);
}

bool NetworkCacheQueue::isWorldFreeGemAlreadyGet(const std::string& bonusName)
{
	for (size_t i = 0; i < m_vecFreeGemMarks.size(); i++)
	{
		if (m_vecFreeGemMarks[i] == bonusName)
			return true;
	}
	return false;
}

void NetworkCacheQueue::addWorldFreeGemsGet(const std::string& bonusName)
{
	for (std::vector<std::string>::iterator it = m_vecFreeGemMarks.begin(); it != m_vecFreeGemMarks.end(); ++it)
	{
		if (*it == bonusName)
			return;
	}
	m_vecFreeGemMarks.push_back(bonusName);
}

void NetworkCacheQueue::removeWorldFreeGemsGet(const std::string& bonusName)
{
	for (std::vector<std::string>::iterator it = m_vecFreeGemMarks.begin(); it != m_vecFreeGemMarks.end(); ++it)
	{
		if (*it == bonusName)
		{
			m_vecFreeGemMarks.erase(it);
			return;
		}
	}
}

void NetworkCacheQueue::insertCachedObject(int i_objectId, int i_quantity, std::string i_src)
{
	{
		std::vector<NetworkCacheObjects>::iterator it = m_cachedObjects.begin();
		std::vector<NetworkCacheObjects>::iterator end = m_cachedObjects.end();
		for (; it != end; ++it)
		{
			if ((*it).objectId == i_objectId && (*it).source == i_src)
			{
				(*it).quantity += i_quantity;
				return;
			}
		}
	}
	NetworkCacheObjects o;
	o.objectId = i_objectId;
	o.quantity = i_quantity;
	o.source = i_src;
	m_cachedObjects.push_back(o);
}

void NetworkCacheQueue::insertCachedObject(std::vector<NetworkCacheObjects> i_needCachedObjects)
{
	std::vector<NetworkCacheObjects>::iterator it = i_needCachedObjects.begin();
	std::vector<NetworkCacheObjects>::iterator end = i_needCachedObjects.end();
	for (; it != end; ++it)
		insertCachedObject((*it).objectId, (*it).quantity, (*it).source);
}

void NetworkCacheQueue::insertItemFragmentCache(const std::vector<NetworkItemInfo>& i_infos)
{
	m_vecItemFragments.insert(m_vecItemFragments.end(), i_infos.begin(), i_infos.end());
}

void NetworkCacheQueue::removeSyncItemFragment(const std::vector<NetworkItemInfo>& i_infos)
{
	std::vector<NetworkItemInfo>::iterator it = m_vecItemFragments.begin();
	while (it != m_vecItemFragments.end())
	{
		NetworkItemInfo info = *it;
		if (std::find(i_infos.begin(), i_infos.end(), info) != i_infos.end())
			it = m_vecItemFragments.erase(it);
		else
			++it;
	}
}

bool NetworkCacheQueue::ConvertPlantFragmentToItemFragment()
{
	bool converted = false;
	if (!m_vecPlantFragments.empty())
	{
		std::vector<NetworkCacheFragement>::iterator it = m_vecPlantFragments.begin();
		std::vector<NetworkCacheFragement>::iterator end = m_vecPlantFragments.end();
		for (; it != end; ++it)
		{
			NetworkCacheFragement& f = *it;
			NetworkItemInfo info;
			info.m_objectId = f.fragmentId;
			info.m_count = f.fragmentCount;
			m_vecItemFragments.push_back(info);
		}
		converted = true;
	}
	return converted;
}

/////////////// Lifetime ///////////////

NetworkCacheQueue::NetworkCacheQueue()
{
	m_isFlushing = false;
	m_iPlayerId = 0;
	m_llReqSeq = 0;
	m_sSK = "";
	m_sDefineID = "";
	m_sUserID = "";
	m_isSyncProfile = false;
	gMessageRouter->Subscribe(Message::AddFreeGemFinish, Sexy::MakeDelegate(*this, &NetworkCacheQueue::onFlushAddFreeGemFinish));
}

NetworkCacheQueue::~NetworkCacheQueue()
{
	gMessageRouter->Unsubscribe(this);
}

bool NetworkCacheQueue::flush()
{
	if (isNetCacheEmpty())
	{
		m_isFlushing = false;
		return false;
	}
	m_isFlushing = true;
	INetworkMsgProcess* proc = gNetworkMgr->GetNewNetWorkProcess();
	if (m_cachedObjects.size() != 0)
		proc->IRequestFlushCacheObjects();
	if (m_vecPlantFragments.size() != 0)
		proc->IFlushCacheRequestUpdateDatePlantFragments();
	if (m_vecDressFragments.size() != 0)
		proc->IFlushCacheRequestUpdateDateDressFragments();
	if (m_vecPendantFragments.size() != 0 || m_vecPendants.size() != 0)
		proc->IFlushCacheRequestUpdateDatePendantInfo();
	if (m_vecAddFreeGemIds.size() != 0)
		proc->IFlushCacheRequestUpdateAddFreeGem();
	return true;
}
