//
//  ComponentProjectileConverter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ComponentProjectileConverter.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ComponentProjectileConverterProps);

void ComponentProjectileConverterProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ConvertProjectileNameNode);
	REFLECTION_CLASSBUILDER_END(ConvertProjectileNameNode);

	REFLECTION_CLASSBUILDER_BEGIN(ComponentProjectileConverterProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ConvertProjectileNameNode>, ConvertProjectiles);
	REFLECTION_CLASSBUILDER_END(ComponentProjectileConverterProps);
}
