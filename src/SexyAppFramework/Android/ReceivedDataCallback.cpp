//
//  ReceivedDataCallback.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/http/android/AndroidHttpTransaction.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidHttpTransaction::ReceivedDataCallback::ReceivedDataCallback()
{
}

void AndroidHttpTransaction::ReceivedDataCallback::Func()
{
	transaction->OnReceivedData(data, dataSize);
	transaction->ReleaseReceivedDataCallback(this);
}
