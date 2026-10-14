//
//  DinosaurYounger.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DinosaurYounger.h"

DinosaurYounger::DinosaurYounger()
{
	m_numberOfZombiesCarriedAndDropped = 0;
}

DinosaurYounger::~DinosaurYounger()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurYounger);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurYoungerPropertySheet);

void DinosaurYoungerPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinosaurYoungerPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(DinosaurPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(bool, ShakeEnabled);
	REFLECTION_CLASSBUILDER_END(DinosaurYoungerPropertySheet);
}

bool DinosaurYounger::CanBeCharmed()
{
	return false;
}

void DinosaurYounger::cryAnimDoneHandler()
{
}

void DinosaurYounger::wakeAnimDoneHandler()
{
}

void DinosaurYounger::caughtAnimDoneHandler()
{
}

void DinosaurYounger::Charm()
{
}
