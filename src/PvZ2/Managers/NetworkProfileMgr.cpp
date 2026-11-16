//
//  NetworkProfileMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-09.
//

#include "SexyAppFramework/Common.h"

#include "NetworkProfileMgr.h"
#include "LawnApp.h"
#include "gameNetWork/NetworkMgr.h"
#include "gameNetWork/NetworkMsgProcess.h"
#include "gameNetWork/NetworkCacheQueue.h"
#include "gameNetWork/NetworkData.h"
#include "gameNetWork/PacketID.h"
#include "NameMapper.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "PlantAccessoryMgr.h"
#include <algorithm>
#include <functional>
#include <sstream>

/////////////// Lifecycle ///////////////

NetworkProfileMgr::NetworkProfileMgr()
{
	gMessageRouter->Subscribe(Message::MsgErrorRequest, Sexy::MakeDelegate(*this, &NetworkProfileMgr::onMsgError));
}

NetworkProfileMgr::~NetworkProfileMgr()
{
	gMessageRouter->Unsubscribe(this);
}

/////////////// Sync ///////////////

void NetworkProfileMgr::TrySync()
{
	onSyncFinished(true);
}

bool NetworkProfileMgr::NeedSync()
{
	return !HasProfileSyncComplete();
}

bool NetworkProfileMgr::HasProfileSyncComplete()
{
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	if (process != nullptr)
	{
		NetworkCacheQueue* queue = process->GetNetworkCacheQueue();
		if (queue != nullptr)
		{
			return queue->isSyncProfile();
		}
	}
	return false;
}

void NetworkProfileMgr::SetProfileSync(bool i_finish)
{
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	if (process != nullptr)
	{
		NetworkCacheQueue* queue = process->GetNetworkCacheQueue();
		if (queue != nullptr)
		{
			queue->setSyncProfile(i_finish);
			process->SaveCache();
		}
	}
}

void NetworkProfileMgr::onSyncFinished(bool i_success)
{
	gMessageRouter->Post(Message::NetworkProfileSyncFinish, i_success);
}

void NetworkProfileMgr::onMsgError(int i_errorId, const std::string& i_requestID)
{
	_PacketId ids;
	if (i_requestID == ids.ID_REQUEST_NETWORK_SYNC_PROFILE)
	{
		onSyncFinished(false);
	}
}

/////////////// Id mapping ///////////////

int NetworkProfileMgr::GetIdByIdType(int i_plantId, IdType i_type)
{
	int result = ServerPlantID(i_plantId).ToInt();
	std::string name = PlantNameMapperServerID::GetInstance().GetNameForId(result);
	switch (i_type)
	{
	case Id_Plant:
		break;
	case Id_PlantChip:
		result = PlantChipNameMapperServerID::GetInstance().GetIdForName(name);
		break;
	case Id_Avatar:
		result = AvatarNameMapperServerID::GetInstance().GetIdForName(name);
		break;
	case Id_AvatarChip:
		result = AvatarChipNameMapperServerID::GetInstance().GetIdForName(name);
		break;
	default:
		result = -1;
		break;
	}
	return result;
}

/////////////// Profile lists ///////////////

std::string NetworkProfileMgr::getRechargeStatusList()
{
	std::string result = "";
	const std::vector<int>& list = ProfileMgr::GetInstance().GetCurrentProfile()->GetNewTotalRechargeRewardStatus();
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	result += "[";
	for (const int& status : list)
	{
		ss.str(std::string(""));
		ss << status;
		result += ss.str();
		result += ",";
	}
	if (list.size() != 0)
	{
		result.erase(result.end() - 1);
	}
	result += "]";
	return result;
}

std::string NetworkProfileMgr::getPendantList()
{
	std::string result = "";
	std::string entry = "";
	bool found = false;
	result += "[";
	std::vector<PlantAccessoryInfo>& infos = ProfileMgr::GetInstance().GetCurrentProfile()->GetPlantAccessoryInfos();
	std::vector<PlantAccessoryInfo>::iterator it = infos.begin();
	std::vector<PlantAccessoryInfo>::iterator end = infos.end();
	for (; it != end; ++it)
	{
		std::string type = it->Type;
		int count = std::count(infos.begin(), infos.end(), type);
		bool hasType = type != "";
		if (count > 0 && hasType)
		{
			found = true;
			result += "{";
			entry = Sexy::StrFormat("\"pei\":\"-1\",\"peti\":\"%d\",\"lv\":\"%d\"", PlantAccessoryInfoMapper::GetInstance().GetIdForName(type), count);
			result += entry;
			result += "}";
			result += ",";
		}
	}
	if (found)
	{
		result.erase(result.end() - 1);
	}
	result += "]";
	return result;
}

