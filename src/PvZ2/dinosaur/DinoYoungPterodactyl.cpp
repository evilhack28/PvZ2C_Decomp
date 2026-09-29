//
//  DinoYoungPterodactyl.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DinoYoungPterodactyl.h"

DinoYoungPterodactyl::~DinoYoungPterodactyl()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinoYoungPterodactyl);

void DinoYoungPterodactyl::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinoYoungPterodactyl);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(DinosaurYounger);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<DinosaurPterodactyl>, m_ptero);
	REFLECTION_CLASSBUILDER_END(DinoYoungPterodactyl);
}
