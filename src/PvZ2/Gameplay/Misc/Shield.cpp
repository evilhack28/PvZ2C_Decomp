//
//  Shield.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Shield.h"

Shield::~Shield()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Shield);

void Shield::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ShieldProps);
		REFLECTION_CLASSBUILDER_FIELD(float, Hitpoints);
	REFLECTION_CLASSBUILDER_END(ShieldProps);

	REFLECTION_CLASSBUILDER_BEGIN(Shield);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(float, m_hitpoints);
		REFLECTION_CLASSBUILDER_FIELD(ShieldProps, m_props);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_damageIndex);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PlantAnimRig_Shielded>, m_animRig);
	REFLECTION_CLASSBUILDER_END(Shield);
}

#include "Shield.h"
bool Shield::Undamaged()
{
	return Shield::hasShield();
}
