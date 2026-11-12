//
//  AndroidDiagDriver.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-07.
//
//  HWBRK's members and the static thread function th have no name in the game; their names here are not real.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/diag/android/AndroidDiagDriver.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "drivers/app/android/AndroidAppDriver.h"
#include "drivers/app/android/JavaInterface.h"

using namespace Sexy;

/////////////// Helpers ///////////////

namespace Sexy
{
	class HWBRK
	{
	public:
		void* a;
		pthread_t hT;
		IDiagDriver::EHardwareBreakpointType Type;
		int Size;
		Condition* hEv;
		int iReg;
		bool Opr;
		bool SUCC;

		HWBRK()
		{
			Opr = 0;
			a = 0;
			hT = 0;
			hEv = 0;
			iReg = 0;
			SUCC = false;
		}
	};
}

static void* th(void* lpParameter)
{
	return NULL;
}

/////////////// Lifecycle ///////////////

AndroidDiagDriver::AndroidDiagDriver()
{
}

AndroidDiagDriver::~AndroidDiagDriver()
{
}

bool AndroidDiagDriver::Init()
{
	return true;
}

void AndroidDiagDriver::Update()
{
}

/////////////// Info ///////////////

const char* AndroidDiagDriver::GetInfoString(EInfoStringType inType)
{
	switch (inType)
	{
	case INFO_OSVersion:
	{
		std::string str;
		Android::Diag::GetOSVersion(str);
		EnsureInfoStringCapacity(str.length());
		strcpy(mInfoString, str.c_str());
		return mInfoString;
	}
	case INFO_HardwareModel:
	{
		std::string str;
		Android::Diag::GetHardwareModel(str);
		EnsureInfoStringCapacity(str.length());
		strcpy(mInfoString, str.c_str());
		return mInfoString;
	}
	case INFO_DeviceID:
	{
		std::string str;
		Android::Diag::GetPrimaryMACAddress(str);
		EnsureInfoStringCapacity(str.length());
		strcpy(mInfoString, str.c_str());
		return mInfoString;
	}
	}
	return NULL;
}

double AndroidDiagDriver::GetInfoNumber(EInfoNumberType inType)
{
	switch (inType)
	{
	case INFO_MemoryUsed:
		return ((AndroidAppDriver*)gSexyAppBase->mAppDriver)->GetMemoryUsed();
	case INFO_MemoryAvailable:
		return ((AndroidAppDriver*)gSexyAppBase->mAppDriver)->GetMemoryAvailable();
	}
	return 0;
}

/////////////// Hardware breakpoints ///////////////

AndroidDiagDriver::HHardwareBreakpoint AndroidDiagDriver::SetHardwareBreakpoint(EHardwareBreakpointType inType, void* inAddr, int inSizeBytes)
{
	pthread_t thread = pthread_self();
	HWBRK* h = new HWBRK;
	h->a = inAddr;
	h->Type = inType;
	h->Size = inSizeBytes;
	h->hT = thread;
	h->hEv = new Condition;
	h->Opr = false;
	pthread_t hY;
	if (pthread_create(&hY, NULL, th, h) != 0)
		return NULL;
	h->hEv->Wait(-1);
	delete h->hEv;
	h->hEv = NULL;
	if (!h->SUCC)
	{
		delete h;
		return NULL;
	}
	return h;
}

bool AndroidDiagDriver::ClearHardwareBreakpoint(HHardwareBreakpoint inHandle)
{
	HWBRK* h = (HWBRK*)inHandle;
	if (!h)
		return false;
	h->hEv = new Condition;
	h->Opr = true;
	pthread_t hY;
	if (pthread_create(&hY, NULL, th, h) != 0)
		return false;
	h->hEv->Wait(-1);
	delete h->hEv;
	h->hEv = NULL;
	delete h;
	return true;
}

/////////////// Call stack ///////////////

int AndroidDiagDriver::GetCallStack(void** outCallStack, int inNumStackElements)
{
	return 0;
}

bool AndroidDiagDriver::GetTextForCallStack(void** inCallStack, int inNumStackElements, std::string* ioStrings)
{
	return false;
}
