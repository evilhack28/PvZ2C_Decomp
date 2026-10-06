//
//  DRef.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "DRef.h"

/////////////// DRef ///////////////

DRef::DRef()
{
	m_refCount = 1;
}

DRef::DRef(const DRef &other)
{
	m_refCount = other.m_refCount;
}

DRef::~DRef()
{
}

void DRef::ref()
{
	m_refCount++;
}

void DRef::unref()
{
	m_refCount--;
	if (m_refCount == 0)
	{
		delete this;
	}
}
