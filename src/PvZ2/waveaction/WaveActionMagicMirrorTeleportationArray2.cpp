//
//  WaveActionMagicMirrorTeleportationArray2.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "WaveActionMagicMirrorTeleportationArray2.h"

WaveActionMagicMirrorTeleportationArray2::WaveActionMagicMirrorTeleportationArray2()
{
}

WaveActionMagicMirrorTeleportationArray2::~WaveActionMagicMirrorTeleportationArray2()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveActionMagicMirrorTeleportationArray2);

void WaveActionMagicMirrorTeleportationArray2::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveActionMagicMirrorTeleportationArray2);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(WaveActionMagicMirrorTeleportationArray2);
}

void WaveActionMagicMirrorTeleportationArray2::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void WaveActionMagicMirrorTeleportationArray2::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
