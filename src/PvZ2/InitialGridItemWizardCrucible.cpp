//
//  InitialGridItemWizardCrucible.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "InitialGridItemWizardCrucible.h"

InitialGridItemWizardCrucible::InitialGridItemWizardCrucible()
{
}

InitialGridItemWizardCrucible::~InitialGridItemWizardCrucible()
{
}

InitialGridItemWizardCrucibleProps::InitialGridItemWizardCrucibleProps()
{
}

InitialGridItemWizardCrucibleProps::~InitialGridItemWizardCrucibleProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(InitialGridItemWizardCrucible);

void InitialGridItemWizardCrucible::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(InitialGridItemWizardCrucible);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

	REFLECTION_CLASSBUILDER_END(InitialGridItemWizardCrucible);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(InitialGridItemWizardCrucibleProps);

void InitialGridItemWizardCrucibleProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(WizardCrucibleDescribe);
	REFLECTION_CLASSBUILDER_END(WizardCrucibleDescribe);

	REFLECTION_CLASSBUILDER_BEGIN(InitialGridItemWizardCrucibleProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<WizardCrucibleDescribe>, InitialGridItemWizardCrucibles);
	REFLECTION_CLASSBUILDER_END(InitialGridItemWizardCrucibleProps);
}