std::string NetworkProfileMgr::getMaterialList()
{
	std::string result = "";
	bool found = false;
	result += "{";
	std::vector<MaterialInfo> materials = ProfileMgr::GetInstance().GetCurrentProfile()->GetMaterialInfo();
	std::sort(materials.begin(), materials.end(), std::bind(std::less<int>(), std::bind(&MaterialInfo::id, std::placeholders::_1), std::bind(&MaterialInfo::id, std::placeholders::_2)));
	std::vector<MaterialInfo>::iterator newEnd = std::unique(materials.begin(), materials.end(), std::bind(std::equal_to<int>(), std::bind(&MaterialInfo::id, std::placeholders::_1), std::bind(&MaterialInfo::id, std::placeholders::_2)));
	materials.erase(newEnd, materials.end());
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	std::vector<MaterialInfo>::iterator it = materials.begin();
	std::vector<MaterialInfo>::iterator end = materials.end();
	for (; it != end; ++it)
	{
		MaterialInfo& info = *it;
		int count = info.count;
		if (count > 0)
		{
			found = true;
			result += "\"";
			ss.str(std::string(""));
			ss << info.id;
			result += ss.str();
			result += "\"";
			result += ":";
			ss.str(std::string(""));
			ss << count;
			result += ss.str();
			result += ",";
		}
	}
	if (found)
	{
		result.erase(result.end() - 1);
	}
	result += "}";
	return result;
}

std::string NetworkProfileMgr::getPlantList()
{
	std::string result = "";
	bool found = false;
	result += "{";
	std::vector<PlantStarLevel> items = ProfileMgr::GetInstance().GetCurrentProfile()->GetPlantStarsInfo();
	std::sort(items.begin(), items.end(), std::bind(std::less<int>(), std::bind(&PlantStarLevel::iCurrentPlantId, std::placeholders::_1), std::bind(&PlantStarLevel::iCurrentPlantId, std::placeholders::_2)));
	std::vector<PlantStarLevel>::iterator newEnd = std::unique(items.begin(), items.end(), std::bind(std::equal_to<int>(), std::bind(&PlantStarLevel::iCurrentPlantId, std::placeholders::_1), std::bind(&PlantStarLevel::iCurrentPlantId, std::placeholders::_2)));
	items.erase(newEnd, items.end());
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	std::vector<PlantStarLevel>::iterator it = items.begin();
	std::vector<PlantStarLevel>::iterator end = items.end();
	for (; it != end; ++it)
	{
		PlantStarLevel& info = *it;
		if (info.iCurrentLevel > 0)
		{
			int id = GetIdByIdType(info.iCurrentPlantId, Id_Plant);
			if (id != -1)
			{
				found = true;
				result += "\"";
				ss.str(std::string(""));
				ss << id;
				result += ss.str();
				result += "\"";
				result += ":";
				ss.str(std::string(""));
				ss << info.iCurrentLevel;
				result += ss.str();
				result += ",";
			}
		}
	}
	if (found)
	{
		result.erase(result.end() - 1);
	}
	result += "}";
	return result;
}

std::string NetworkProfileMgr::getPlantChipList()
{
	std::string result = "";
	bool found = false;
	result += "{";
	std::vector<PlantPieceRecord> items = ProfileMgr::GetInstance().GetCurrentProfile()->GetPlantPiecesInfo();
	std::sort(items.begin(), items.end(), std::bind(std::less<int>(), std::bind(&PlantPieceRecord::PlantId, std::placeholders::_1), std::bind(&PlantPieceRecord::PlantId, std::placeholders::_2)));
	std::vector<PlantPieceRecord>::iterator newEnd = std::unique(items.begin(), items.end(), std::bind(std::equal_to<int>(), std::bind(&PlantPieceRecord::PlantId, std::placeholders::_1), std::bind(&PlantPieceRecord::PlantId, std::placeholders::_2)));
	items.erase(newEnd, items.end());
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	std::vector<PlantPieceRecord>::iterator it = items.begin();
	std::vector<PlantPieceRecord>::iterator end = items.end();
	for (; it != end; ++it)
	{
		PlantPieceRecord& info = *it;
		if (info.PieceCount > 0)
		{
			int id = GetIdByIdType(info.PlantId, Id_PlantChip);
			if (id != -1)
			{
				found = true;
				result += "\"";
				ss.str(std::string(""));
				ss << id;
				result += ss.str();
				result += "\"";
				result += ":";
				ss.str(std::string(""));
				ss << info.PieceCount;
				result += ss.str();
				result += ",";
			}
		}
	}
	if (found)
	{
		result.erase(result.end() - 1);
	}
	result += "}";
	return result;
}

