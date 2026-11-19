//
//  WorldMap_LuaButtonsImpl.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "WorldMap_LuaButtonsDelegate.h"

/////////////// Logic ///////////////

void WorldMap_LuaButtonsImpl::RegisterHandler(int nHandler)
{
	m_luaHandler = nHandler;
}
