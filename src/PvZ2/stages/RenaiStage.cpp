//
//  RenaiStage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-05.
//

#include "Common.h"
#include "RenaiStage.h"

#include "ReflectionBuilder.h"

static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY_LEFT("IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY_LEFT");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY("IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY_RIGHT("IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY_RIGHT");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT_LEFT("IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT_LEFT");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT("IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT");
static CachedResourcePtr<Sexy::Image> IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT_RIGHT("IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT_RIGHT");

RT_CLASS_IMPLEMENT(RenaiStage);
void RenaiStage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RenaiStage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModule);

	REFLECTION_CLASSBUILDER_END(RenaiStage);
}

RT_CLASS_IMPLEMENT(RenaiStageProperties);
void RenaiStageProperties::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(EnvironmentAnim);
		REFLECTION_CLASSBUILDER_FIELD(std::string, AnimName);
		REFLECTION_CLASSBUILDER_FIELD(SexyVector2, AnimPos);
	REFLECTION_CLASSBUILDER_END(EnvironmentAnim);

	REFLECTION_CLASSBUILDER_BEGIN(RenaiStageProperties);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StageModuleProperties);

		REFLECTION_CLASSBUILDER_FIELD(std::vector<EnvironmentAnim>, Anims);

	REFLECTION_CLASSBUILDER_END(RenaiStageProperties);
}


void RenaiStage::initializeModule()
{
	StageModule::initializeModule();
}


void RenaiStage::registerForEvents()
{
	StageModule::registerForEvents();
	getManager()->RegisterOnLoadComplete(Sexy::MakeDelegate(*this, &RenaiStage::onLoadComplete));
	getManager()->RegisterAddToRenderQueue(Sexy::MakeDelegate(*this, &RenaiStage::addBackgroundToRenderQueue));
}

RenaiStage::RenaiStage()
{
	m_environmentType = (decltype(m_environmentType))0;
}

RenaiStage::~RenaiStage()
{
	for (Effect_PopAnimPtr anim : m_environmentAnims)
	{
		if (anim.IsValid())
			anim->Destroy();
		anim.ClearId();
	}
}

void RenaiStage::SetEnvironmentType(EnvironmentType i_type)
{
	m_environmentType = i_type;
}

void RenaiStage::setUpAnims()
{
	for (int i = 0; i < getProps<RenaiStageProperties>()->Anims.size(); i++)
	{
		EnvironmentAnim animInfo = getProps<RenaiStageProperties>()->Anims[i];
		Effect_PopAnimPtr anim = gLawnApp->m_board->AddEffect<Effect_PopAnim>()->GetPtr();
		anim->CreatePopAnimRig(GetPAMByName(animInfo.AnimName), NULL);
		anim->SetBoardSpaceOrigin(SexyVector3(animInfo.AnimPos.x, animInfo.AnimPos.y, 0.0f));
		anim->SetCentered(true);
		anim->SetRenderLayerOverride(RENDER_LAYER_FOG + 1);
		anim->SetVisibility(false);
		anim->SetKeepAlive(true);
		anim->SetScale(0.8f);
		m_environmentAnims.push_back(anim);
	}
}

void RenaiStage::ActivateAnims()
{
	for (Effect_PopAnimPtr anim : m_environmentAnims)
	{
		if (anim && anim.IsValid())
		{
			anim->SetVisibility(true);
			anim->PlayLoopingAnimation("candle");
		}
	}
}

void RenaiStage::onLoadComplete()
{
	m_dayBackImageLeft = IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY_LEFT;
	m_dayBackImage = IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY;
	m_dayBackImageRight = IMAGE_BACKGROUNDS_RENAI_TEXTURE_DAY_RIGHT;
	m_nightBackImageLeft = IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT_LEFT;
	m_nightBackImage = IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT;
	m_nightBackImageRight = IMAGE_BACKGROUNDS_RENAI_TEXTURE_NIGHT_RIGHT;
	setUpAnims();
}

void RenaiStage::addBackgroundToRenderQueue(RenderQueue* i_queue)
{
	switch (m_environmentType)
	{
	case EType_Day:
		i_queue->Add(RENDER_LAYER_STAGE_BACKGROUND + 1, Sexy::MakeDelegate(*this, &RenaiStage::onRenderDay));
		break;
	case EType_Evening:
		i_queue->Add(RENDER_LAYER_STAGE_BACKGROUND + 1, Sexy::MakeDelegate(*this, &RenaiStage::onRenderEvening));
		break;
	case EType_Night:
		i_queue->Add(RENDER_LAYER_STAGE_BACKGROUND + 1, Sexy::MakeDelegate(*this, &RenaiStage::onRenderNight));
		break;
	}
}

void RenaiStage::onRenderDay(Graphics* i_g)
{
	if (m_dayBackImageLeft)
		i_g->DrawImage(m_dayBackImageLeft, -m_dayBackImageLeft->GetWidth(), 0);
	if (m_dayBackImage)
		i_g->DrawImage(m_dayBackImage, 0, 0);
	if (m_dayBackImageRight)
		i_g->DrawImage(m_dayBackImageRight, m_dayBackImage->mWidth, 0);
}

void RenaiStage::onRenderEvening(Graphics* i_g)
{
	if (m_eveningBackImageLeft)
		i_g->DrawImage(m_eveningBackImageLeft, -m_eveningBackImageLeft->GetWidth(), 0);
	if (m_eveningBackImage)
		i_g->DrawImage(m_eveningBackImage, 0, 0);
	if (m_eveningBackImageRight)
		i_g->DrawImage(m_eveningBackImageRight, m_eveningBackImage->mWidth, 0);
}

void RenaiStage::onRenderNight(Graphics* i_g)
{
	if (m_nightBackImageLeft)
		i_g->DrawImage(m_nightBackImageLeft, -m_nightBackImageLeft->GetWidth(), 0);
	if (m_nightBackImage)
		i_g->DrawImage(m_nightBackImage, 0, 0);
	if (m_nightBackImageRight)
		i_g->DrawImage(m_nightBackImageRight, m_nightBackImage->mWidth, 0);
}
