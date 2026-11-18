//
//  IPurchaseDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IPurchaseDriver.h"
#include "SexyAppFramework/drivers/purchase/android/AndroidPurchaseDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IPurchaseDriver* IPurchaseDriver::CreatePurchaseDriver(const std::string publicKey)
{
    return new AndroidPurchaseDriver();
}
