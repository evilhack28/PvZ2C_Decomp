//
//  IShareDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "AndroidShareDriverMgr.h"
#include "IShareDriver.h"

/////////////// IShareDriver ///////////////

IShareDriver::IShareDriver()
{
}

IShareDriver* IShareDriver::CreateShareDriver()
{
	return new AndroidShareDriverMgr();
}
