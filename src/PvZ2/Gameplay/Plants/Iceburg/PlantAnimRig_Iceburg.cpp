#include "PlantAnimRig_Iceburg.h"

RT_CLASS_IMPLEMENT(PlantAnimRig_Iceburg);

void PlantAnimRig_Iceburg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig_Iceburg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantAnimRig);

	REFLECTION_CLASSBUILDER_END(PlantAnimRig_Iceburg);
}

bool PlantAnimRig_Iceburg::PlayShootAnimation()
{
	if (PlayAndStop("attack_02") != -1)
	{
		m_state = (PlantAnimRigState)PLANTANIM_ICEBURG_SHOOT;
		return true;
	}
	return false;
}
