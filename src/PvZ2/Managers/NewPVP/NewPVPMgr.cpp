//
//  NewPVPMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "NewPVPGame.h"

/////////////// Lifecycle ///////////////

void NewPVPMgr::Update()
{
	updateFrameCalc();
}

bool NewPVPMgr::canStartFrameCalc()
{
	return m_nextFramesCalcTime == PVZ_EOT();
}
