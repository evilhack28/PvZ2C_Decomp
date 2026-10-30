//
//  MissionEndItem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "Board.h"

/////////////// Lifecycle ///////////////

Board::MissionEndItem::MissionEndItem()
{
}

Board::MissionEndItem::~MissionEndItem()
{
}

Board::MissionEndItem::MissionEndItem(MissionEndItem&& i_other)
	: itemName(static_cast<std::string&&>(i_other.itemName))
	, buy(i_other.buy)
{
}
