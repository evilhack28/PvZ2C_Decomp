//
//  ZombieDarkWizard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieDarkWizard.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDarkWizard);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieDarkWizardProps);

void ZombieDarkWizardProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ZombieDarkWizardProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(Point, SheepOffset);
		REFLECTION_CLASSBUILDER_FIELD(PlantRestrictionSet, TargetablePlantTypes);
	REFLECTION_CLASSBUILDER_END(ZombieDarkWizardProps);
}
