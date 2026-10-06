//
//  PooyanModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PooyanModule.h"

bool PooyanModule::preventSave()
{
	return true;
}

bool PooyanModule::CheckPerfect()
{
	return false;
}

void PooyanModule::levelStarted()
{
}

void PooyanModule::postInitialize()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PooyanModule);

void PooyanModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PooyanModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_TimeFailure);
		REFLECTION_CLASSBUILDER_FIELD(Sexy::TouchID, m_touchIdent);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, m_touchStart);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PooyanShooter>, m_pooyanShooter);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<UIWidget>, m_scoreUI);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<PooyanShooterData>, m_shooterDatas);
	REFLECTION_CLASSBUILDER_END(PooyanModule);
}

#include "PooyanModule.h"
void PooyanModule::onPlantFire()
{
	 PooyanModule::takeShoot();
}

void PooyanModule::initializeModule()
{
}
