//
//  DNodeWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "DNodeWidget.h"

void DNodeWidget::Initialize()
{
}

void DNodeWidget::UserInit()
{
}

void DNodeWidget::debugBtn()
{
}

DNodeWidget::~DNodeWidget()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DNodeWidget);

void DNodeWidget::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DNodeWidget);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Widget);

	REFLECTION_CLASSBUILDER_END(DNodeWidget);
}
