//
//  ZombieBumperCar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "ZombieBumperCar.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBumperCar);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ZombieBumperCarProps);

void ZombieBumperCarProps::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ChargeDegreeRange);
	REFLECTION_CLASSBUILDER_END(ChargeDegreeRange);

	REFLECTION_CLASSBUILDER_BEGIN(ChargeInfo);
		REFLECTION_CLASSBUILDER_FIELD(float, Damage);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector3, InitialVelocity);
	REFLECTION_CLASSBUILDER_END(ChargeInfo);

	REFLECTION_CLASSBUILDER_BEGIN(ZombieBumperCarProps);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(ZombiePropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(Rect, BumperHitRect);
		REFLECTION_CLASSBUILDER_FIELD(ValueRange, LaunchHeight);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ChargeDegreeRange>, DegreeRanges);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ChargeInfo>, ChargeInfos);
	REFLECTION_CLASSBUILDER_END(ZombieBumperCarProps);
}
