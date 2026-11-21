//
//  MetricsCollectorNameSpace.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "MetricsCollector.h"
#include "ProfileMgr.h"

/////////////// Accessors ///////////////

std::string MetricsCollectorNameSpace::GetPCPID()
{
	return ProfileMgr::GetInstance().GetAccountName();
}
