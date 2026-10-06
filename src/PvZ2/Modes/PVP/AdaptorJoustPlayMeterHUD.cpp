//
//  AdaptorJoustPlayMeterHUD.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorJoustPlayMeterHUD.h"

AdaptorJoustPlayMeterHUD::~AdaptorJoustPlayMeterHUD()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorJoustPlayMeterHUD);

void AdaptorJoustPlayMeterHUD::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorJoustPlayMeterHUD);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorJoustPlayMeterHUD);
}

#include "HotUIAdaptor.h"
void AdaptorJoustPlayMeterHUD::onLayoutFinished()
{
	 HotUIAdaptor::GetEntryPointWidget();
}

#include "AdaptorJoustPlayMeterHUD.h"
void AdaptorJoustPlayMeterHUD::Update()
{
	 AdaptorJoustPlayMeterHUD::updateScoreLerp();
}
