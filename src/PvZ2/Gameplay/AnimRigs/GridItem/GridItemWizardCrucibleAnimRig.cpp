//
//  GridItemWizardCrucibleAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemWizardCrucible.h"

GridItemWizardCrucibleAnimRig::GridItemWizardCrucibleAnimRig()
{
}

GridItemWizardCrucibleAnimRig::~GridItemWizardCrucibleAnimRig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWizardCrucibleAnimRig);

void GridItemWizardCrucibleAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemWizardCrucibleAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PopAnimRig);

	REFLECTION_CLASSBUILDER_END(GridItemWizardCrucibleAnimRig);
}
