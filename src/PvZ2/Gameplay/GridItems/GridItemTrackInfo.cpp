//
//  GridItemTrackInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "RunningSubway.h"

/////////////// GridItemTrackInfo ///////////////

GridItemTrackInfo::GridItemTrackInfo()
{
}

GridItemTrackInfo::GridItemTrackInfo(GridItemPtr i_gridItem, Point i_location)
	: GridItem(i_gridItem)
	, Location(i_location)
{
}

GridItemTrackInfo::~GridItemTrackInfo() = default;

GridItemTrackInfo& GridItemTrackInfo::operator=(const GridItemTrackInfo& i_other) = default;

GridItemTrackInfo& GridItemTrackInfo::operator=(GridItemTrackInfo&& i_other) = default;
