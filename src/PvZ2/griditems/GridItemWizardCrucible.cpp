//
//  GridItemWizardCrucible.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemWizardCrucible.h"

GridItemWizardCrucible::~GridItemWizardCrucible()
{
}

GridItemWizardCrucibleProps::GridItemWizardCrucibleProps()
{
}

GridItemWizardCrucibleProps::~GridItemWizardCrucibleProps()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWizardCrucible);

void GridItemWizardCrucible::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemWizardCrucible);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimation);

		REFLECTION_CLASSBUILDER_FIELD(int, m_state);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasExploded);
		REFLECTION_CLASSBUILDER_FIELD(std::string, m_currentUpgradePlantTypeName);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::vector<std::string>>, m_plantTypeNameListVector);
	REFLECTION_CLASSBUILDER_END(GridItemWizardCrucible);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemWizardCrucibleProps);

void GridItemWizardCrucibleProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemWizardCrucibleProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemBreakableTargetProps);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, CannotGetPlantTypeName);
	REFLECTION_CLASSBUILDER_END(GridItemWizardCrucibleProps);
}

void GridItemWizardCrucible::updateState()
{
}

#include "GridItem.h"
void GridItemWizardCrucible::registerForEvents()
{
	 GridItem::registerForEvents();
}

#include "GridItem.h"
void GridItemWizardCrucible::onDestroy()
{
	 GridItem::onDestroy();
}

bool GridItemWizardCrucible::CollidesWithType(const CollisionTypeFlags i_arg) const
{
	return true;
}
