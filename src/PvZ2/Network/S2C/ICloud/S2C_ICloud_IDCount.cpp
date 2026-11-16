//
//  S2C_ICloud_IDCount.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_IDCount);

void S2C_ICloud_IDCount::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_IDCount);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_id, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_count, q);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_IDCount);
}

/////////////// Logic ///////////////

bool S2C_ICloud_IDCount::Find(const std::vector<S2C_ICloud_IDCount>& src, int id, int count)
{
	bool found = false;
	for (const S2C_ICloud_IDCount& entry : src)
	{
		if (entry.m_id == id && entry.m_count == count)
		{
			found = true;
			break;
		}
	}

	return found;
}
