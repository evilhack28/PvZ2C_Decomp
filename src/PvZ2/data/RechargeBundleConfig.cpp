//
//  RechargeBundleConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RechargeBundleConfig.h"

RechargeBundleConfig::RechargeBundleConfig()
{
	bundleRefreshTime = (decltype(bundleRefreshTime))3600;
}

RechargeBundleConfig::~RechargeBundleConfig()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RechargeBundleConfig);

bool RechargeBundleConfig::IsBundleListSingleton(int bundleTypeId)
{
	return true;
}
