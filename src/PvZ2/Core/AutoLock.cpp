//
//  AutoLock.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include <functional>

#include "AutoLock.h"

/////////////// AutoLock ///////////////

AutoLock::AutoLock(std::function<void()> lockfun, std::function<void()> unlockfun)
	: m_unlockfun(unlockfun)
{
	if (lockfun)
	{
		lockfun();
	}
}

AutoLock::~AutoLock()
{
	if (m_unlockfun)
	{
		m_unlockfun();
	}
}
