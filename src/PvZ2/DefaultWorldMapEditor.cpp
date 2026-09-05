//
//  DefaultWorldMapEditor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "DefaultWorldMapEditor.h"
#include "MapEventItem.h"
#include "ParallaxCache.h"

/////////////// DefaultWorldMapEditor ///////////////

DefaultWorldMapEditor::DefaultWorldMapEditor()
{
}

void DefaultWorldMapEditor::SetDrawColor(Sexy::Graphics* i_g)
{
}

void DefaultWorldMapEditor::DrawDarkBackground(Sexy::Graphics* i_g, int i_x, int i_y, int i_width, int i_height)
{
}

void DefaultWorldMapEditor::DrawMapLayers(Sexy::Graphics* i_g, std::vector<MapRenderItem>& i_mapRenderList, WorldMapCamera* i_camera, ParallaxCache& i_parallaxCache)
{
	i_g->SetColorizeImages(false);

	for (size_t i = 0; i < i_mapRenderList.size(); i++)
	{
		MapEventItem* mapEventItem = i_mapRenderList[i].m_mapEventItem;
		mapEventItem->DrawIslandLayer(i_g, i_camera, i_parallaxCache.GetOffsetForLayer(mapEventItem->m_parallaxLayer));
	}
}
