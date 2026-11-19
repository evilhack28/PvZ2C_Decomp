//
//  AsyncTaskManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/AsyncTaskManager.h"

using namespace Sexy;

/////////////// Queues ///////////////

void AsyncTaskManager::AddTaskToQueue(IAsyncNetworkTask* const theTask, AsyncTaskQueue* const theQueue)
{
	if (theTask)
		theQueue->AddTask(theTask);
}
