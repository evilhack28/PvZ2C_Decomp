//
//  RenderQueue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "RenderQueue.h"

/////////////// RenderQueue ///////////////

bool RenderItemSortFunc(const RenderItem& i_a, const RenderItem& i_b)
{
	return i_a.m_zPos < i_b.m_zPos;
}

RenderQueue::RenderQueue(int i_reservedSize)
	: m_sorted(false)
{
	m_renderItems.reserve(i_reservedSize);
}

RenderQueue::~RenderQueue()
{
}

void RenderQueue::Add(int i_renderOrder, Sexy::Delegate1<Sexy::Graphics*> i_renderCall)
{
	m_renderItems.resize(m_renderItems.size() + 1);
	RenderItem& item = m_renderItems[m_renderItems.size() - 1];
	item.m_zPos = i_renderOrder;
	item.m_renderDelegate = i_renderCall;
}

const std::vector<RenderItem>& RenderQueue::GetSortedQueue()
{
	if (!m_sorted)
	{
		std::sort(m_renderItems.begin(), m_renderItems.end(), RenderItemSortFunc);
		m_sorted = true;
	}

	return m_renderItems;
}
