//
//  MiniBoard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "MiniBoard.h"
#include "Collectable.h"
#include "Plant.h"
#include "Zombie.h"
#include "Projectile.h"
#include "EffectObject.h"
#include "PlantGroup.h"
#include "PlantGroupSubsystem.h"
#include "TransitionOverlayWidget.h"

/////////////// Lifecycle ///////////////

MiniBoard::MiniBoard()
{
	SetIgnoreMouseInput(true);
	m_gridSizeX = 5;
	m_gridSizeY = 3;
}

MiniBoard::~MiniBoard()
{
	ResetBoard();
}

/////////////// Accessors ///////////////

bool MiniBoard::IsMiniBoard()
{
	return true;
}

/////////////// Logic ///////////////

bool MiniBoard::CanSaveGameState()
{
	return false;
}

void MiniBoard::ResetBoard()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTS); it; ++it)
	{
		Plant* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLANTS)->GetObjectForId(*it)->CastChecked<Plant>();
		object->Destroy();
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTGROUPS); it; ++it)
	{
		PlantGroup* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PLANTGROUPS)->GetObjectForId(*it)->CastChecked<PlantGroup>();
		object->Destroy();
	}
	GetPlantGroupSubsystem()->ClearData();
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		Zombie* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_ZOMBIES)->GetObjectForId(*it)->CastChecked<Zombie>();
		if (object)
			object->Destroy();
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GRIDITEMS); it; ++it)
	{
		GridItem* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_GRIDITEMS)->GetObjectForId(*it)->CastChecked<GridItem>();
		if (object)
			object->Destroy();
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROJECTILES); it; ++it)
	{
		Projectile* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_PROJECTILES)->GetObjectForId(*it)->CastChecked<Projectile>();
		object->Destroy();
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_COLLECTABLES); it; ++it)
	{
		Collectable* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_COLLECTABLES)->GetObjectForId(*it)->CastChecked<Collectable>();
		object->Destroy();
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BOARDENTITIES); it; ++it)
	{
		BoardEntity* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_BOARDENTITIES)->GetObjectForId(*it)->CastChecked<BoardEntity>();
		if (object)
			object->Destroy();
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_EFFECTOBJECTS); it; ++it)
	{
		EffectObject* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_EFFECTOBJECTS)->GetObjectForId(*it)->CastChecked<EffectObject>();
		if (object)
			object->Destroy();
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_EFFECTS); it; ++it)
	{
		GameObject* object = PVZDB::GetInstance().GetTable(PVZDB::TABLE_EFFECTS)->GetObjectForId(*it)->CastChecked<GameObject>();
		if (object)
			object->Destroy();
	}
	ClearZombie();
	SetIceHoleExist(false);
}

void MiniBoard::Update()
{
	if (IsPaused())
		return;
	UpdateGameObjects();
	if (m_animationMgr.IsValid())
		m_animationMgr->Update();
	ProcessDeleteQueue();
}

void MiniBoard::InitBoard()
{
	if (!m_animationMgr.IsValid())
	{
		m_animationMgr = AnimationMgr::Create()->GetPtr();
		m_animationMgr->ResetTime();
	}
	for (int i = 0; i < MAX_GRIDSIZEY; i++)
		m_plantRow[i] = PLANTROW_NORMAL;
	if (m_gridSizeY != 6)
		m_plantRow[5] = PLANTROW_DIRT;
	for (int x = 0; x < m_gridSizeX; x++)
		for (int y = 0; y < m_gridSizeY; y++)
			SetGridSquareType(x, y, GRIDSQUARE_GRASS);
	m_boardState = BOARDSTATE_PLAYING_LEVEL;
	EnableGridItems();
	InitPlantGroupSystem();
}

void MiniBoard::CloseBoard()
{
	m_boardState = BOARDSTATE_ENDLEVEL;
	PVZDB::GetInstance().RunDeferredDeletions();
	gMessageRouter->Unsubscribe(this);
	Unload();
}

Zombie* MiniBoard::SpawnZombie(ZombieTypePtr i_zombieType, int i_spawnedFromWave, SpawnZombieParams* pParams)
{
	return SpawnZombieHelper(i_zombieType, i_spawnedFromWave, false, pParams);
}

void MiniBoard::Pause(bool i_pauseGame)
{
	if (i_pauseGame)
	{
		if (!m_paused)
		{
			gMessageRouter->Post(&Message::GamePaused);
			gLawnApp->GetTransitionOverlay()->WillStopTransition();
		}
	}
	else if (m_paused)
	{
		gMessageRouter->Post(&Message::GameUnpaused);
	}
	m_paused = i_pauseGame;
}

void MiniBoard::Draw(Graphics* i_g)
{
	if (m_boardState == BOARDSTATE_ENDLEVEL)
		return;
	Rect clipRect(i_g->mClipRect);
	i_g->ClearClipRect();
	RenderQueue boardQueue(4096);
	RenderQueue uiQueue(256);
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PLANTS); it; ++it)
	{
		PlantPtr ptr = *it;
		ptr->AddToRenderQueue(&boardQueue);
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_ZOMBIES); it; ++it)
	{
		ZombiePtr ptr = *it;
		ptr->CastChecked<Zombie>()->AddToRenderQueue(&boardQueue);
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_PROJECTILES); it; ++it)
	{
		ProjectilePtr ptr = *it;
		ptr->CastChecked<Projectile>()->AddToRenderQueue(&boardQueue);
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_BOARDENTITIES); it; ++it)
	{
		BoardEntityPtr ptr = *it;
		ptr->CastChecked<BoardEntity>()->AddToRenderQueue(&boardQueue);
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_EFFECTOBJECTS); it; ++it)
	{
		StandaloneEffectPtr ptr = *it;
		ptr->CastChecked<StandaloneEffect>()->AddToRenderQueue(&boardQueue);
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_GRIDITEMS); it; ++it)
	{
		GridItemPtr ptr = *it;
		ptr->CastChecked<GridItem>()->AddToRenderQueue(&boardQueue);
	}
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_EFFECTS); it; ++it)
	{
		StandaloneEffectPtr ptr = *it;
		ptr->CastChecked<StandaloneEffect>()->AddToRenderQueue(&boardQueue);
	}
	const std::vector<RenderItem>& boardItems = boardQueue.GetSortedQueue();
	const std::vector<RenderItem>& uiItems = uiQueue.GetSortedQueue();
	SexyMatrix3 transform = MatrixPusher::CalcTransformMatrix(1.0f, 1.0f, 1.0f);
	DrawRenderQueuesInterleaved(boardItems, uiItems, transform, i_g);
	OutputDebugStrF("end draw");
	i_g->SetClipRect(clipRect);
}
