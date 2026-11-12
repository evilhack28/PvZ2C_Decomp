//
//  Android_aio.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//
#include "SexyAppFramework/Common.h"
#include "drivers/file/android/Android_aio.h"
#include "drivers/file/android/AndroidAsyncIOFileDriver.h"
#include <errno.h>

/////////////// Read ///////////////

int AndroidAIO::aio_read(aiocb* pContext)
{
	__atomic_store_n(&pContext->return_code, EINVAL, __ATOMIC_RELEASE);
	__atomic_store_n(&pContext->error_code, EINPROGRESS, __ATOMIC_RELEASE);
	return pContext->pAsyncDriver->SubmitAsyncRead(pContext);
}
