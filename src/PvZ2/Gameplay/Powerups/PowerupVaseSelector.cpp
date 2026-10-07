//
//  PowerupVaseSelector.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"
#include "GridItemVase.h"
#include "LawnApp.h"
#include "Board.h"
#include "ScaledApp.h"
#include "BoardTransforms.h"
#include "PowerupManager.h"

PowerupVaseSelector::PowerupVaseSelector()
{
}

PowerupVaseSelector::~PowerupVaseSelector()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupVaseSelector);

bool PowerupVaseSelector::onTouchBegin(const Sexy::Touch& i_touch)
{
	return true;
}

GridItemVase* PowerupVaseSelector::getFirstVaseAt(const Point& i_gridLoc) const
{
	std::vector<GridItem*> items;
	gLawnApp->m_board->GetGridItemsAt(i_gridLoc.mX, i_gridLoc.mY, items);
	Sexy::Point unused;
	for (size_t i = 0; i < items.size();)
	{
		GridItemVase* vase = items[i++]->Cast<GridItemVase>();
		if (vase)
			return vase;
	}
	return nullptr;
}

void PowerupVaseSelector::onTouchEnd(const Sexy::Touch& i_touch)
{
	Sexy::Point p = i_touch.location;
	SexyVector2 loc(INV_S(p.mX), INV_S(p.mY));
	Sexy::Point grid = BoardTransforms::BoardSpaceToGrid(loc.x, loc.y);
	GridItemVase* vase = getFirstVaseAt(grid);
	bool ok = canActivateOnVase(vase);
	if (ok)
	{
		if (!isInState(2))
			Activate();
		activateOnVase(vase);
		DecrementTimeByUseCost();
	}
	if (!ok)
		gLawnApp->m_board->GetPowerupManager()->CancelActivePowerup();
}

void PowerupVaseSelector::Draw(Sexy::Graphics* i_g)
{
	if (getActiveTouchIdent())
	{
		const Sexy::Touch& touch = getLastTouchEvent();
		SexyVector2 loc(INV_S(touch.location.mX), INV_S(touch.location.mY));
		Sexy::Point grid = BoardTransforms::BoardSpaceToGrid(loc.x, loc.y);
		GridItemVase* vase = getFirstVaseAt(grid);
		if (vase && canActivateOnVase(vase))
		{
			Sexy::Point loc2 = vase->GetGridLocation();
			gLawnApp->m_board->DrawCelHighlight(i_g, loc2.mX, loc2.mY);
		}
	}
}
