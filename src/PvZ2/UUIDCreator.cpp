//
//  UUIDCreator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "UUIDCreator.h"

#include "SexyAppFramework/drivers/app/android/JavaInterface.h"

/////////////// UUIDCreator ///////////////

UUIDCreator::UUIDCreator()
{
}

std::string UUIDCreator::Create()
{
	return Android::Util::GetUUIDString();
}
