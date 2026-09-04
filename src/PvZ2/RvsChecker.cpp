//
//  RvsChecker.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/StructuredData.h"

#include "RvsChecker.h"

static int RvsStatusValue(long value)
{
	return value;
}

/////////////// RvsChecker ///////////////

RvsChecker::RvsChecker()
{
	m_RvsStat = RvsState_None;
}

RvsChecker::~RvsChecker()
{
}

void RvsChecker::ServiceRequestCompleted(const Sexy::StructuredData* response, const void* context)
{
	int status = RvsStatusValue(response->IntegerForPath("$.status", -1));
	m_RvsStat = status == 0 ? RvsState_Sucess : RvsState_Failed;
}

void RvsChecker::ServiceRequestFailed(const Sexy::StructuredData* response, const void* context)
{
	m_RvsStat = RvsState_Failed;
}

void RvsChecker::StartCheckRvsStat()
{
	m_RvsStat = RvsState_Sucess;
}
