//
//  DinoYoungTyrannosaurus.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DinoYoungTyrannosaurus.h"

DinoYoungTyrannosaurus::~DinoYoungTyrannosaurus()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinoYoungTyrannosaurus);

void DinoYoungTyrannosaurus::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinoYoungTyrannosaurus);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(DinosaurYounger);

	REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_nextActivationTime);
	REFLECTION_CLASSBUILDER_FIELD(int, m_numberOfZombiesCarriedAndDropped);

	REFLECTION_CLASSBUILDER_END(DinoYoungTyrannosaurus);
}
