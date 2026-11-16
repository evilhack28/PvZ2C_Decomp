//
//  DraperSaveData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DraperSaveData.h"
#include "ReflectionBuilder.h"

/////////////// Lifecycle ///////////////

DraperSaveData::~DraperSaveData()
{
}

DraperSaveData::DraperSaveData()
	: m_lastSessionPlayTime(-1)
	, m_lastPlayTime(-1)
	, m_lastPurchaseTime(-1)
	, m_transactionCount(0)
	, m_purchaseTotal(0.0f)
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(DraperSaveData);

void DraperSaveData::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DraperSaveData);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_FIELD_RENAME(time_t, m_lastSessionPlayTime, lspt);
			REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(PropGrid.Hide, "");
		REFLECTION_CLASSBUILDER_FIELD_RENAME(time_t, m_lastPlayTime, lpt);
			REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(PropGrid.Hide, "");
		REFLECTION_CLASSBUILDER_FIELD_RENAME(time_t, m_lastPurchaseTime, lpurt);
			REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(PropGrid.Hide, "");
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_transactionCount, tcnt);
			REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(PropGrid.Hide, "");
		REFLECTION_CLASSBUILDER_FIELD_RENAME(float, m_purchaseTotal, pttl);
			REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(PropGrid.Hide, "");
		REFLECTION_CLASSBUILDER_FIELD_RENAME(time_t, m_index, idx);
			REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(PropGrid.Hide, "");

	REFLECTION_CLASSBUILDER_END(DraperSaveData);
}

/////////////// Accessors ///////////////

void DraperSaveData::SetLastPlayTime(time_t i_time)
{
	m_lastSessionPlayTime = i_time;
	m_lastPlayTime = i_time;
	DraperHelpers::SaveLocalDraperState(m_index);
}

void DraperSaveData::SetLastPurchaseTimeAndCountAndTotal(time_t i_time, int i_transCnt, int i_purchaseTotal)
{
	m_lastPurchaseTime = i_time;
	m_transactionCount = i_transCnt;
	m_purchaseTotal = (float)i_purchaseTotal;
	DraperHelpers::SaveLocalDraperState(m_index);
}
