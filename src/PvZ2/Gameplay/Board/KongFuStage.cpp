//
//  KongFuStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "KongFuStage.h"

#include "AudioMgr.h"
#include "LevelModuleManager.h"
#include "ObjectTypeDirectory.h"
#include "ReflectionBuilder.h"
#include "RtDelegate.h"
#include "ZombieType.h"
#include "Board.h"
#include "BoardConstants.h"
#include "BoardTransforms.h"
#include "Graphics.h"
#include "ResourceHelpers.h"
#include "LawnApp.h"
#include "ScaledApp.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(KongFuStage);

void KongFuStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(KongFuStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(KongFuStage);
}

RT_CLASS_IMPLEMENT(KongFuStageProperties);

void KongFuStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(KongFuStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

	REFLECTION_CLASSBUILDER_END(KongFuStageProperties);
}

/////////////// Logic ///////////////

CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_MECHANISM_BG("IMAGE_BACKGROUNDS_KONGFU_BG");

CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_MECHANISM_TRACK("IMAGE_BACKGROUNDS_KONGFU_TRACK");

static SexyVector2 s_trackOffset(5.0f, -25.0f);

void KongFuStage::renderBackground(Graphics* i_g)
{
	StageModule::renderBackground(i_g);

	Board* board = gLawnApp->m_board;
	getProps<KongFuStageProperties>();

	for (int x = 0; x < board->m_gridSizeX; x++)
	{
		for (int y = 0; y < board->m_gridSizeY; y++)
		{
			if (board->GetGridSquareType(x, y) != GRIDSQUARE_GEAR)
				continue;

			SexyVector2 pos;
			int bx = BoardTransforms::GridToBoardSpaceX(x);
			int w = BoardConstants::GRIDSQUARE_WIDTH();
			pos.x = S(bx + s_trackOffset.x - w * 0.5f);
			int by = BoardTransforms::GridToBoardSpaceY(y);
			int h = BoardConstants::GRIDSQUARE_HEIGHT();
			pos.y = S(by + s_trackOffset.y - h * 0.5f);
			if (y == 0 || y == 3)
				i_g->DrawImage(IMAGE_BACKGROUNDS_MECHANISM_TRACK, (int)pos.x, (int)pos.y);
		}
	}
}

void KongFuStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &KongFuStage::parseGearImages));
}

void KongFuStage::onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to)
{
	StageModule::onZombieTypeCountChange(i_type, i_from, i_to);

	if (i_type == ObjectTypeDirectory<ZombieType>::GetInstancePtr()->GetTypeFromTypeName("pharaoh"))
	{
		if (i_from > 0 && i_to <= 0)
			AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_KongFu_Sarcophagus_Mommy", NULL);
		else if (i_from == 0 && i_to > 0)
			AudioMgr::GetInstancePtr()->SendEvent("Play_Zomb_KongFu_Sarcophagus_Mommy", NULL);
	}
}

void KongFuStage::stopZombieGroans()
{
	AudioMgr::GetInstancePtr()->SendEvent("Stop_Zomb_KongFu_Sarcophagus_Mommy", NULL);
	StageModule::stopZombieGroans();
}

void KongFuStage::onPostLoad()
{
	StageModule::onPostLoad();
	parseGearImages();
}

void KongFuStage::parseGearImages()
{
}
