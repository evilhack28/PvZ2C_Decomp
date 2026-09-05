//
//  NetworkStatusDecider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "NetworkStatusDecider.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IHttpDriver.h"

/////////////// NetworkStatusDecider ///////////////

NetworkStatusDecider::NetworkStatusDecider(std::ostream& os)
	: m_os(os)
{
}

const bool NetworkStatusDecider::ShouldSendNetworkRequest() const
{
	if (!networkReachable())
		return false;

	if (!areMetricsEnabled())
		return false;

	return true;
}

const bool NetworkStatusDecider::networkReachable() const
{
	return Sexy::gSexyAppBase->mHttpDriver->GetNetworkStatus() != Sexy::IHttpDriver::NET_NOT_REACHABLE;
}

const bool NetworkStatusDecider::areMetricsEnabled() const
{
	return true;
}
