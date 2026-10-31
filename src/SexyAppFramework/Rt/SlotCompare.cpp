//
//  SlotCompare.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtDb.h"

using namespace Sexy;

/////////////// Sorting ///////////////

int RtDbTable::SlotCompare::Func(const void* a, const void* b)
{
	Slot* slotA = *(Slot**)a;
	Slot* slotB = *(Slot**)b;
	if (slotA->mRefCountAndFlags & Slot::SLOTF_Used)
	{
		size_t result = -1;
		if (slotB->mRefCountAndFlags & Slot::SLOTF_Used)
			result = sSortCurDelegate(sSortCurTable->GetIdForSlot(slotA), sSortCurTable->GetIdForSlot(slotB));
		return result;
	}
	return slotB->mRefCountAndFlags >> 31;
}
