//
//  CollectablePlantUpgrade.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectablePlantUpgrade.h"
#include "GameEventMgr.h"
#include "Board.h"

CollectablePlantUpgrade::CollectablePlantUpgrade()
{
}

CollectablePlantUpgrade::~CollectablePlantUpgrade()
{
}

CollectablePlantUpgradeType::CollectablePlantUpgradeType()
{
}

CollectablePlantUpgradeType::~CollectablePlantUpgradeType()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectablePlantUpgrade);

void CollectablePlantUpgrade::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectablePlantUpgrade);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Collectable);

	REFLECTION_CLASSBUILDER_FIELD(std::string, m_seedName);

	REFLECTION_CLASSBUILDER_END(CollectablePlantUpgrade);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectablePlantUpgradeType);

void CollectablePlantUpgradeType::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CollectablePlantUpgradeType);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(CollectableType);

	REFLECTION_CLASSBUILDER_END(CollectablePlantUpgradeType);
}

/////////////// Logic ///////////////

void CollectablePlantUpgrade::SetSeedName(const std::string& i_seedName)
{
	m_seedName = i_seedName;
}

std::string CollectablePlantUpgrade::GetSeedName()
{
	return m_seedName;
}

void CollectablePlantUpgrade::onFinishMotion()
{
	Collectable::onFinishMotion();
	if (getState() == CS_Collecting)
		gMessageRouter->Post(&Message::TakePlantWeapon, m_seedName);
}
