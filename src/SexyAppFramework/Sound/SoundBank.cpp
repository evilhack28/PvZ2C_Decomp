//
//  SoundBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-06.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/SoundBank.h"
#include "ReflectionBuilder.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

SoundBank* SoundBank::Create()
{
	RtClass* aClass = RtClass::StaticGetClassNamed("WwiseSoundBank");
	if (aClass != NULL && aClass->IsDerivedFrom<SoundBank>())
		return aClass->New()->Cast<SoundBank>();
	return NULL;
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT_ABSTRACT(SoundBank);
