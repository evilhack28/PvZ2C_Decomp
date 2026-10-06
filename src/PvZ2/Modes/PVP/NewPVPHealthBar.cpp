//
//  NewPVPHealthBar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "NewPVPHealthBar.h"

void NewPVPHealthBar::initLoadingResourcesGroupList()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(NewPVPHealthBar);

void NewPVPHealthBar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NewPVPHealthBar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_damageFlashStartTime);
		REFLECTION_CLASSBUILDER_FIELD(int, m_type);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_headShotID);
		REFLECTION_CLASSBUILDER_FIELD(UIHeadshotIcon*, m_pHeadshotIcon);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_hasEffect);
		REFLECTION_CLASSBUILDER_FIELD(SexyString, m_nameSexyStr);
	REFLECTION_CLASSBUILDER_END(NewPVPHealthBar);
}
