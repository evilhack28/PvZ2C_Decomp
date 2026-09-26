//
//  GridItemDevilsEgg.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Plant_DevilsFlower.h"

GridItemDevilsEgg::~GridItemDevilsEgg()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemDevilsEgg);

void GridItemDevilsEgg::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemDevilsEgg);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemAnimController);

	REFLECTION_CLASSBUILDER_FIELD(int, m_level);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_isAvatar);

	REFLECTION_CLASSBUILDER_END(GridItemDevilsEgg);
}

#include "GridItemAnimController.h"
void GridItemDevilsEgg::onGridItemInitialize()
{
	 GridItemAnimController::onGridItemInitialize();
}

#include "GridItemAnimController.h"
void GridItemDevilsEgg::onUpdate()
{
	 GridItemAnimController::onUpdate();
}
