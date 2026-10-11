//
//  IdleAnimationSelector.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "IdleAnimationSelector.h"

IdleAnimationSelector::IdleAnimationSelector()
{
}

IdleAnimationSelector::~IdleAnimationSelector()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(IdleAnimationSelector);

/////////////// Reflection ///////////////

void IdleAnimationSelector::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ProbabilityStringRecord);
		REFLECTION_CLASSBUILDER_FIELD(std::string, Value);
		REFLECTION_CLASSBUILDER_FIELD(int, Weight);
	REFLECTION_CLASSBUILDER_END(ProbabilityStringRecord);

	REFLECTION_CLASSBUILDER_BEGIN(IdleAnimationSelector);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<ProbabilityStringRecord>, m_entries);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_lastLabel);
	REFLECTION_CLASSBUILDER_END(IdleAnimationSelector);
}

/////////////// Logic ///////////////

void IdleAnimationSelector::SetWeights(const std::vector<int>& i_weights)
{
	m_entries = convertWeightsToEntries(i_weights);
}

std::string IdleAnimationSelector::GetLabel()
{
	m_lastLabel = m_picker.Pick(m_entries);
	return m_lastLabel;
}

std::vector<ProbabilityStringRecord> IdleAnimationSelector::convertWeightsToEntries(const std::vector<int>& i_weights)
{
	std::vector<ProbabilityStringRecord> entries;
	int index = 1;
	for (size_t i = 0; i < i_weights.size(); i++)
	{
		std::string label;
		if (i == 0)
			label = "idle";
		else
			label = Sexy::StrFormat("idle%d", index);
		index++;
		ProbabilityStringRecord record = {label, 0};
		record.Weight = i_weights[i];
		entries.push_back(static_cast<ProbabilityStringRecord&&>(record));
	}
	return entries;
}
