//
//  Thread.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include <eathread/eathread_callstack.h>

namespace EA
{
namespace Thread
{

bool GetPthreadStackInfo(void** pBase, void** pLimit);

/////////////// Stack ///////////////

void* GetStackLimit()
{
	void* pLimit;
	if (GetPthreadStackInfo(NULL, &pLimit))
		return pLimit;
	return (void*)((uintptr_t)__builtin_frame_address(0) & ~(uintptr_t)4095);
}

} // namespace Thread
} // namespace EA
