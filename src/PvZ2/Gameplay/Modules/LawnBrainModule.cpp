//
//  LawnBrainModule.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "LawnBrainModule.h"
#include "LawnApp.h"
#include "Board.h"
#include "LevelModuleManager.h"
#include "ResourceHelpers.h"
#include "ReflectionBuilder.h"
#include "LawnBrainModule.h"

/////////////// Lifecycle ///////////////

LawnBrainModule::LawnBrainModule()
{
}

LawnBrainModule::~LawnBrainModule()
{
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(LawnBrainModule);

void LawnBrainModule::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(LawnBrainModule);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(LevelModule);

		REFLECTION_CLASSBUILDER_FIELD(int32, m_nBrainsRemaining);
	REFLECTION_CLASSBUILDER_END(LawnBrainModule);
}

/////////////// Accessors ///////////////

float LawnBrainModule::GetEntryAnimDuration()
{
	return getProps<LawnBrainProperties>()->MowerEntryAnimDuration;
}

/////////////// Logic ///////////////

void LawnBrainModule::onReadyForBrains()
{
	 LawnBrainModule::createBrains();
}

bool LawnBrainModule::checkWin()
{
	return m_nBrainsRemaining == 0;
}

void LawnBrainModule::initializeModule()
{
	m_nBrainsRemaining = gLawnApp->m_board->m_gridSizeY;
}

void LawnBrainModule::onBrainDie(GridItemBrain* i_brain)
{
	if (m_nBrainsRemaining > 0 && !gLawnApp->m_board->IsGameplayEnded())
		m_nBrainsRemaining--;
}

const std::string& LawnBrainModule::getMowerAudio()
{
	return getProps<LawnBrainProperties>()->MowerActivatedAudioEvent;
}

PopAnim* LawnBrainModule::getMowerAnim()
{
	return GetPAMByName(getProps<LawnBrainProperties>()->MowerPopAnim);
}

void LawnBrainModule::registerForEvents()
{
	getManager()->RegisterWinCondition(Sexy::MakeDelegate(*this, &LawnBrainModule::checkWin));
	gMessageRouter->Subscribe(&Message::ReadyForLawnItems, Sexy::MakeDelegate(*this, &LawnBrainModule::onReadyForBrains));
	gMessageRouter->Subscribe(&Message::BrainDie, Sexy::MakeDelegate(*this, &LawnBrainModule::onBrainDie));
}

void LawnBrainModule::createBrains()
{
	PopAnim* mowerAnim = getMowerAnim();
	gLawnApp->m_board->GetStage();
	std::string mowerAudio = getMowerAudio();
if (gLawnApp->m_board->m_gridSizeY > 0 && gLawnApp->m_board->m_plantRow[0] != PLANTROW_DIRT)
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 0)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 0);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 1 && gLawnApp->m_board->m_plantRow[1] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 1)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 1);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 2 && gLawnApp->m_board->m_plantRow[2] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 2)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 2);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 3 && gLawnApp->m_board->m_plantRow[3] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 3)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 3);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 4 && gLawnApp->m_board->m_plantRow[4] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 4)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 4);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 5 && gLawnApp->m_board->m_plantRow[5] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 5)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 5);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 6 && gLawnApp->m_board->m_plantRow[6] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 6)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 6);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 7 && gLawnApp->m_board->m_plantRow[7] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 7)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 7);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 8 && gLawnApp->m_board->m_plantRow[8] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 8)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 8);
	}
if (__builtin_expect(gLawnApp->m_board->m_gridSizeY > 9 && gLawnApp->m_board->m_plantRow[9] != PLANTROW_DIRT, 0))
	{
		GridItemBrain* brain = gLawnApp->m_board->AddGridItem("brain", 0, 9)->Cast<GridItemBrain>();
		brain->LawnBrainInitialize(mowerAnim, 9);
	}
}
