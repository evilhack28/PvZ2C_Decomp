//
//  PVPManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "PVPManager.h"

/////////////// Accessors ///////////////

bool PVPManager::IsInPVPMap()
{
	return m_mapType != 0;
}
