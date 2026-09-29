//
//  WaveActionMagicMirrorTeleportationArray.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WaveActionMagicMirrorTeleportationArray.h"

WaveActionMagicMirrorTeleportationArray::WaveActionMagicMirrorTeleportationArray()
{
}

WaveActionMagicMirrorTeleportationArray::~WaveActionMagicMirrorTeleportationArray()
{
}

WaveActionMagicMirrorTeleportationArrayProps::~WaveActionMagicMirrorTeleportationArrayProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveActionMagicMirrorTeleportationArray);

void WaveActionMagicMirrorTeleportationArray::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WaveActionMagicMirrorTeleportationArray);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveAction);

	REFLECTION_CLASSBUILDER_END(WaveActionMagicMirrorTeleportationArray);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WaveActionMagicMirrorTeleportationArrayProps);

void WaveActionMagicMirrorTeleportationArrayProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MagicMirrorTeleportationArrayData);
		REFLECTION_CLASSBUILDER_FIELD(float, MirrorExistDuration);
	REFLECTION_CLASSBUILDER_END(MagicMirrorTeleportationArrayData);

	REFLECTION_CLASSBUILDER_BEGIN(WaveActionMagicMirrorTeleportationArrayProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(WaveActionProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<MagicMirrorTeleportationArrayData>, MagicMirrorTeleportationArrays);
	REFLECTION_CLASSBUILDER_END(WaveActionMagicMirrorTeleportationArrayProps);
}

void WaveActionMagicMirrorTeleportationArray::WaveUpdate(int i_arg0, Sexy::MTRand & i_arg1)
{
}

void WaveActionMagicMirrorTeleportationArray::WaveEnd(int i_arg0, Sexy::MTRand & i_arg1)
{
}
