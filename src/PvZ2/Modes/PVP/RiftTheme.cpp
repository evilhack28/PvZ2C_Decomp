//
//  RiftTheme.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "RiftTheme.h"

RiftThemeProperties::RiftThemeProperties()
{
}

RiftThemeProperties::~RiftThemeProperties()
{
}

RiftTheme::~RiftTheme()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftThemeProperties);

void RiftThemeProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftThemeProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(PropertySheetBase);

	REFLECTION_CLASSBUILDER_END(RiftThemeProperties);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftTheme);

void RiftTheme::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftTheme);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<RiftThemeProperties>, m_props);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_activated);

	REFLECTION_CLASSBUILDER_END(RiftTheme);
}

RiftTheme::RiftTheme()
{
	m_activated = 0;
}
