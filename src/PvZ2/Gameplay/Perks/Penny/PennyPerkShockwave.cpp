//
//  PennyPerkShockwave.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PennyPerkShockwave.h"

PennyPerkShockwave::PennyPerkShockwave()
{
}

PennyPerkShockwave::~PennyPerkShockwave()
{
}

PennyPerkShockwaveProperties::PennyPerkShockwaveProperties()
{
}

PennyPerkShockwaveProperties::~PennyPerkShockwaveProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkShockwave);

void PennyPerkShockwave::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkShockwave);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkTimedEffect);

	REFLECTION_CLASSBUILDER_END(PennyPerkShockwave);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PennyPerkShockwaveProperties);

void PennyPerkShockwaveProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PennyPerkShockwaveProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PennyPerkProperties);

	REFLECTION_CLASSBUILDER_END(PennyPerkShockwaveProperties);
}

#include "PennyPerkShockwave.h"
void PennyPerkShockwave::onUpdate()
{
	 PennyPerkShockwave::createShockWave();
}
