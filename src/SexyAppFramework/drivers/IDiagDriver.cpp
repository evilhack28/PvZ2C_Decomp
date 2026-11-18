//
//  IDiagDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/IDiagDriver.h"
#include "SexyAppFramework/drivers/diag/android/AndroidDiagDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

IDiagDriver* IDiagDriver::CreateDiagDriver()
{
    return new AndroidDiagDriver();
}
