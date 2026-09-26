//
//  Effect_GarlicStinkLines.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Garlic.h"

Effect_GarlicStinkLines::Effect_GarlicStinkLines()
{
}

Effect_GarlicStinkLines::~Effect_GarlicStinkLines()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_GarlicStinkLines);

void Effect_GarlicStinkLines::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_GarlicStinkLines);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, m_targetZombie);

	REFLECTION_CLASSBUILDER_END(Effect_GarlicStinkLines);
}
