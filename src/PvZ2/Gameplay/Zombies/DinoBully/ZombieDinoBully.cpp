//
//  ZombieDinoBully.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDinoBully.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDinoBully);

void ZombieDinoBully::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieDinoBully);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieDinoBasic);

	REFLECTION_CLASSBUILDER_END(ZombieDinoBully);
}
