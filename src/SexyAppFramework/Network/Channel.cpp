//
//  Channel.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/NetworkServiceManager.h"

using namespace Sexy;

/////////////// Slots ///////////////

NetworkServiceManager::Slot* NetworkServiceManager::Channel::FreeSlot()
{
	for (Slots::iterator it = slots.begin(); it != slots.end(); ++it)
	{
		Slot* slot = &*it;
		if (slot->IsFree())
			return slot;
	}
	return NULL;
}
