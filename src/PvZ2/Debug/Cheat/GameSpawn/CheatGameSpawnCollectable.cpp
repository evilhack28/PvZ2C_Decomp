//
//  CheatGameSpawnCollectable.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-16.
//

#include "SexyAppFramework/Common.h"

#include "PVZCheats.h"

/////////////// Reflection ///////////////

bool CheatGameSpawnCollectable::IsAbstract() const
{
	return false;
}

RtClass* CheatGameSpawnCollectable::GetClass() const
{
	return StaticGetClass();
}
