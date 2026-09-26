//
//  ZombieDinoEggShell.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-26.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDinoEggShell.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDinoEggShell);

void ZombieDinoEggShell::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieDinoEggShell);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieBasic);

	REFLECTION_CLASSBUILDER_END(ZombieDinoEggShell);
}

bool ZombieDinoEggShell::willDieToShrinking()
{
	return true;
}

ZombieDinoEggShell::ZombieDinoEggShell()
{
}

ZombieDinoEggShell::~ZombieDinoEggShell()
{
}
