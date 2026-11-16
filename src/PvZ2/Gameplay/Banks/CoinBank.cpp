//
//  CoinBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CoinBank.h"

void CoinBank::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CoinBank);

void CoinBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CoinBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(bool, m_showPlusButton);
	REFLECTION_CLASSBUILDER_END(CoinBank);
}
