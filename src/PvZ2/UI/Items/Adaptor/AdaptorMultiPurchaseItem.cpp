//
//  AdaptorMultiPurchaseItem.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorMultiPurchaseItem.h"

void AdaptorMultiPurchaseItem::onLinkToUIViewCreated()
{
}

AdaptorMultiPurchaseItem::~AdaptorMultiPurchaseItem()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorMultiPurchaseItem);

void AdaptorMultiPurchaseItem::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorMultiPurchaseItem);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorMultiPurchaseItem);
}

#include "HotUIAdaptor.h"
void AdaptorMultiPurchaseItem::onLayoutFinished()
{
	 HotUIAdaptor::GetEntryPointWidget();
}
