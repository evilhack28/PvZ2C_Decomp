//
//  GachaItemDisplayer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//
#include "SexyAppFramework/Common.h"
#include "PvZ/GachaItemDisplayer.h"
#include "PvZ/GachaMgr.h"
#include "PvZ/GameEventMgr.h"
#include "PvZ/PVZ2UIPlantCard.h"
#include "PvZ/ProfileMgr.h"
#include "PvZ/LawnApp.h"
#include "PvZ/PVZ2UIDialog.h"
#include "PvZ/PlayerInfo.h"
#include "PvZ/UIHelper.h"
#include "PvZ/PrimeText_Game.h"
#include "ScaledApp.h"
#include "PvZ/UIGachaDetail.h"
#include "PvZ/PVZ2UIButton.h"
#include "PvZ/TodLib/TodStringFile.h"
#include "UIEditor/StringHelper.h"

namespace GachaItemConfig
{
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_STORE_GACHA_EVENT_NORMAL;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_STORE_GACHA_EVENT_RARE;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_STORE_GACHA_EVENT_LEGEND;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_STORE_GACHA_EVENT_AVATAR;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_DIALOG_ASSET_BG_BLUE;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_DIALOG_ASSET_BG_PURPLE;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_CARDS_STORE_STORE_COIN_CARD;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_DIALOG_ASSET_CARD_PURPLE;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_GENERIC_LIGHT_BUTTON_GREEN;
    extern CachedUIResourcePtr<Sexy::Image> IMAGE_UI_GENERIC_LIGHT_BUTTON_GREEN_DOWN;
}
using namespace GachaItemConfig;

static __attribute__((noinline)) int Ver(int i_v) { return i_v; }
static float s_uiScaleKeep = UI_S(1.0f);

/////////////// Constructor ///////////////

