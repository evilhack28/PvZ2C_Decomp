//
//  ZombieAnimRig_ModernSuperfanImp.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ZombieModernSuperfanImp.h"

ZombieAnimRig_ModernSuperfanImp::ZombieAnimRig_ModernSuperfanImp()
{
}

ZombieAnimRig_ModernSuperfanImp::~ZombieAnimRig_ModernSuperfanImp()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieAnimRig_ModernSuperfanImp);

void ZombieAnimRig_ModernSuperfanImp::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieAnimRig_ModernSuperfanImp);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombieAnimRig_Imp);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_kicked);

	REFLECTION_CLASSBUILDER_END(ZombieAnimRig_ModernSuperfanImp);
}
