//
//  ArcadePowerUpTemplateAdaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArcadePowerUpTemplateAdaptor.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArcadePowerUpTemplateAdaptor);

void ArcadePowerUpTemplateAdaptor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArcadePowerUpTemplateAdaptor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(ArcadePowerUpTemplateAdaptor);
}
