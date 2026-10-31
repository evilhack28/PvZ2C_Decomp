//
//  MTRand.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "MTRand.h"

#include <stdlib.h>

namespace Sexy
{

static const unsigned long mag01[2] = {0x0, 0x9908b0df};
static int gRandDisallowCount = 0;

/////////////// Lifecycle ///////////////

MTRand::MTRand(const std::string& theSerialData)
{
	SRand(theSerialData);
	mti = MTRAND_N + 1;
}

MTRand::MTRand(unsigned long seed)
{
	SRand(seed);
}

MTRand::MTRand()
{
	SRand(4357);
}

/////////////// Seeding ///////////////

void MTRand::SRand(const std::string& theSerialData)
{
	std::string aString = theSerialData;

	int aPos = aString.find(' ');
	if (aPos != -1)
	{
		size_t aSeed = atoi(aString.substr(0, aPos).c_str());
		aString = aString.substr(aPos + 1, aString.size());

		int aPos2 = aString.find(' ');
		if (__builtin_expect(!!(aPos2 != -1), 1))
		{
			size_t aWrapCount = atoi(aString.substr(0, aPos2).c_str());
			aString = aString.substr(aPos2 + 1, aString.size());

			if (aString.size() != 0)
			{
				int anIndex = atoi(aString.c_str());

				SRand(aSeed);
				for (size_t i = 0; i != aWrapCount; i++)
				{
					mti = MTRAND_N;
					NextNoAssert();
				}
				mti = anIndex;
				goto done;
			}
		}
	}

	SRand(4357);
done:;
}

void MTRand::SRand(unsigned long seed)
{
	if (seed != 0)
	{
		mStartingSeed = seed;
		mWrapCount = 0;
		mt[0] = seed & 0xffffffff;
	}
	else
	{
		mStartingSeed = 4357;
		mWrapCount = 0;
		mt[0] = 4357;
	}

	unsigned long i;
	for (i = 1; i < MTRAND_N; i++)
		mt[i] = (1812433253UL * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i) & 0xffffffff;
	mti = i;
}

std::string MTRand::Serialize()
{
	return StrFormat("%u %u %d", mStartingSeed, mWrapCount, mti);
}

void MTRand::SetRandAllowed(bool allowed)
{
	if (allowed)
	{
		if (gRandDisallowCount > 0)
			gRandDisallowCount--;
	}
	else
		gRandDisallowCount++;
}

/////////////// Generation ///////////////

unsigned long MTRand::NextNoAssert()
{
	unsigned long y;

	if (mti >= MTRAND_N)
	{
		int kk;

		for (kk = 0; kk < MTRAND_N - 397; kk++)
		{
			y = (mt[kk] & 0x80000000) | (mt[kk + 1] & 0x7fffffff);
			mt[kk] = mt[kk + 397] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		for (; kk < MTRAND_N - 1; kk++)
		{
			y = (mt[kk] & 0x80000000) | (mt[kk + 1] & 0x7fffffff);
			mt[kk] = mt[kk + (397 - MTRAND_N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		y = (mt[MTRAND_N - 1] & 0x80000000) | (mt[0] & 0x7fffffff);
		mt[MTRAND_N - 1] = mt[396] ^ (y >> 1) ^ mag01[y & 0x1];

		mti = 0;
		mWrapCount++;
	}

	y = mt[mti++];
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680;
	y ^= (y << 15) & 0xefc60000;
	y ^= (y >> 18);

	return y & 0x7fffffff;
}

unsigned long MTRand::Next()
{
	return NextNoAssert();
}

unsigned long MTRand::NextNoAssert(unsigned long range)
{
	return NextNoAssert() % range;
}

unsigned long MTRand::Next(unsigned long range)
{
	return NextNoAssert(range);
}

unsigned long MTRand::Next(int range)
{
	return Next((unsigned long)range);
}

float MTRand::NextNoAssert(float range)
{
	return range * (1.0 / 2147483647.0) * NextNoAssert();
}

float MTRand::Next(float range)
{
	return NextNoAssert(range);
}

float MTRand::NextRange(float i_min, float i_max)
{
	return Next(i_max - i_min) + i_min;
}

}