std::string NetworkProfileMgr::getNewAvatarChipList()
{
	std::string result = "";
	bool found = false;
	result += "{";
	std::vector<PlantNewAvatarPiecesInfo> items = ProfileMgr::GetInstance().GetCurrentProfile()->GetPlantNewAvatarPiecesInfo();
	std::sort(items.begin(), items.end(), std::bind(std::less<int>(), std::bind(&PlantNewAvatarPiecesInfo::iPlantNewPiecesID, std::placeholders::_1), std::bind(&PlantNewAvatarPiecesInfo::iPlantNewPiecesID, std::placeholders::_2)));
	std::vector<PlantNewAvatarPiecesInfo>::iterator newEnd = std::unique(items.begin(), items.end(), std::bind(std::equal_to<int>(), std::bind(&PlantNewAvatarPiecesInfo::iPlantNewPiecesID, std::placeholders::_1), std::bind(&PlantNewAvatarPiecesInfo::iPlantNewPiecesID, std::placeholders::_2)));
	items.erase(newEnd, items.end());
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	std::vector<PlantNewAvatarPiecesInfo>::iterator it = items.begin();
	std::vector<PlantNewAvatarPiecesInfo>::iterator end = items.end();
	for (; it != end; ++it)
	{
		PlantNewAvatarPiecesInfo& info = *it;
		int count = info.iPiecesCount;
		if (count > 0)
		{
			found = true;
			result += "\"";
			ss.str(std::string(""));
			ss << info.iPlantNewPiecesID;
			result += ss.str();
			result += "\"";
			result += ":";
			ss.str(std::string(""));
			ss << count;
			result += ss.str();
			result += ",";
		}
	}
	if (found)
	{
		result.erase(result.end() - 1);
	}
	result += "}";
	return result;
}

std::string NetworkProfileMgr::getPendantChipList()
{
	std::string result = "";
	bool found = false;
	result += "{";
	std::vector<AccessoryPiece> items = ProfileMgr::GetInstance().GetCurrentProfile()->GetAccessoryPiecesInfo();
	std::sort(items.begin(), items.end(), std::bind(std::less<std::string>(), std::bind(&AccessoryPiece::Type, std::placeholders::_1), std::bind(&AccessoryPiece::Type, std::placeholders::_2)));
	std::vector<AccessoryPiece>::iterator newEnd = std::unique(items.begin(), items.end(), std::bind(std::equal_to<std::string>(), std::bind(&AccessoryPiece::Type, std::placeholders::_1), std::bind(&AccessoryPiece::Type, std::placeholders::_2)));
	items.erase(newEnd, items.end());
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	std::vector<AccessoryPiece>::iterator it = items.begin();
	std::vector<AccessoryPiece>::iterator end = items.end();
	for (; it != end; ++it)
	{
		AccessoryPiece& info = *it;
		std::string type = info.Type;
		int count = info.PieceCount;
		if (count > 0)
		{
			found = true;
			result += "\"";
			ss.str(std::string(""));
			ss << PlantAccessoryPieceMapper::GetInstance().GetIdForName(type);
			result += ss.str();
			result += "\"";
			result += ":";
			ss.str(std::string(""));
			ss << count;
			result += ss.str();
			result += ",";
		}
	}
	if (found)
	{
		result.erase(result.end() - 1);
	}
	result += "}";
	return result;
}

std::string NetworkProfileMgr::getAvatarList()
{
	std::string result = "";
	std::vector<PlantAvatarInfo> items = ProfileMgr::GetInstance().GetCurrentProfile()->GetPlantAvatarInfo();
	std::sort(items.begin(), items.end(), std::bind(std::less<int>(), std::bind(&PlantAvatarInfo::iPlantID, std::placeholders::_1), std::bind(&PlantAvatarInfo::iPlantID, std::placeholders::_2)));
	std::vector<PlantAvatarInfo>::iterator newEnd = std::unique(items.begin(), items.end(), std::bind(std::equal_to<int>(), std::bind(&PlantAvatarInfo::iPlantID, std::placeholders::_1), std::bind(&PlantAvatarInfo::iPlantID, std::placeholders::_2)));
	items.erase(newEnd, items.end());
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	result += "[";
	std::vector<PlantAvatarInfo>::iterator it = items.begin();
	std::vector<PlantAvatarInfo>::iterator end = items.end();
	for (; it != end; ++it)
	{
		int id = GetIdByIdType((*it).iPlantID, Id_Avatar);
		if (id != -1)
		{
			ss.str(std::string(""));
			ss << id;
			result += ss.str();
			result += ",";
		}
	}
	if (items.size() != 0)
	{
		result.erase(result.end() - 1);
	}
	result += "]";
	return result;
}

