//
//  Effect_Mole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "IntrosWhackAMole.h"

Effect_Mole::Effect_Mole()
{
}

Effect_Mole::~Effect_Mole()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_Mole);

void Effect_Mole::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_Mole);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_END(Effect_Mole);
}

void Effect_Mole::SetMoleType(MoleType i_arg)
{
	m_moleType = i_arg;
}
