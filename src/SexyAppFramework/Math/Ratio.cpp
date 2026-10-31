//
//  Ratio.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "Ratio.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

Ratio::Ratio()
{
	mNumerator = 1;
	mDenominator = 1;
}

Ratio::Ratio(int theNumerator, int theDenominator)
{
	Set(theNumerator, theDenominator);
}

/////////////// Accessors ///////////////

void Ratio::Set(int theNumerator, int theDenominator)
{
	int a = theNumerator;
	int b = theDenominator;
	while (b != 0)
	{
		int c = a % b;
		a = b;
		b = c;
	}

	mNumerator = theNumerator / a;
	mDenominator = theDenominator / a;
}

float Ratio::Get()
{
	return (float)mNumerator / (float)mDenominator;
}
