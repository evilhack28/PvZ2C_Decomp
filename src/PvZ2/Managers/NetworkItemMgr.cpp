//
//  NetworkItemMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "NetworkItemMgr.h"
#include "gameNetWork/androidNetworkMsgProcess.h"
#include "gameNetWork/NetworkCacheQueue.h"
#include "LawnApp.h"

#include "NetworkItemMgr.h"
void NetworkItemMgr::onFinishGetPlayerinfo()
{
	 NetworkItemMgr::TryCheckUnsyncItems();
}

bool NetworkItemMgr::HasNetworkCacheSyncComplete()
{
	INetworkMsgProcess* process = NetworkMgr::Instance()->GetNewNetWorkProcess();
	if (process)
	{
		NetworkCacheQueue* queue = process->GetNetworkCacheQueue();
		if (queue)
			return queue->isItemCacheEmpty();
	}
	return false;
}

bool NetworkItemMgr::NeedSync()
{
	return (HasNetworkCacheSyncComplete() || m_sendingRequest || m_syncCount > 2 || gLawnApp->GetCheatsEnabled()) ? false : !m_finishedSync;
}
