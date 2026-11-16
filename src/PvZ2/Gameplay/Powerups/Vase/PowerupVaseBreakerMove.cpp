//
//  PowerupVaseBreakerMove.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PowerupVaseBreaker.h"
#include "GridItemVase.h"
#include "AudioMgr.h"
#include "LawnApp.h"
#include "Board.h"
#include "ScaledApp.h"
#include "BoardTransforms.h"
#include "PowerupManager.h"

PowerupVaseBreakerMove::PowerupVaseBreakerMove()
{
	m_dragging = 0;
	m_movingQueuedVase = 0;
}

PowerupVaseBreakerMove::~PowerupVaseBreakerMove()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupVaseBreakerMove);

void PowerupVaseBreakerMove::Draw(Sexy::Graphics* i_g)
{
}

void PowerupVaseBreakerMove::clearSelection()
{
	if (m_selectedVase)
	{
		m_selectedVase->SetSelectedForMove(false);
		m_selectedVase.ClearId();
	}
}

void PowerupVaseBreakerMove::clearQueuedVase()
{
	if (m_queuedVase)
	{
		m_queuedVase->SetSelectedForMove(false);
		m_queuedVase.ClearId();
	}
}

void PowerupVaseBreakerMove::queueSelectedVase()
{
	if (m_selectedVase)
	{
		m_queuedVase = m_selectedVase;
		m_selectedVase.ClearId();
	}
}

void PowerupVaseBreakerMove::selectQueuedVase()
{
	if (m_queuedVase)
	{
		m_selectedVase = m_queuedVase;
		m_queuedVase.ClearId();
	}
}

void PowerupVaseBreakerMove::onTouchCanceled()
{
	clearSelection();
	m_dragging = false;
	m_movingQueuedVase = false;
}

void PowerupVaseBreakerMove::onExitState_Selected(PowerupState i_toState)
{
	PowerupTouchBased::onExitState_Selected(i_toState);
	clearSelection();
	clearQueuedVase();
}

void PowerupVaseBreakerMove::onEnterState_Activated(PowerupState i_fromState)
{
	gAudioMgr->SendEvent("Play_UI_MiniGame_VaseBreak_MoveRelease");
}

void PowerupVaseBreakerMove::selectVase(GridItemVase* i_vase)
{
	clearSelection();
	if (i_vase)
	{
		m_selectedVase = i_vase->GetPtr();
		i_vase->SetSelectedForMove(true);
		gAudioMgr->SendEvent("Play_UI_MiniGame_VaseBreak_MovePress");
	}
}

GridItemVase* PowerupVaseBreakerMove::getFirstVaseAt(const Point& i_gridLoc) const
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

bool PowerupVaseBreakerMove::onTouchBegin(const Sexy::Touch& i_touch)
{
	bool selected = false;
	if (m_queuedVase.IsValid())
	{
		selectQueuedVase();
		m_movingQueuedVase = true;
		return true;
	}
	Sexy::Point p = i_touch.location;
	SexyVector2 loc(INV_S(p.mX), INV_S(p.mY));
	Sexy::Point grid = BoardTransforms::BoardSpaceToGrid(loc.x, loc.y);
	GridItemVase* vase = getFirstVaseAt(grid);
	if (vase && !vase->IsBreaking())
	{
		selected = true;
		selectVase(vase);
	}
	return selected;
}

void PowerupVaseBreakerMove::onTouchMoved(const Sexy::Touch& i_touch)
{
	if (!m_selectedVase.IsValid())
		return;
	Sexy::Point p = i_touch.location;
	SexyVector2 loc(INV_S(p.mX), INV_S(p.mY));
	Sexy::Point grid = BoardTransforms::BoardSpaceToGrid(loc.x, loc.y);
	if (grid.mX >= 0 && grid.mY >= 0 && grid != m_selectedVase->GetGridLocation())
		m_dragging = true;
	else if (!m_dragging)
		return;
	bool canMove = canMoveVaseTo(grid);
	m_selectedVase->SetMovePreviewPosition(canMove ? Sexy::Point(grid) : Sexy::Point(-1, -1));
}

bool PowerupVaseBreakerMove::canMoveVaseTo(const Point& i_gridLoc)
{
	bool result = false;
	if (i_gridLoc.mX >= 0 && i_gridLoc.mY >= 0)
	{
		std::vector<GridItem*> items;
		gLawnApp->m_board->GetGridItemsAt(i_gridLoc.mX, i_gridLoc.mY, items);
		PowerupTypeVaseBreakerMove* type = GetType()->CastChecked<PowerupTypeVaseBreakerMove>();
		GridItemRestrictionSet blockers = type->GridItemsWhichBlockMove;
		bool blocked = false;
		for (GridItem* item : items)
		{
			if (blockers.IsIncluded(item))
			{
				blocked = true;
				break;
			}
		}
		if (!blocked)
		{
			if (!gLawnApp->m_board->GetPlantAt(i_gridLoc.mX, i_gridLoc.mY))
				result = gLawnApp->m_board->GetGridSquareType(i_gridLoc.mX, i_gridLoc.mY) != GRIDSQUARE_RAIL;
		}
	}
	return result;
}

void PowerupVaseBreakerMove::onTouchEnd(const Sexy::Touch& i_touch)
{
	if (!m_selectedVase.IsValid())
		return;
	Sexy::Point p = i_touch.location;
	SexyVector2 loc(INV_S(p.mX), INV_S(p.mY));
	Sexy::Point grid = BoardTransforms::BoardSpaceToGrid(loc.x, loc.y);
	if (grid.mX >= 0 && grid.mY >= 0 && grid != m_selectedVase->GetGridLocation())
		m_dragging = true;
	else if (!m_dragging)
	{
		if (!m_movingQueuedVase)
		{
			queueSelectedVase();
			return;
		}
		gLawnApp->m_board->GetPowerupManager()->CancelActivePowerup();
		return;
	}
	if (canMoveVaseTo(grid))
	{
		m_selectedVase->SetGridLocation(grid);
		if (!isInState(POWERUP_Activated))
			Activate();
		DecrementTimeByUseCost();
		return;
	}
	gLawnApp->m_board->GetPowerupManager()->CancelActivePowerup();
}
