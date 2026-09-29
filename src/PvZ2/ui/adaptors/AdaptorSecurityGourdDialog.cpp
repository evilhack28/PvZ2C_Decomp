//
//  AdaptorSecurityGourdDialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorSecurityGourdDialog.h"

AdaptorSecurityGourdDialog::AdaptorSecurityGourdDialog()
{
}

AdaptorSecurityGourdDialog::~AdaptorSecurityGourdDialog()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorSecurityGourdDialog);

void AdaptorSecurityGourdDialog::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorSecurityGourdDialog);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorSecurityGourdDialog);
}
