//
//  S2C_PlatformGiftData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_PlatformGiftData);

void S2C_PlatformGiftData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GiftItem);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, _id, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, _count, q);
	REFLECTION_CLASSBUILDER_END(GiftItem);

	REFLECTION_CLASSBUILDER_BEGIN(S2C_PlatformGiftData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::vector<GiftItem>, _giftList, b);
	REFLECTION_CLASSBUILDER_END(S2C_PlatformGiftData);

}
