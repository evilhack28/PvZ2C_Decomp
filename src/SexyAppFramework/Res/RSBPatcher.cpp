//
//  RSBPatcher.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/IFileDriver.h"
#include "SexyAppFramework/SexyThread.h"
#include "open_vcdiff/google/vcdecoder.h"

using namespace Sexy;


/////////////// Lifecycle ///////////////

RSBPatcher::RSBPatcher(SexyAppBase* inApp, IRSBPatcherListener* inListener, void* inListenerContext)
{
    Init(inApp, inListener, inListenerContext);
}

RSBPatcher::RSBPatcher(SexyAppBase* inApp)
{
    Init(inApp, NULL, NULL);
}

void RSBPatcher::Init(SexyAppBase* inApp, IRSBPatcherListener* inListener, void* inListenerContext)
{
    mApp = inApp;
    mListener = inListener;
    mListenerContext = inListenerContext;
    mStatus = Status_Invalid;
    mHaveProcessedFirstUpdateSinceStart = false;
    mIsPatchRunning = false;
    mTargetRsbBytesProcessed = 0;
    mTotalTargetRsbByteCount = 100000;
}


/////////////// Status ///////////////

RSBPatcher::Status RSBPatcher::GetStatus() const
{
    AutoCrit aCrit(mCritSect);
    return mStatus;
}

void RSBPatcher::SetStatus(Status inStatus)
{
    AutoCrit aCrit(mCritSect);
    mStatus = inStatus;
}

RSBPatcher::ErrorReason RSBPatcher::GetErrorReason() const
{
    AutoCrit aCrit(mCritSect);
    return mErrorReason;
}

void RSBPatcher::SetErrorReason(ErrorReason inReason)
{
    AutoCrit aCrit(mCritSect);
    mErrorReason = inReason;
}

bool RSBPatcher::IsCancelRequested()
{
    return GetStatus() == Status_Canceling;
}

void RSBPatcher::Cancel()
{
    SetStatus(Status_Canceling);
}

bool RSBPatcher::IsFinished() const
{
    return !mIsPatchRunning;
}

float RSBPatcher::GetProgress() const
{
    AutoCrit aCrit(mCritSect);
    return (float)((double)mTargetRsbBytesProcessed / (double)mTotalTargetRsbByteCount);
}

void RSBPatcher::IncrementTargetRsbBytesProcessed(uint64 inDeltaByteCount)
{
    AutoCrit aCrit(mCritSect);
    mTargetRsbBytesProcessed += inDeltaByteCount;
    if (mTargetRsbBytesProcessed > mTotalTargetRsbByteCount)
        mTargetRsbBytesProcessed = mTotalTargetRsbByteCount;
}


/////////////// Patching ///////////////

void RSBPatcher::Start(const std::string& inBaseRsbFilePath, const std::string& inRsbPatchFilePath, const std::string& inPatchedRsbFilePath)
{
    mBaseRsbFilePath = inBaseRsbFilePath;
    mRsbPatchFilePath = inRsbPatchFilePath;
    mPatchedRsbFilePath = inPatchedRsbFilePath;
    SetStatus(Status_Patching);
    mHaveProcessedFirstUpdateSinceStart = false;
    mTargetRsbBytesProcessed = 0;
    mIsPatchRunning = true;
    mTotalTargetRsbByteCount = 100000;
    LaunchThread(SynchroniousRSBPatchThreadProc, this, STP_NORMAL);
}

void RSBPatcher::Update()
{
    if (!mIsPatchRunning)
        return;

    Status aStatus = GetStatus();
    if (!mHaveProcessedFirstUpdateSinceStart)
    {
        mHaveProcessedFirstUpdateSinceStart = true;
        if (aStatus != Status_Error)
            mListener->PatchStarted(this, mListenerContext);
    }

    switch (aStatus)
    {
    case Status_Error:
        mIsPatchRunning = false;
        mListener->PatchError(this, mListenerContext);
        break;
    case Status_Canceled:
        mIsPatchRunning = false;
        mListener->PatchCanceled(this, mListenerContext);
        break;
    case Status_Complete:
        mIsPatchRunning = false;
        mListener->PatchComplete(this, mListenerContext);
        break;
    }
}

void RSBPatcher::SynchroniousRSBPatchThreadProc(void* inContext)
{
    ((RSBPatcher*)inContext)->SynchroniousRSBPatch();
}

void RSBPatcher::SynchroniousRSBPatch()
{
    bool aSucceeded = ApplyPatch(mBaseRsbFilePath, mRsbPatchFilePath, mPatchedRsbFilePath);
    if (IsCancelRequested())
        SetStatus(Status_Canceled);
    else if (!aSucceeded)
        SetStatus(Status_Error);
    else
        SetStatus(Status_Complete);
}

bool RSBPatcher::ApplyPatch(const std::string& inBaseRsbFilePath, const std::string& inRsbPatchFilePath, const std::string& inPatchedRsbFilePath)
{
    bool aSucceeded = ApplyPatchHelper(inBaseRsbFilePath, inRsbPatchFilePath, inPatchedRsbFilePath);
    if (!aSucceeded && mApp->mFileDriver->FileExists(inPatchedRsbFilePath))
        mApp->mFileDriver->DeleteFile(inPatchedRsbFilePath);
    return aSucceeded;
}


/////////////// Diff ///////////////

bool RSBPatcher::ApplyDiff(uint8* inBaseData, uint64 inBaseDataByteCount, uint8* inPatchData, uint64 inPatchDataByteCount, std::string& outTargetData)
{
    std::string aPatchData((const char*)inPatchData, inPatchDataByteCount);
    open_vcdiff::VCDiffStreamingDecoder aDecoder;
    open_vcdiff::OutputString<std::string> aOutput(&outTargetData);
    aOutput.clear();
    if (inBaseDataByteCount > 0x4000000)
    {
        aDecoder.SetMaximumTargetWindowSize(inBaseDataByteCount);
        aDecoder.SetMaximumTargetFileSize(inBaseDataByteCount);
    }
    aDecoder.StartDecoding((const char*)inBaseData, inBaseDataByteCount);
    bool aResult = aDecoder.DecodeChunkToInterface(aPatchData.data(), aPatchData.size(), &aOutput);
    if (aResult)
        aResult = aDecoder.FinishDecoding();
    return aResult;
}
