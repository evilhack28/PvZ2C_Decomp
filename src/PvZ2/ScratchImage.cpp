//
//  ScratchImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "ScratchImage.h"
#include "LawnApp.h"
#include "SexyAppFramework/DeviceImage.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/RenderEffect.h"
#include <algorithm>

using namespace Sexy;

// the game keeps these outside this unit's .bss, so ours must not push s_targetImage off offset 0
bool ScratchImage::m_targetOwned __attribute__((section(".data"))) = false;
int ScratchImage::m_transitionAlpha __attribute__((section(".data"))) = 0;

static CachedResourcePtr<RenderEffectDefinition> s_effect("EFFECT_SCRATCH_IMAGE");

static Sexy::DeviceImage* s_targetImage = nullptr;



/////////////// ScratchImage ///////////////

ScratchImage::ScratchImage()
	: m_image(nullptr)
	, m_graphics()
	, m_alpha(m_transitionAlpha)
{
	if (s_targetImage == nullptr)
	{
		s_targetImage = new Sexy::DeviceImage(gLawnApp);
		s_targetImage->AddImageFlags(0x10);
		s_targetImage->mWidth = gLawnApp->mScreenBounds.mWidth;
		s_targetImage->mHeight = gLawnApp->mScreenBounds.mHeight;
		s_targetImage->mBits = nullptr;
		s_targetImage->SetImageMode(true, true);
	}
	if (!m_targetOwned)
	{
		m_image = s_targetImage;
		m_targetOwned = true;
	}
}

ScratchImage::~ScratchImage()
{
	if (m_targetOwned && m_image != nullptr)
	{
		m_targetOwned = false;
		m_image = nullptr;
	}
}

void ScratchImage::DeleteRenderTarget()
{
	if (s_targetImage != nullptr)
		delete s_targetImage;
	s_targetImage = nullptr;
}

void ScratchImage::SetTransitionAlpha(const int i_val)
{
	m_transitionAlpha = i_val;
}

void ScratchImage::SetAlpha(const int i_val)
{
	m_alpha = i_val;
}

void ScratchImage::SetMinAlpha(const int i_val)
{
	m_alpha = std::min(i_val, m_alpha);
}

Graphics* ScratchImage::StartDraw()
{
	if (!m_targetOwned)
		return nullptr;
	if (!m_graphics)
		m_graphics.reset(new Graphics(s_targetImage));
	m_graphics->Get3D()->ClearColorBuffer(Color(0, 0, 0, 0));
	return m_graphics.get();
}

void ScratchImage::FinishDraw(Graphics* i_g)
{
	if (m_image == nullptr)
		return;
	i_g->PushState();
	RenderEffect* effect = i_g->Get3D()->GetEffect(s_effect);
	effect->SetCurrentTechnique("Default", true);
	for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
	{
		i_g->SetColor(Color(255, 255, 255, m_alpha));
		i_g->SetColorizeImages(true);
		i_g->DrawImage(m_image, 0, 0);
	}
	i_g->PopState();
}
