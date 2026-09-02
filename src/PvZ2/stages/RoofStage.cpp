//
//  RoofStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "RoofStage.h"

#include "Board.h"
#include "BoardRegion.h"
#include "LawnApp.h"
#include "LevelModuleManager.h"
#include "ReflectionBuilder.h"
#include "RtDelegate.h"
#include "ScaledApp.h"
#include "UIWidget.h"

RT_CLASS_IMPLEMENT(RoofStage);
void RoofStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RoofStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(RoofStage);
}

RT_CLASS_IMPLEMENT(RoofStageProperties);
void RoofStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RoofStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(RoofStageProperties);
}


void RoofStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &RoofStage::onLoadComplete));
}


void RoofStage::onLevelLoaded()
{
	StageModule::onLevelLoaded();

	BoardRegionRoof* region = gLawnApp->m_board->AddRegion<BoardRegionRoof>();
	region->SetRegionFromBoardCoordinates(Sexy::FRect(200.0f, 0.0f, 800.0f, 600.0f));
}


void RoofStage::onLoadComplete()
{
	UIWidget* plantfood = UIWidget::GetWidgetBySheetName("UIPlantfood");
	if (plantfood)
		plantfood->SetPositionOffset(Sexy::SexyVector2(UI_S(410), UI_S(0)));

	UIWidget* coinBank = UIWidget::GetWidgetBySheetName("UICoinBank");
	if (coinBank)
		coinBank->SetPositionOffset(Sexy::SexyVector2(UI_S(-500), UI_S(-10)));
}
