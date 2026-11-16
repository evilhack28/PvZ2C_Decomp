//
//  AnimRigLayerSet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AnimRigLayerSet.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

AnimRigLayerSet::AnimRigLayerSet()
{
}

AnimRigLayerSet::~AnimRigLayerSet()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(AnimRigLayerSet);

void AnimRigLayerSet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AnimRigLayerSet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_FIELD(std::map<std::string RT_COMMA std::vector<std::string>>, m_layerSets);
	REFLECTION_CLASSBUILDER_FIELD(std::string, m_currentLayerName);

	REFLECTION_CLASSBUILDER_END(AnimRigLayerSet);
}

/////////////// Logic ///////////////

void AnimRigLayerSet::AddSet(std::string setName, std::vector<std::string> layerNames)
{
	m_layerSets[setName] = layerNames;
}

void AnimRigLayerSet::ShowSet(PopAnimRig* animRig, std::string setName)
{
	if (m_currentLayerName == setName)
		return;
	std::map<std::string, std::vector<std::string>>::iterator it = m_layerSets.begin();
	while (it != m_layerSets.end())
	{
		{
			std::pair<const std::string, std::vector<std::string>>& entry = *it;
			bool visible = entry.first == setName;
			std::vector<std::string>::iterator layer = entry.second.begin();
			std::vector<std::string>::iterator layerEnd = entry.second.end();
			while (layer != layerEnd)
			{
				animRig->SetLayerVisibility(*layer, visible);
				++layer;
			}
			++it;
		}
	}
	m_currentLayerName = setName;
}
