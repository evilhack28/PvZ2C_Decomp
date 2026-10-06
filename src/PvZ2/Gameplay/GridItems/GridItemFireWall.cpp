//
//  GridItemFireWall.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemFireWall.h"

GridItemFireWallPropertySheet::~GridItemFireWallPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFireWall);

void GridItemFireWall::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DamageZombieInfo);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Zombie>, zombePtr);
		REFLECTION_CLASSBUILDER_FIELD(int32, oldState);
	REFLECTION_CLASSBUILDER_END(DamageZombieInfo);

	REFLECTION_CLASSBUILDER_BEGIN(GridItemFireWall);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<EffectAnimRig_FireWall>, m_pRenderRig);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<DamageZombieInfo>, m_pBeDamageZombieVec);
		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_iLastDamageTime);
		REFLECTION_CLASSBUILDER_FIELD(float, m_damageRate);
	REFLECTION_CLASSBUILDER_END(GridItemFireWall);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFireWallPropertySheet);

void GridItemFireWallPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFireWallPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
	REFLECTION_CLASSBUILDER_END(GridItemFireWallPropertySheet);
}

#include "GridItem.h"
void GridItemFireWall::registerForEvents()
{
	 GridItem::registerForEvents();
}