GachaItemDisplayer::GachaItemDisplayer(GachaType i_type, const Rect& i_rect)
    : m_buyButton(NULL)
    , m_backgroundImage(NULL)
{
    m_type = i_type;
    m_drawAlign = DS_ALIGN_CENTER;
    m_card = NULL;
    m_imgIsPlantlocked = NULL;
    m_imgIcon = NULL;
    m_imgObtain = NULL;
    m_imgBanner = NULL;
    std::string unused("");
    m_imgTimingFree = NULL;
    int coin = GachaMgr::GetInstance().GetTargetGachaRewardCoin(i_type, false);
    switch (i_type)
    {
    case 0:
        m_headerLabel = TodStringTranslate(L"[GACHA_ITEM_NORMAL_HEADER]");
        m_descriptionLabel = StringHelper::ReplaceNumberString(std::string("[GACHA_ITEM_NORMAL_DES]"), L"{NUMBER}", coin);
        m_backgroundImage = IMAGE_UI_DIALOG_ASSET_BG_BLUE;
        break;
    case 1:
        m_headerLabel = TodStringTranslate(L"[GACHA_ITEM_RARE_HEADER]");
        m_descriptionLabel = StringHelper::ReplaceNumberString(std::string("[GACHA_ITEM_RARE_DES]"), L"{NUMBER}", coin);
        m_backgroundImage = IMAGE_UI_DIALOG_ASSET_BG_PURPLE;
        break;
    case 2:
        m_headerLabel = TodStringTranslate(L"[GACHA_ITEM_LEGEND_HEADER]");
        m_descriptionLabel = StringHelper::ReplaceNumberString(std::string("[GACHA_ITEM_LEGEND_DES]"), L"{NUMBER}", coin);
        m_backgroundImage = IMAGE_UI_CARDS_STORE_STORE_COIN_CARD;
        break;
    case 3:
        m_headerLabel = TodStringTranslate(L"[GACHA_ITEM_AVATAR_HEADER]");
        m_descriptionLabel = StringHelper::ReplaceNumberString(std::string("[GACHA_ITEM_AVATAR_DES]"), L"{NUMBER}", coin);
        m_backgroundImage = IMAGE_UI_DIALOG_ASSET_CARD_PURPLE;
        break;
    }
    m_headerHeightScaled = UI_S(70);
    m_headerHeightScaled = UI_S(44);
    Image* normalImage = IMAGE_UI_GENERIC_LIGHT_BUTTON_GREEN;
    Image* downImage = IMAGE_UI_GENERIC_LIGHT_BUTTON_GREEN_DOWN;
    m_button_width = UI_S(120);
    m_card = new PVZ2UIGameObjectCard(ObjectTypeDescriptorPtr(NULL), false, E_AVATAR_ILLEGAL, false, true);
    m_card->SetSpecificBackground(getGachaImage(i_type), Color(0, 44, 77, 0));
    AddWidget(m_card);
    AddWidget(UIGachaChest::create(i_type, Rect(0, 0, (int)INV_UI_S((float)i_rect.mWidth), (int)INV_UI_S((float)i_rect.mHeight))));
    m_buyButton = new PVZ2UIButton(101, this, SexyString(L""), Color(Color::White));
    m_buyButton->AddText(TodStringTranslate(L"[GACHA_ITEM_PREVIEW]"), PrimeText_Game::Typeface_FZShaoEr_24_Outline->Typeface(), BUTTON_JUST_CENTER);
    m_buyButton->SetDialogStates(PVZ2UIImage(normalImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(downImage, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
    AddWidget(m_buyButton);
    Resize(i_rect.mX, i_rect.mY, i_rect.mWidth, i_rect.mHeight);
    gMessageRouter->Subscribe(Message::NotifyTutorialResponse, Sexy::MakeDelegate(*this, &GachaItemDisplayer::OnNotifyTutorialResponse));
}

/////////////// Create ///////////////

GachaItemDisplayer* GachaItemDisplayer::Create(GachaType i_type, const Rect& i_rect)
{
    return new GachaItemDisplayer(i_type, i_rect);
}

/////////////// Destructor ///////////////

GachaItemDisplayer::~GachaItemDisplayer()
{
    RemoveAllWidgets(true, true);
    gMessageRouter->Unsubscribe(this);
}

/////////////// getGachaImage ///////////////

Sexy::Image* GachaItemDisplayer::getGachaImage(GachaType i_type)
{
    if (i_type == 0) return IMAGE_UI_STORE_GACHA_EVENT_NORMAL;
    if (i_type == 1) return IMAGE_UI_STORE_GACHA_EVENT_RARE;
    if (i_type == 2) return IMAGE_UI_STORE_GACHA_EVENT_LEGEND;
    if (i_type == 3) return IMAGE_UI_STORE_GACHA_EVENT_AVATAR;
    return NULL;
}

/////////////// OnNotifyTutorialResponse ///////////////

void GachaItemDisplayer::OnNotifyTutorialResponse()
{
if (GachaMgr::GetInstance().GetTutorialStep() == Gacha_Normal_Draw) { if (m_type == 0) { GachaMgr::GetInstance().SetTutorialOffset(mX + m_buyButton->mX + m_buyButton->mWidth / 2);
} }
else if (GachaMgr::GetInstance().GetTutorialStep() == Gacha_Epic_Draw) { if (m_type == 1) { GachaMgr::GetInstance().SetTutorialOffset(mX + m_buyButton->mX + m_buyButton->mWidth / 2);
} }
else if (GachaMgr::GetInstance().GetTutorialStep() == Gacha_Avatar_Draw) { if (m_type == 3) { GachaMgr::GetInstance().SetTutorialOffset(mX + m_buyButton->mX + m_buyButton->mWidth / 2);
} }
else if (GachaMgr::GetInstance().GetTutorialStep() == Gacha_Legend_Draw) { if (m_type == 2) { GachaMgr::GetInstance().SetTutorialOffset(mX + m_buyButton->mX + m_buyButton->mWidth / 2);
} }
}

/////////////// DrawAll ///////////////

void GachaItemDisplayer::DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g)
{
    Widget::DrawAll(i_flags, i_g);
}

/////////////// Resize ///////////////

void GachaItemDisplayer::Resize(int i_x, int i_y, int i_width, int i_height)
{
    Widget::Resize(i_x, i_y, i_width, i_height);
    Rect cardRect(UI_S(14), UI_S(30) + m_headerHeightScaled, mWidth - UI_S(28), UI_S(190));
    if (m_card != NULL)
        m_card->Resize(cardRect);
    if (m_buyButton != NULL)
    {
        int w = m_button_width;
        m_buyButton->Resize((mWidth - w) / 2, (mHeight - UI_S(15)) - UI_S(40), w, UI_S(40) + UI_S(5));
        ProfileMgr::GetInstance().GetCurrentProfile();
    }
}

/////////////// ButtonDepress ///////////////

void GachaItemDisplayer::ButtonDepress(int i_id)
{
PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
if (i_id == 101) {
if (__builtin_expect(gLawnApp->IsConnected() || Ver(*(int*)((char*)profile + 0x40)) == 23, 1)) {
gLawnApp->ShowGachaDisplayerDialog(m_type);
GachaDisplayerDialog* gd = gLawnApp->GetGachaDisplayerDialog();
if (gd != NULL) gd->ShowMask();
} else {
PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[NETWORK_NOT_CONNECTED_TITLE]"), SexyString(L"[NETWORK_NOT_CONNECTED_TEXT]"));
dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog), PVZ2UIDialog::BUTTON_TYPE_GENERIC_SECONDARY);
}
}
}

/////////////// Draw ///////////////

void GachaItemDisplayer::Draw(Sexy::Graphics* i_g)
{
    Rect rect(UI_S(4), 0, mWidth - UI_S(8), mHeight);
    Draw9SliceImage(i_g, rect, m_backgroundImage);
    Rect headerRect(rect.mX + UI_S(10), (int)UI_S(15.0f), rect.mWidth - UI_S(20), m_headerHeightScaled);
    WriteWordInRect(i_g, m_headerLabel, headerRect, PrimeText_Game::Typeface_FZShaoEr_28_ThickOutline->Typeface(), Color(Color::White), DS_ALIGN_CENTER_VERTICAL_MIDDLE, true);
    int y = UI_S(194) + m_headerHeightScaled + UI_S(35);
    Rect descRect(rect.mX + UI_S(10), y, rect.mWidth - UI_S(20), (int)(PrimeText_Game::Typeface_FZCuYuan_18->Typeface()->GetLineHeight() * 4.0f));
    WriteWordInRect(i_g, m_descriptionLabel, descRect, PrimeText_Game::Typeface_FZCuYuan_18->Typeface(), PrimeText_Game::Color_Description_Brown, m_drawAlign, true);
}
