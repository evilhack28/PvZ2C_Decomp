// PvZ2/Core/Prime/PrimeText_PotentialTypefaceDictionary.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28.
//

#include "SexyAppFramework/Common.h"

#include "PrimeText_PotentialTypeface.h"

static std::string s_DefaultTypeface;

/////////////// Typefaces ///////////////

void PrimeText_PotentialTypefaceDictionary::SetDefaultTypeface(const std::string& i_name)
{
	s_DefaultTypeface = i_name;
}

PrimeTypeface* PrimeText_PotentialTypefaceDictionary::GetTypeface(const std::string& i_name)
{
	return GetPotentialTypeface(i_name)->Typeface();
}
