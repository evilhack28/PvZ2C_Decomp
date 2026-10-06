//
//  GridItemCardGameTowerGenerateData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "AnimationMgr.h"
#include "RenderQueue.h"
#include "CardGameModule.h"

/////////////// GridItemCardGameTowerGenerateData ///////////////

GridItemCardGameTowerGenerateData::GridItemCardGameTowerGenerateData()
{
	Name = "";
	GridX = 0;
	GridY = 0;
}

GridItemCardGameTowerGenerateData::GridItemCardGameTowerGenerateData(const GridItemCardGameTowerGenerateData& other)
	: Name(other.Name)
	, GridX(other.GridX)
	, GridY(other.GridY)
{
}

GridItemCardGameTowerGenerateData::GridItemCardGameTowerGenerateData(GridItemCardGameTowerGenerateData&& other)
	: Name(static_cast<std::string&&>(other.Name))
	, GridX(other.GridX)
	, GridY(other.GridY)
{
}

GridItemCardGameTowerGenerateData::~GridItemCardGameTowerGenerateData()
{
}
