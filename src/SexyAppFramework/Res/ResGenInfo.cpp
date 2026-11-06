//
//  ResGenInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResourceManager.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////
ResGenInfo::ResGenInfo()
{
	mRgMajorVersion = 3;
	mRgMinorVersion = 0;
	mRgTargetName = "windows";
}

ResGenInfo::~ResGenInfo()
{
}

ResGenInfo& ResGenInfo::operator=(const ResGenInfo&) = default;
