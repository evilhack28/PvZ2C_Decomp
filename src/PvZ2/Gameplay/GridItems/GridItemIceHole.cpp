//
//  GridItemIceHole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemIceHole.h"

GridItemIceHolePropertySheet::~GridItemIceHolePropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemIceHole);

void GridItemIceHole::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemIceHole);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<EffectAnimRig_IceHole>, m_pRenderRig);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_bHoleRunning);
		REFLECTION_CLASSBUILDER_FIELD(int, m_iDamageZombieCount);
	REFLECTION_CLASSBUILDER_END(GridItemIceHole);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemIceHolePropertySheet);

void GridItemIceHolePropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemIceHolePropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, PopAnim);
	REFLECTION_CLASSBUILDER_END(GridItemIceHolePropertySheet);
}

#include "GridItem.h"
void GridItemIceHole::registerForEvents()
{
	 GridItem::registerForEvents();
}

bool GridItemIceHole::CanBeTargetedBy(const BoardEntity* i_entity) const
{
	return false;
}
