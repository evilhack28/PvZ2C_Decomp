//
//  PlantAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PlantAnimRig.h"

PlantAnimRig::~PlantAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantAnimRig);

void PlantAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantCustomLayers);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_baseName);
	REFLECTION_CLASSBUILDER_END(PlantCustomLayers);

	REFLECTION_CLASSBUILDER_BEGIN(PlantAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_bAvatar);
		REFLECTION_CLASSBUILDER_FIELD(int, m_avatarIndex);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PlantCustomLayers>, m_customizableLayers);
	REFLECTION_CLASSBUILDER_END(PlantAnimRig);
}

void PlantAnimRig::onLevelUpdate()
{
}

void PlantAnimRig::onAvatarUpdate()
{
}

void PlantAnimRig::InitAnimRig_ZenGarden()
{
}
