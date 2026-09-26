//
//  AnimRigLayerSet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AnimRigLayerSet.h"

AnimRigLayerSet::AnimRigLayerSet()
{
}

AnimRigLayerSet::~AnimRigLayerSet()
{
}

#include "ReflectionBuilder.h"

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
