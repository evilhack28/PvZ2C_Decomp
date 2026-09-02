//
//  FrontLawnStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "FrontLawnStage.h"

#include "Board.h"
#include "LawnApp.h"
#include "LevelDefinition.h"
#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(FrontLawnStage);
void FrontLawnStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FrontLawnStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(FrontLawnStage);
}

RT_CLASS_IMPLEMENT(FrontLawnStageProperties);
void FrontLawnStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(FrontLawnStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(FrontLawnStageProperties);
}


void FrontLawnStage::renderBackground(Graphics* i_g)
{
	StageModule::renderBackground(i_g);
}


void FrontLawnStage::initializeModule()
{
	m_RenderBackGround = true;
	if (gLawnApp->m_board->GetLevelDefinition()->IsLevelOfTheDay)
		m_RenderBackGround = true;
	StageModule::initializeModule();
}