std::string NetworkProfileMgr::getAvatarChipList()
{
	std::string result = "";
	bool found = false;
	result += "{";
	std::vector<PlantAvatarPiecesInfo> items = ProfileMgr::GetInstance().GetCurrentProfile()->GetPlantAvatarPiecesInfo();
	std::sort(items.begin(), items.end(), std::bind(std::less<int>(), std::bind(&PlantAvatarPiecesInfo::iPlantID, std::placeholders::_1), std::bind(&PlantAvatarPiecesInfo::iPlantID, std::placeholders::_2)));
	std::vector<PlantAvatarPiecesInfo>::iterator newEnd = std::unique(items.begin(), items.end(), std::bind(std::equal_to<int>(), std::bind(&PlantAvatarPiecesInfo::iPlantID, std::placeholders::_1), std::bind(&PlantAvatarPiecesInfo::iPlantID, std::placeholders::_2)));
	items.erase(newEnd, items.end());
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	std::vector<PlantAvatarPiecesInfo>::iterator it = items.begin();
	std::vector<PlantAvatarPiecesInfo>::iterator end = items.end();
	for (; it != end; ++it)
	{
		PlantAvatarPiecesInfo& info = *it;
		int count = info.vecAvatarPiecesCount[E_AVATAR_NORMAL];
		if (count > 0)
		{
			int id = GetIdByIdType(info.iPlantID, Id_AvatarChip);
			if (id != -1)
			{
				found = true;
				result += "\"";
				ss.str(std::string(""));
				ss << id;
				result += ss.str();
				result += "\"";
				result += ":";
				ss.str(std::string(""));
				ss << count;
				result += ss.str();
				result += ",";
			}
		}
	}
	if (found)
	{
		result.erase(result.end() - 1);
	}
	result += "}";
	return result;
}

std::string NetworkProfileMgr::getNewAvatarList()
{
	std::string result = "";
	std::vector<PlantNewAvatarInfo> items = ProfileMgr::GetInstance().GetCurrentProfile()->GetPlantNewAvatarInfo();
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	result += "[";
	std::vector<PlantNewAvatarInfo>::iterator it = items.begin();
	std::vector<PlantNewAvatarInfo>::iterator end = items.end();
	for (; it != end; ++it)
	{
		std::vector<int>& unlocked = (*it).vecNewAvatarUnlockedID;
		std::sort(unlocked.begin(), unlocked.end());
		std::vector<int>::iterator newEnd = std::unique(unlocked.begin(), unlocked.end());
		unlocked.erase(newEnd, unlocked.end());
		std::vector<int>::iterator idIt = unlocked.begin();
		std::vector<int>::iterator idEnd = unlocked.end();
		for (; idIt != idEnd; ++idIt)
		{
			int& value = *idIt;
			ss.str(std::string(""));
			ss << value;
			result += ss.str();
			result += ",";
		}
	}
	if (items.size() != 0)
	{
		result.erase(result.end() - 1);
	}
	result += "]";
	return result;
}

/////////////// Sync request ///////////////

void NetworkProfileMgr::DoSync()
{
	std::map<std::string, std::string> params;
	std::stringstream ss(std::ios_base::out | std::ios_base::in);
	PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
	int gems = profile->GetNumGems(true);
	ss.str(std::string(""));
	ss << gems;
	params["g"] = ss.str();
	params["pcl"] = getPlantChipList();
	params["pl"] = getPlantList();
	params["dcl"] = getAvatarChipList();
	params["dl"] = getAvatarList();
	params["ndcl"] = getNewAvatarChipList();
	params["ndl"] = getNewAvatarList();
	params["il"] = getMaterialList();
	params["pdl"] = getPendantList();
	params["pdcl"] = getPendantChipList();
	ss.str(std::string(""));
	ss << profile->GetNumTotalRechargeCurrency();
	params["c"] = ss.str();
	ss.str(std::string(""));
	ss << profile->GetNumRechargeCurrency();
	params["ntc"] = ss.str();
	params["ntcs"] = getRechargeStatusList();
	DNetwork* network = DNetwork::getInstance();
	_PacketId ids;
	network->requestMsg(ids.ID_REQUEST_NETWORK_SYNC_PROFILE, params, 30.0f, [this](const std::string& i_response)
	{
		NetworkProfileSyncInfo info;
		if (info.SerializeJson(i_response))
		{
			SetProfileSync(true);
			onSyncFinished(true);
		}
		else
		{
			onSyncFinished(false);
		}
	}, true, true, "[NET_CONNECTING]", 0);
}
