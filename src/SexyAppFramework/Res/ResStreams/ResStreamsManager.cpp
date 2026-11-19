//
//  ResStreamsManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/ResStreamsManager.h"

using namespace Sexy;

/////////////// Groups ///////////////

bool ResStreamsManager::IsGroupLoaded(const std::string& theGroupName)
{
	return IsGroupLoaded(LookupGroup(theGroupName));
}

bool ResStreamsManager::LoadGroup(const std::string& theGroupName)
{
	return LoadGroup(LookupGroup(theGroupName));
}

bool ResStreamsManager::ForceLoadGroup(const std::string& theGroupName, const std::string& theDbgReason)
{
	return ForceLoadGroup(LookupGroup(theGroupName), theDbgReason);
}

bool ResStreamsManager::DeleteGroup(const std::string& theGroupName)
{
	return DeleteGroup(LookupGroup(theGroupName));
}

bool ResStreamsManager::IsGroupLoaded(uint32 theGroupId)
{
	return theGroupId != UNKNOWN_GROUP && GetGroupStatus(theGroupId) == RESIDENT;
}

/////////////// Loading ///////////////

void ResStreamsManager::OnGPUDataFinished(ResStreamsLoadDesc* theDesc)
{
	theDesc->gpu_data_loaded = true;
}

/////////////// Stats ///////////////

uint32 ResStreamsManager::GetTotalBytesForGroup(RSBDesc* pRsbDesc, uint32 theGroupId)
{
	if (!pRsbDesc)
		return -1;

	ResStreamGroupDescriptor* aDesc = pRsbDesc->mGroups[theGroupId].mDesc;
	return aDesc->data_gpu_total_size + aDesc->data_resident_total_size + aDesc->data_transient_total_size;
}
