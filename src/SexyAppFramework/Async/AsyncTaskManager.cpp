//
//  AsyncTaskManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/AsyncTaskManager.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include "SexyAppFramework/SexyThread.h"

using namespace Sexy;

/////////////// Queues ///////////////

void AsyncTaskManager::AddTaskToQueue(IAsyncNetworkTask* const theTask, AsyncTaskQueue* const theQueue)
{
	if (theTask)
		theQueue->AddTask(theTask);
}

void AsyncTaskManager::stopWorkerThread()
{
}

AsyncTaskManager* AsyncTaskManager::DefaultAsyncTaskManager()
{
	NetworkServiceManager* aManager = NetworkServiceManager::TryDefaultNetworkServiceManager();
	if (aManager)
		return aManager->GetResumeRequestTaskManager();
	return NULL;
}

bool AsyncTaskManager::IsQueueEmpty(const std::string& theTaskQueueName) const
{
	AsyncTaskQueue* aQueue = GetQueueByName(theTaskQueueName);
	if (aQueue)
		return aQueue->IsQueueEmpty();
	return true;
}

void AsyncTaskManager::startWorkerThread()
{
	LaunchThread(workerThreadProc, this, STP_NORMAL);
}

void AsyncTaskManager::workerThreadProc(void* inUntypedAsyncTaskManagerPtr)
{
	((AsyncTaskManager*)inUntypedAsyncTaskManagerPtr)->workerThreadMainLoop();
}

AsyncTaskQueue* AsyncTaskManager::GetQueueByName(const std::string& theTaskQueueName) const
{
	for (std::list<AsyncTaskQueue*>::const_iterator anItr = mQueues.begin(); anItr != mQueues.end(); ++anItr)
	{
		if ((*anItr)->GetName().compare(theTaskQueueName) == 0)
			return *anItr;
	}
	return NULL;
}

AsyncTaskQueue* AsyncTaskManager::CreateQueue(const std::string& theTaskQueueName)
{
	AsyncTaskQueue* aQueue = GetQueueByName(theTaskQueueName);
	if (aQueue)
		return aQueue;

	AsyncTaskQueue* aNewQueue = new AsyncTaskQueue(theTaskQueueName);
	mQueues.push_back(aNewQueue);
	if ((int)mQueues.size() == 1)
		mLastQueueServiced = mQueues.begin();
	return aNewQueue;
}

void AsyncTaskManager::addWorkerThreadTask(IAsyncNetworkTask* inWorkerThreadTask)
{
	AutoCrit aCrit(mWorkerThreadQueueLock);
	mWorkerThreadTasks.push_back(inWorkerThreadTask);
	inWorkerThreadTask->SetPendingRunState();
	mWorkerThreadTasksAvailableEvent.Notify();
}

bool AsyncTaskManager::moveToNextQueue()
{
	bool aResult = false;
	if (!mQueues.empty())
	{
		++mLastQueueServiced;
		if (mLastQueueServiced == mQueues.end())
			mLastQueueServiced = mQueues.begin();
		aResult = mLastQueueServiced != mQueues.end();
	}
	return aResult;
}

bool AsyncTaskManager::moveToPrevQueue()
{
	bool aResult = false;
	if (!mQueues.empty())
	{
		if (mLastQueueServiced == mQueues.begin())
			mLastQueueServiced = mQueues.end();
		--mLastQueueServiced;
		aResult = mLastQueueServiced != mQueues.end();
	}
	return aResult;
}

void AsyncTaskManager::workerThreadMainLoop()
{
	for (;;)
	{
		IAsyncNetworkTask* aTask = NULL;
		{
			AutoCrit aCrit(mWorkerThreadQueueLock);
			if (!mWorkerThreadTasks.empty())
				aTask = mWorkerThreadTasks.front();
			else
				mWorkerThreadTasksAvailableEvent.Reset();
		}

		if (aTask)
		{
			aTask->Run();

			AutoCrit aCrit(mWorkerThreadQueueLock);
			mWorkerThreadTasks.pop_front();
		}
		else
			mWorkerThreadTasksAvailableEvent.Wait(100000);
	}
}

AsyncTaskManager::~AsyncTaskManager()
{
	stopWorkerThread();
}

void AsyncTaskManager::AddTaskToQueue(IAsyncNetworkTask* const theTask, const std::string& theTaskQueueName)
{
	for (std::list<AsyncTaskQueue*>::iterator anItr = mQueues.begin(); anItr != mQueues.end(); ++anItr)
	{
		if ((*anItr)->GetName().compare(theTaskQueueName) == 0)
		{
			AddTaskToQueue(theTask, *anItr);
			return;
		}
	}
}

void AsyncTaskManager::RequestQueueDelete(AsyncTaskQueue* inTaskQueueToDelete)
{
	if (*mLastQueueServiced == inTaskQueueToDelete)
		moveToPrevQueue();

	inTaskQueueToDelete->Clear();
	mQueues.erase(std::find(mQueues.begin(), mQueues.end(), inTaskQueueToDelete));
	if (mQueues.empty())
		mLastQueueServiced = mQueues.end();

	delete inTaskQueueToDelete;
}

void AsyncTaskManager::Update()
{
	std::vector<IAsyncNetworkTask*> aMainThreadTasks;

	for (int i = 0; i < (int)mQueues.size(); i++)
	{
		moveToNextQueue();
		(*mLastQueueServiced)->Update();

		IAsyncNetworkTask::State aState = (*mLastQueueServiced)->GetState();
		if (aState == IAsyncNetworkTask::State_SuccessComplete || aState == IAsyncNetworkTask::State_ErrorComplete)
		{
			RequestQueueDelete(*mLastQueueServiced);
		}
		else if ((*mLastQueueServiced)->HasPendingErrorTask())
		{
			bool aDone = (*mLastQueueServiced)->GetTasks().empty();
			if (!aDone)
			{
				IAsyncNetworkTask::State aFrontState = (*mLastQueueServiced)->GetTasks().front()->GetState();
				aDone = aFrontState == IAsyncNetworkTask::State_SuccessComplete || aFrontState == IAsyncNetworkTask::State_ErrorComplete;
			}
			if (aDone)
			{
				(*mLastQueueServiced)->RemoveCompletedTasks();
				(*mLastQueueServiced)->NotifyPendingTasksOfError();
				IAsyncNetworkTask* aTask = (*mLastQueueServiced)->GetPendingErrorTask();
				aMainThreadTasks.push_back(aTask);
			}
		}
		else
		{
			(*mLastQueueServiced)->RemoveCompletedTasks();
			IAsyncNetworkTask* aTask = (*mLastQueueServiced)->GetNextTask();
			if (aTask)
			{
				if (aTask->IsMainThreadTask())
				{
					aTask->SetPendingRunState();
					aMainThreadTasks.push_back(aTask);
				}
				else
					addWorkerThreadTask(aTask);
			}
		}
	}

	for (std::vector<IAsyncNetworkTask*>::iterator anItr = aMainThreadTasks.begin(); anItr != aMainThreadTasks.end(); ++anItr)
		(*anItr)->Run();
}
