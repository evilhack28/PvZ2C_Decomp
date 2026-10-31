//
//  RtIdProtocol.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-31.
//
#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/RtDb.h"

using namespace Sexy;

RT_CLASS_IMPLEMENT(RtIdProtocol);

RtIdProtocol::GetRtIdDelegateType RtIdProtocol::GetDelegate()
{
	return mDelegate;
}

void RtIdProtocol::SetDelegate(const GetRtIdDelegateType& inDelegate)
{
	mDelegate = inDelegate;
}
