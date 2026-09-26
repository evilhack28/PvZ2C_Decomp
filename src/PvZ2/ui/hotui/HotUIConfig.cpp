//
//  HotUIConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HotUIConfig.h"

HotUIConfig::~HotUIConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HotUIConfig);

void HotUIConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HotUIConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ObjectTypeDescriptor);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, ReloadableMenus);

	REFLECTION_CLASSBUILDER_END(HotUIConfig);
}
