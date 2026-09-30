//
//  CannonMinigame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CannonMinigame.h"

CannonMinigameProperties::~CannonMinigameProperties()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CannonMinigameProperties);

void CannonMinigameProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PirateLane);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<SexyVector2>, SplinePoints);
	REFLECTION_CLASSBUILDER_END(PirateLane);

	REFLECTION_CLASSBUILDER_BEGIN(ComboBracket);
		REFLECTION_CLASSBUILDER_FIELD(int, ZombiesKilled);
		REFLECTION_CLASSBUILDER_FIELD(float, ScoreMultiplier);
		REFLECTION_CLASSBUILDER_FIELD(Color, MessageColor);
		REFLECTION_CLASSBUILDER_FIELD(std::string, AudioCue);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, Exclamations);
	REFLECTION_CLASSBUILDER_END(ComboBracket);

	REFLECTION_CLASSBUILDER_BEGIN(CannonMinigameProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<PirateLane>, Lanes);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, RowHasCannon);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<ComboBracket>, ComboBrackets);
	REFLECTION_CLASSBUILDER_END(CannonMinigameProperties);
}
