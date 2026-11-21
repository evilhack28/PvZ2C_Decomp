//
//  ResourceInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "ResourceManager.h"
#include "ReflectionBuilder.h"

/////////////// Logic ///////////////

void ResourceInfo::DeleteResource()
{
	if (!mInstanceRtId || mSrcRefResInfo)
		return;

	if (RtDb::GetDb()->GetObjectDeletionMode(mInstanceRtId) != RtDbTable::ODM_Never)
		delete RtDb::GetDb()->GetObjectForId(mInstanceRtId)->Cast<BaseResource>();

	RtDb::GetDb()->ReplaceObjectForId(mInstanceRtId, NULL);
	if (mInstanceRtId.GetTableIndex() == RtDb::SYSTEMTABLE_ResourceInstancesHidden)
		RtDb::GetDb()->ReleaseId(mInstanceRtId);
	mInstanceRtId = RtId();
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT_ABSTRACT(ResourceInfo);
