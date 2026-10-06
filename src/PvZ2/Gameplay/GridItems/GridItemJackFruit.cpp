//
//  GridItemJackFruit.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Jackfruit.h"

GridItemJackFruit::GridItemJackFruit()
{
}

GridItemJackFruitPropertySheet::~GridItemJackFruitPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemJackFruit);

void GridItemJackFruit::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemJackFruit);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_pRenderRig);
	REFLECTION_CLASSBUILDER_END(GridItemJackFruit);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemJackFruitPropertySheet);

void GridItemJackFruitPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemJackFruitPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

	REFLECTION_CLASSBUILDER_END(GridItemJackFruitPropertySheet);
}

#include "GridItem.h"
void GridItemJackFruit::registerForEvents()
{
	 GridItem::registerForEvents();
}

#include "GridItem.h"
void GridItemJackFruit::onUpdate()
{
	 GridItem::onUpdate();
}
