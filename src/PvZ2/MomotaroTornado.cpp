//
//  MomotaroTornado.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "MomotaroTornado.h"

MomotaroTornado::MomotaroTornado()
{
}

MomotaroTornado::~MomotaroTornado()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(MomotaroTornado);

void MomotaroTornado::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(MomotaroTornado);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(SkatingGuacodile);

	REFLECTION_CLASSBUILDER_END(MomotaroTornado);
}
