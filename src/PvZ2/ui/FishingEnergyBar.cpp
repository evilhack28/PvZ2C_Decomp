//
//  FishingEnergyBar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "FishingEnergyBar.h"

void FishingEnergyBar::initLoadingResourcesGroupList()
{
}

FishingEnergyBar::FishingEnergyBar()
{
	m_touchIdent = 0;
	m_curEnergy = 0;
	m_maxEnergy = 0;
}

FishingEnergyBar::~FishingEnergyBar()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FishingEnergyBar);

void FishingEnergyBar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FishingEnergyBar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

	REFLECTION_CLASSBUILDER_END(FishingEnergyBar);
}
