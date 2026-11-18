//
//  ProxyWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/misc/iphoneos/ProxyWidget.h"

namespace Sexy
{

/////////////// Lifecycle ///////////////

ProxyWidget::ProxyWidget(ProxyWidgetListener *listener)
{
	mListener = listener;
}

/////////////// Drawing ///////////////

void ProxyWidget::Draw(Graphics *g)
{
	if (mListener)
		mListener->DrawProxyWidget(g, this);
}

}
