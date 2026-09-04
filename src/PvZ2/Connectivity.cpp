//
//  Connectivity.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/IHttpDriver.h"
#include "SexyAppFramework/SexyApp.h"

using namespace Sexy;

#include "Connectivity.h"

/////////////// Connectivity ///////////////

bool Connectivity::IsConnectedOnWifi()
{
	return gSexyApp->mHttpDriver->GetNetworkStatus() == IHttpDriver::NET_REACHABLE_WIFI;
}

bool Connectivity::IsConnectedOnEthernet()
{
	return gSexyApp->mHttpDriver->GetNetworkStatus() == IHttpDriver::NET_REACHABIE_ETHERNET;
}

bool Connectivity::IsConnectedOnWWAN()
{
	return gSexyApp->mHttpDriver->GetNetworkStatus() == IHttpDriver::NET_REACHABLE_WWAN;
}

bool Connectivity::IsConnected()
{
	if (IsConnectedOnWifi())
	{
		return true;
	}
	if (IsConnectedOnWWAN())
	{
		return true;
	}

	return IsConnectedOnEthernet();
}
