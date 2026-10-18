//
//  New_S2C_ItemAddInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"
#include "ReflectionBuilder.h"

#include "NetworkData.h"

New_S2C_ItemAddInfo::New_S2C_ItemAddInfo()
{
}

New_S2C_ItemAddInfo::~New_S2C_ItemAddInfo()
{
}

void New_S2C_ItemAddInfo::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NetworkItemInfo);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, m_count, q);
		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(int, m_objectId, i);
	REFLECTION_CLASSBUILDER_END(NetworkItemInfo);

	REFLECTION_CLASSBUILDER_BEGIN(New_S2C_ItemAddInfo);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(std::vector<NetworkItemInfo>, m_itemList, bl);
	REFLECTION_CLASSBUILDER_END(New_S2C_ItemAddInfo);
}

RT_CLASS_IMPLEMENT(New_S2C_ItemAddInfo);
