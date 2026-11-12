//
//  BaseDiagDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/diag/BaseDiagDriver.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

BaseDiagDriver::BaseDiagDriver()
{
	mInfoString = NULL;
	mInfoStringCapacity = 0;
}

BaseDiagDriver::~BaseDiagDriver()
{
	if (mInfoString)
		free(mInfoString);
}

/////////////// Info ///////////////

double BaseDiagDriver::GetInfoNumber(EInfoNumberType inType)
{
	return 0;
}

const char* BaseDiagDriver::EnsureInfoStringCapacity(size_t length)
{
	if (!mInfoString || mInfoStringCapacity < length)
	{
		mInfoStringCapacity = length;
		mInfoString = (char*)realloc(mInfoString, length + 1);
	}
	return mInfoString;
}

const char* BaseDiagDriver::GetInfoStringSafe(EInfoStringType inType)
{
	const char* infoString = GetInfoString(inType);
	if (infoString)
		return infoString;
	EnsureInfoStringCapacity(1);
	mInfoString[0] = 0;
	return mInfoString;
}
