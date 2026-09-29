//
//  SkyCannonTypeUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "SkyCannonTypeUI.h"

SkyCannonTypeUI::~SkyCannonTypeUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(SkyCannonTypeUI);

void SkyCannonTypeUI::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(SkyCannonTypeUI);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(float, m_fCoolDownTime);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Effect_PopAnim>, m_crazyEffect);
	REFLECTION_CLASSBUILDER_END(SkyCannonTypeUI);
}
