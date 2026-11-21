//
//  fixed_pool_base.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include <EASTL/internal/fixed_pool.h>

namespace eastl
{

/////////////// Lifecycle ///////////////

void fixed_pool_base::init(void* pMemory, size_t memorySize, size_t nodeSize, size_t alignment, size_t /*alignmentOffset*/)
{
	if (pMemory)
	{
		if (alignment == 0)
			alignment = 1;
		const uintptr_t end = (uintptr_t)pMemory + memorySize;
		mpNext = (Link*)(((uintptr_t)pMemory + alignment - 1) & ~(alignment - 1));
		memorySize = end - (uintptr_t)mpNext;
		if (nodeSize < sizeof(Link))
			nodeSize = (sizeof(Link) + alignment - 1) & ~(alignment - 1);
		mnNodeSize = nodeSize;
		mpHead = NULL;
		mpCapacity = (Link*)((char*)mpNext + (memorySize / nodeSize) * nodeSize);
	}
}

}
