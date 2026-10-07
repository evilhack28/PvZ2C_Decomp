//
//  TipsManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "TipsManager.h"
#include "LawnApp.h"
#include "ActivityConfig.h"
#include "TodLib/TodStringFile.h"

TipsManager::~TipsManager()
{
}

TipsManager::TipsManager()
    : m_currentTip(L"")
    , m_state(TipsInvalid)
    , m_fadeStartTime(PVZ_EOT())
    , m_color(Sexy::Color::White)
    , m_tipsRefCount(0)
{
    m_pBannerImg = nullptr;
}

void TipsManager::StopTip()
{
    setState(TipsFadeOut);
}

void TipsManager::setState(TipsState i_state)
{
    m_state = i_state;
    switch (i_state)
    {
    case TipsInvalid:
        decreaseUIGroupRefCount();
        m_fadeStartTime = PVZ_EOT();
        break;
    case TipsFadeIn:
        m_color.mAlpha = 0;
        m_fadeStartTime = PVZ_T();
        break;
    case TipsDisplay:
        m_color.mAlpha = 255;
        m_fadeStartTime = PVZ_EOT();
        break;
    case TipsFadeOut:
        m_color.mAlpha = 255;
        m_fadeStartTime = PVZ_T();
        break;
    default:
        m_fadeStartTime = PVZ_EOT();
        break;
    }
}

void TipsManager::increaseUIGroupRefCount()
{
    if (++m_tipsRefCount == 1)
        gLawnApp->LoadGroup(std::string("UI_Tips"));
}

void TipsManager::decreaseUIGroupRefCount()
{
    --m_tipsRefCount;
    if (m_tipsRefCount == 0)
    {
        gLawnApp->DeleteGroup(std::string("UI_Tips"));
        m_pBannerImg = nullptr;
    }
    else if (m_tipsRefCount < 0)
    {
        m_tipsRefCount = 0;
        m_pBannerImg = nullptr;
    }
}

void TipsManager::StartNewTip(const SexyString& i_tipBaseName, int i_baseIndex, int i_tipsCount, const Sexy::Color& i_color)
{
    SexyString aKey = StrFormat(L"[%ls_%d]", i_tipBaseName.c_str(), RandRangeInt(i_baseIndex, i_baseIndex + i_tipsCount - 1));
    m_currentTip = TodStringTranslate(aKey);
    m_color = i_color;
    setState(TipsFadeIn);
}

void TipsManager::Update()
{
    switch (m_state)
    {
    case TipsFadeIn:
        m_color.mAlpha = (int)((PVZ_T() - m_fadeStartTime) * 510.0f);
        if (m_fadeStartTime + 0.5f < PVZ_T())
            setState(TipsDisplay);
        break;
    case TipsFadeOut:
        m_color.mAlpha = (int)(((m_fadeStartTime + 0.5f) - PVZ_T()) * 510.0f);
        if (m_fadeStartTime + 0.5f < PVZ_T())
            setState(TipsInvalid);
        break;
    default:
        break;
    }
}

void TipsManager::StartNewTipFromAcitvityConfig()
{
    if (gLawnApp->GetActivityConfig() && gLawnApp->GetActivityConfig()->IsTipsActivated())
    {
        increaseUIGroupRefCount();
        m_pBannerImg = gLawnApp->GetActivityConfig()->GetTipsImage();
        int aCount = (int)gLawnApp->GetActivityConfig()->GetTipsData().TipsContent.size();
        int aMax = aCount - 1;
        if (aMax >= 0)
        {
            int aIndex = RandRangeInt(0, aMax);
            TipsData aData(gLawnApp->GetActivityConfig()->GetTipsData());
            m_currentTip = TodStringTranslate(Sexy::StringToSexyString(aData.TipsContent[aIndex]));
            std::string aColorType = gLawnApp->GetActivityConfig()->GetTipsData().strTipsProperty.sColorType;
            m_color = Sexy::Color(gLawnApp->GetActivityConfig()->GetActivityTextColor(aColorType));
            setState(TipsFadeIn);
        }
    }
}

void TipsManager::Draw(Graphics* i_g)
{
    if (m_state != TipsInvalid)
    {
        GraphicsAutoState aState(i_g);
        if (gLawnApp->GetActivityConfig() && gLawnApp->GetActivityConfig()->GetTipsData().bIsActivated)
        {
            LawnApp* aApp = gLawnApp;
            Sexy::Rect aRect(0, (int)(UI_S(130.0f) + (float)aApp->mHeight * 0.5f), aApp->mWidth, (int)UI_S(50.0f));
            WriteWordInRect(i_g, m_currentTip, aRect, PrimeText_Game::Typeface_FZCuYuan_26_Shaded->Typeface(), Sexy::Color(m_color), DS_ALIGN_CENTER_VERTICAL_MIDDLE, false);
        }
        if (m_pBannerImg)
        {
            i_g->SetColorizeImages(true);
            i_g->SetColor(Sexy::Color(255, 255, 255, m_color.mAlpha));
            int aX = (gLawnApp->mWidth - m_pBannerImg->GetWidth()) / 2;
            Image* aImg = m_pBannerImg;
            int aY = (gLawnApp->mHeight - aImg->GetHeight()) / 2;
            i_g->DrawImage(aImg, aX, (int)((float)aY - UI_S(60.0f)));
            i_g->SetColorizeImages(false);
        }
    }
}
