//
//  DamageLifetime.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DamageLifetime.h"
#include "PopAnimRig.h"

DamageLifetime::DamageLifetime()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DamageLifetime);

void DamageLifetime::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DamageLifetime);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(RtObject);

	REFLECTION_CLASSBUILDER_FIELD(std::vector<DamagePhase>, Phases);

	REFLECTION_CLASSBUILDER_END(DamageLifetime);
}

int DamageLifetime::OnHealthChanged(float i_health, float i_healthMax, PopAnimRig* i_animRig, int i_lastPhase) const
{
	if (Phases.size() == 0)
		return -1;

	int phase = getDamagePhase(i_health, i_healthMax);
	if (phase != i_lastPhase && phase >= 0)
		switchToPhase(phase, i_animRig);

	return phase;
}

void DamageLifetime::SetAnimRigToPhase(int i_phase, PopAnimRig* i_animRig) const
{
	switchToPhase(i_phase, i_animRig);
}

int DamageLifetime::getDamagePhase(float i_health, float i_healthMax) const
{
	size_t count = Phases.size();
	if (count == 0)
		return -1;

	int result = 0;
	float ratio = i_health / i_healthMax;
	for (size_t i = 0; i < count - 1; i++)
	{
		if (Phases[i].StartAtHealthPercent <= ratio)
			return i;

		result = i + 1;
	}

	return result;
}

void DamageLifetime::switchToPhase(int i_phase, PopAnimRig* i_animRig) const
{
	if (i_animRig == NULL)
		return;

	for (size_t i = 0; i < Phases.size(); i++)
	{
		const DamagePhase& phase = Phases[i];
		if (i_phase == (int)i)
		{
			if (!phase.Animation.empty())
				i_animRig->Play(phase.Animation, PLAY_ONCE, SELECT_EXACT, std::vector<int>());

			if (!phase.Layers.empty())
			{
				for (std::vector<std::string>::const_iterator it = phase.Layers.begin(); it != phase.Layers.end(); ++it)
				{
					std::string layer = *it;
					i_animRig->SetLayerVisibility(layer, true);
				}
			}
		}
		else
		{
			if (!phase.Layers.empty())
			{
				for (std::vector<std::string>::const_iterator it = phase.Layers.begin(); it != phase.Layers.end(); ++it)
				{
					std::string layer = *it;
					i_animRig->SetLayerVisibility(layer, false);
				}
			}
		}
	}
}
