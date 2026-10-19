//
//  PrimeAllocator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/Prime_EATech_Bridge.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PrimeAllocator::PrimeAllocator()
{
}

/////////////// Allocation ///////////////

void* PrimeAllocator::Alloc(size_t size, const char* /*name*/, unsigned /*flags*/)
{
	return new char[size];
}

void* PrimeAllocator::Alloc(size_t size, const char* /*name*/, unsigned /*flags*/, unsigned /*align*/, unsigned /*alignOffset*/)
{
	return new char[size];
}

void PrimeAllocator::Free(void* ptr, size_t /*size*/)
{
	if (ptr)
		delete[] static_cast<char*>(ptr);
}
