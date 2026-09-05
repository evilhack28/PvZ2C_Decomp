//
//  GridItemPlacement.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "InitialGridItemPlacer.h"

/////////////// GridItemPlacementProperties ///////////////

GridItemPlacementProperties::GridItemPlacementProperties()
{
	GridX = -1;
	GridY = -1;
}

GridItemPlacementProperties::GridItemPlacementProperties(const GridItemPlacementProperties& i_other) = default;

GridItemPlacementProperties::GridItemPlacementProperties(GridItemPlacementProperties&& i_other) = default;

GridItemPlacementProperties::~GridItemPlacementProperties() = default;
