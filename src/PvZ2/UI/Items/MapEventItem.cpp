//
//  MapEventItem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "MapEventItem.h"

void MapEventItem::DrawMapAdventurePlant(Sexy::Graphics* i_g, WorldMapCamera* i_camera)
{
}

uint16 MapEventItem::GetEventId() const
{
	return m_eventId;
}

void MapEventItem::ResetPointers()
{
	m_parent = NULL;
	m_unlockedFromEvent = NULL;
	m_visibleFromEvent = NULL;
	m_worldDataPtr = NULL;
	m_children.clear();
}

void MapEventItem::SetParentEventPtr(MapEventItem* i_ptr)
{
	if (m_parent)
		m_parent->RemoveChild(this);
	m_parent = i_ptr;
	if (m_parent)
		m_parent->AddChild(this);
}
