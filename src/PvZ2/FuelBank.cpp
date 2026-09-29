//
//  FuelBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "FuelBank.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FuelBank);

void FuelBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FuelBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(FuelBank);
}
