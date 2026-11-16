//
//  JoustStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "JoustStage.h"
#include "ReflectionBuilder.h"
#include "Board.h"
#include "BoardConstants.h"
#include "Graphics.h"
#include "GridItemScoreTile.h"
#include "LawnApp.h"
#include "LevelModuleManager.h"
#include "PrimeText_Game.h"
#include "RenderQueue.h"
#include "ResourceHelpers.h"
#include "RtDelegate.h"
#include "ScaledApp.h"

JoustStage::JoustStage()
{
}

JoustStage::~JoustStage()
{
}

JoustStageProperties::~JoustStageProperties()
{
}

void JoustStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &JoustStage::addFlagOverlayToRenderQueue));
	getManager()->RegisterOnIntroStarted(Sexy::MakeDelegate(*this, &JoustStage::findMultiplierValues));
}

void JoustStage::findMultiplierValues()
{
	float lastMultiplier = -1.0f;
	for (int x = 0; x < BoardConstants::NUMBER_OF_COLUMNS(); x++)
	{
		std::vector<GridItem*> gridItems;
		gLawnApp->m_board->GetGridItemsAt(x, 0, gridItems);
		for (std::vector<GridItem*>::iterator it = gridItems.begin(), end = gridItems.end(); it != end; ++it)
		{
			GridItem* item = *it;
			if (item->IsA<GridItemScoreTile>())
			{
				float multiplier = item->Cast<GridItemScoreTile>()->GetBonusModifier();
				if (lastMultiplier < multiplier)
				{
					m_scoreMultipliers.push_back(multiplier);
					lastMultiplier = multiplier;
				}
			}
		}
	}
}

void JoustStage::addFlagOverlayToRenderQueue(RenderQueue* i_queue)
{
	i_queue->Add(RENDER_LAYER_TOP, Sexy::MakeDelegate(*this, &JoustStage::renderFlagOverlay));
}

void JoustStage::drawMultiplierLabel(Graphics* i_g, PrimeTypeface* i_font, int i_x, int i_y, const Color& i_color, float i_multiplier)
{
	SexyString text = StrFormat(L"%.0fx", i_multiplier);
	i_font->DrawString_Paragraph(i_g, (float)i_x, (float)i_y, (float)S(78), (float)S(39), text, EA::Text::kHACenter, EA::Text::kVACenter, i_color, NULL);
}

RT_CLASS_IMPLEMENT(JoustStage);

void JoustStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<float>, m_scoreMultipliers);
	REFLECTION_CLASSBUILDER_END(JoustStage);
}

RT_CLASS_IMPLEMENT(JoustStageProperties);

void JoustStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(JoustStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(JoustStageProperties);
}
