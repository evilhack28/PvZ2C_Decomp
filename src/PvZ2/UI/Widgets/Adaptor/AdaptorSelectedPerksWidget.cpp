//
//  AdaptorSelectedPerksWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorSelectedPerksWidget.h"

AdaptorSelectedPerksWidget::~AdaptorSelectedPerksWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorSelectedPerksWidget);

void AdaptorSelectedPerksWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorSelectedPerksWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<HotUIButton*>, m_selectedPerksButtons);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, m_selectedPerks);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_isInitializeTop);
		REFLECTION_CLASSBUILDER_FIELD(int, m_top);
	REFLECTION_CLASSBUILDER_END(AdaptorSelectedPerksWidget);
}
