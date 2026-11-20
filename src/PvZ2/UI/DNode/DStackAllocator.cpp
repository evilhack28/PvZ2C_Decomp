//
//  DStackAllocator.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "DNode/DStackAllocator.h"

/////////////// Lifecycle ///////////////

DStackAllocator::DStackAllocator()
{
	m_index = 0;
	m_allocation = 0;
	m_maxAllocation = 0;
	m_entryCount = 0;
}

DStackAllocator::~DStackAllocator()
{
	popAll();
}

DStackAllocator* DStackAllocator::getInstance()
{
	if (sp_stackAllocator)
		return sp_stackAllocator;

	sp_stackAllocator = new DStackAllocator();
	return sp_stackAllocator;
}

void DStackAllocator::purge()
{
	if (sp_stackAllocator)
	{
		delete sp_stackAllocator;
		sp_stackAllocator = nullptr;
	}
}

/////////////// Stack ///////////////

void DStackAllocator::pop()
{
	DStackEntry* entry = m_entries + m_entryCount - 1;
	if (entry->usedMalloc)
	{
		delete[] entry->data;
	}
	else
	{
		m_index -= entry->size;
	}

	m_entryCount--;
	m_allocation -= entry->size;
	entry->data = nullptr;
}

void DStackAllocator::pop(size_t num)
{
	if (num > m_entryCount)
		num = m_entryCount;

	for (size_t i = 0; i < num; i++)
		pop();
}

/////////////// Accessors ///////////////

size_t DStackAllocator::getMaxAllocation() const
{
	return m_maxAllocation;
}
