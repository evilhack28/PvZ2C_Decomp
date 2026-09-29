//
//  PVPSeedChooser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVPSeedChooser.h"

bool PVPSeedChooser::isBlacklisted(const std::string& i_arg)
{
	return false;
}

#include "PVPSeedChooser.h"
void PVPSeedChooser::onCheatEnabled()
{
	 PVPSeedChooser::rebuildSeedList();
}

#include "PVPSeedChooser.h"
void PVPSeedChooser::onCheatDisabled()
{
	 PVPSeedChooser::rebuildSeedList();
}

#include "SeedChooser.h"
void PVPSeedChooser::VerifyAndSelectSeeds()
{
	 SeedChooser::sendBorrowRequestBeforeFinalize();
}
