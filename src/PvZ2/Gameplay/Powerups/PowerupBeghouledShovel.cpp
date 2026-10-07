//
//  PowerupBeghouledShovel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupBeghouled.h"
#include "GridItemCrater.h"
#include "EntityFinder.h"
#include "Plant.h"
#include "LawnApp.h"
#include "Board.h"
#include "ScaledApp.h"
#include "BoardTransforms.h"
#include "PowerupManager.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

PowerupBeghouledShovel::PowerupBeghouledShovel()
{
}

PowerupBeghouledShovel::~PowerupBeghouledShovel()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(PowerupBeghouledShovel);

void PowerupBeghouledShovel::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PowerupBeghouledShovel);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PowerupTouchBased);

	REFLECTION_CLASSBUILDER_END(PowerupBeghouledShovel);
}

/////////////// Logic ///////////////

bool PowerupBeghouledShovel::onTouchBegin(const Sexy::Touch& i_touch)
{
	return true;
}

static GridItemCrater* GetCraterAt(int i_x, int i_y)
{
	std::vector<BoardEntity*> entities;
	EntityFinder::GetEntitiesAtGridSquare(entities, ENTITYTYPE_GRIDITEM, i_x, i_y);
	for (size_t i = 0; i < entities.size(); i++)
	{
		GridItemCrater* crater = entities[i]->Cast<GridItemCrater>();
		if (crater)
			return crater;
	}
	return nullptr;
}

void PowerupBeghouledShovel::onTouchEnd(const Sexy::Touch& i_touch)
{
	Sexy::Point p = i_touch.location;
	SexyVector2 loc(INV_S(p.mX), INV_S(p.mY));
	Sexy::Point grid = BoardTransforms::BoardSpaceToGrid(loc.x, loc.y);
	Plant* plant = gLawnApp->m_board->GetPlantAt(grid.mX, grid.mY, "");
	GridItemCrater* crater = GetCraterAt(grid.mX, grid.mY);
	if (plant || crater)
	{
		gMessageRouter->Broadcast(Message::BeghouledClearGridLocation, grid.mX, grid.mY);
		Activate();
		Deactivate();
	}
	else
		gLawnApp->m_board->GetPowerupManager()->CancelActivePowerup();
}
