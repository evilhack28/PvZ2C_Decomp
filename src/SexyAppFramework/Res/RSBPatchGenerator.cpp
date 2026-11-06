//
//  RSBPatchGenerator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "open_vcdiff/google/vcencoder.h"

using namespace Sexy;


/////////////// Lifecycle ///////////////

RSBPatchGenerator::RSBPatchGenerator(SexyAppBase* inApp)
{
    mApp = inApp;
}
