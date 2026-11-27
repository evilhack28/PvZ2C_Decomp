//
//  Thread.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include <eathread/eathread_callstack.h>
#include <eathread/android/eathread_atomic_android.h>
#include <pthread.h>

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

/////////////// Fake 64-bit atomics ///////////////

static pthread_mutex_t sFakeAtomic64Locks[32];

int64_t android_fake_atomic_swap_64(int64_t value, volatile int64_t* addr)
{
	pthread_mutex_t* lock = &sFakeAtomic64Locks[((uintptr_t)addr >> 3) % 32];
	pthread_mutex_lock(lock);
	int64_t oldValue = *addr;
	*addr = value;
	pthread_mutex_unlock(lock);
	return oldValue;
}

int android_fake_atomic_cmpxchg_64(int64_t oldvalue, int64_t newvalue, volatile int64_t* addr)
{
	pthread_mutex_t* lock = &sFakeAtomic64Locks[((uintptr_t)addr >> 3) % 32];
	int result;
	pthread_mutex_lock(lock);
	if (*addr == oldvalue)
	{
		*addr = newvalue;
		result = 0;
	}
	else
		result = 1;
	pthread_mutex_unlock(lock);
	return result;
}

int64_t android_fake_atomic_read_64(volatile int64_t* addr)
{
	pthread_mutex_t* lock = &sFakeAtomic64Locks[((uintptr_t)addr >> 3) % 32];
	pthread_mutex_lock(lock);
	int64_t value = *addr;
	pthread_mutex_unlock(lock);
	return value;
}

} // namespace Thread
} // namespace EA
