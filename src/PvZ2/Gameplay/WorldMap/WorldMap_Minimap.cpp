//
//  WorldMap_Minimap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_Minimap.h"

WorldMap_Minimap::WorldMap_Minimap()
{
	m_transformsNeedUpdate = 1;
}

WorldMap_Minimap::~WorldMap_Minimap()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(WorldMap_Minimap);

void WorldMap_Minimap::OnMouseUp(const int i_mouseX, const int i_mouseY)
{
}
