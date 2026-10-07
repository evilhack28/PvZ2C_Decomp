//
//  Plant_MorningGlory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_MorningGlory.h"

PlantMorningGlory::PlantMorningGlory()
{
}

PlantMorningGlory::~PlantMorningGlory()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PlantMorningGlory);

void PlantMorningGlory::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PlantMorningGlory);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PlantFramework);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_linkingEffect);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_targetEntity);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, m_targetPos);
	REFLECTION_CLASSBUILDER_END(PlantMorningGlory);
}

#include "Plant_MorningGlory.h"
void PlantMorningGlory::UpdateActions()
{
	 PlantMorningGlory::checkLinkingStatus();
}

void PlantMorningGlory::DoSpecial(int i_extraParam)
{
}
