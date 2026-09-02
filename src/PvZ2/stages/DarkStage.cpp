//
//  DarkStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "DarkStage.h"

#include "BoardEntity.h"
#include "EntityFinder.h"
#include "GridItemGravestoneShortcut.h"
#include "ObjectTypeDirectory.h"
#include "ReflectionBuilder.h"
#include "ZombieType.h"

RT_CLASS_IMPLEMENT(DarkStage);
void DarkStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DarkStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(DarkStage);
}

RT_CLASS_IMPLEMENT(DarkStageProperties);
void DarkStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DarkStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(DarkStageProperties);
}


ZombieTypePtr DarkStage::GetZombieTypeForBasicHelm(HelmType i_helmType)
{
	if (i_helmType == HELMTYPE_CROWN)
		return GetArmor3ZombieType();

	return StageModule::GetZombieTypeForBasicHelm(i_helmType);
}


ZombieTypePtr DarkStage::ResolveZombieType(const std::string& i_genericTypeName)
{
	if (i_genericTypeName == "armor3")
		return GetArmor3ZombieType();

	return StageModule::ResolveZombieType(i_genericTypeName);
}


void DarkStage::registerForEvents()
{
	StageModule::registerForEvents();
}


ZombieTypePtr DarkStage::GetArmor3ZombieType()
{
	if (m_armor3ZombieType != ZombieTypePtr())
		return m_armor3ZombieType;

	m_armor3ZombieType = ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName(
		getProps<DarkStageProperties>()->Armor3ZombieTypeName);
	return m_armor3ZombieType;
}


int DarkStage::GetDefaultZombieSpawnPositionX(int i_row)
{
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesInRowMatchingClass(entities, ENTITYTYPE_GRIDITEM, i_row, GridItemGravestoneShortcut::StaticGetClass());
	std::sort(entities.begin(), entities.end(), BoardEntity::BoardEntityLeftToRightSortFunc);

	if (entities.empty())
		return StageModule::GetDefaultZombieSpawnPositionX(i_row);

	return (int)(entities.front()->GetPosition().x - 50.0f);
}
