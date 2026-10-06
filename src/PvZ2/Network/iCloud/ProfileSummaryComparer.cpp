//
//  ProfileSummaryComparer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-06.
//

#include "SexyAppFramework/Common.h"

#include "PvZ/iCloud/ProfileSummaryComparer.h"
#include "PvZ/LawnApp.h"
#include "PvZ/GameEventMgr.h"
#include "PvZ/PlayerInfo.h"
#include "PvZ/AuthMgr.h"
#include "PvZ/GameCommon.h"
#include "PvZ/UIHelper.h"
#include "PvZ/TodLib/TodStringFile.h"
#include "PvZ/PrimeText_Game.h"
#include "PvZ/UIEditor/StringHelper.h"
#include "PvZ/PVZ2UIButton.h"
#include "PvZ/PVZ2UIDialog.h"

static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN("IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_GEM_ICON("IMAGE_UI_PROFILE_SELECT_GEM_ICON");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_DIALOG_ASSET_BG_GREEN("IMAGE_UI_DIALOG_ASSET_BG_GREEN");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_COIN_ICON("IMAGE_UI_PROFILE_SELECT_COIN_ICON");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE_DOWN("IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE_DOWN");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN_DOWN("IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN_DOWN");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_SUMMARY_NORMAL("IMAGE_UI_PROFILE_SELECT_SUMMARY_NORMAL");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_PLANTS_ICON("IMAGE_UI_PROFILE_SELECT_PLANTS_ICON");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_SUMMARY_BG("IMAGE_UI_PROFILE_SELECT_SUMMARY_BG");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_ALMANAC_TABS_CLOSE_TAB("IMAGE_UI_ALMANAC_TABS_CLOSE_TAB");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE("IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_SUMMARY_HOVER("IMAGE_UI_PROFILE_SELECT_SUMMARY_HOVER");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_AVATAR_ICON("IMAGE_UI_PROFILE_SELECT_AVATAR_ICON");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_DIALOG_ASSET_BG_ROUND_GREEN("IMAGE_UI_DIALOG_ASSET_BG_ROUND_GREEN");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_NEW_DATE_MARK("IMAGE_UI_PROFILE_SELECT_NEW_DATE_MARK");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_DIALOG_ASSET_BG_PURPLE("IMAGE_UI_DIALOG_ASSET_BG_PURPLE");
static CachedUIResourcePtr<Sexy::Image> IMAGE_UI_PROFILE_SELECT_EGYPT_ICON("IMAGE_UI_PROFILE_SELECT_EGYPT_ICON");

/////////////// ProfileSummaryComparer ///////////////

__attribute__((noclone, pure)) static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

ProfileSummaryComparer::ProfileSummaryComparer(bool isCloudLeft)
{
	Resize((gLawnApp->mScreenBounds.mWidth - UIScaleNum(650)) / 2, 0, UIScaleNum(650), gLawnApp->mScreenBounds.mHeight);
	gLawnApp->LoadGroup("UI_Almanac");
	gLawnApp->LoadGroup("UI_Profile_select");
	initUIs(isCloudLeft);
}

ProfileSummaryComparer::~ProfileSummaryComparer()
{
	gMessageRouter->Unsubscribe(this);
	RemoveAllWidgets(true, true);
	gLawnApp->DeleteGroup("UI_Profile_select");
}

void ProfileSummaryComparer::onConfirmUsingOlderData()
{
	gLawnApp->KillPVZ2Dialog();
	gMessageRouter->Post(Message::ProfileSummarySelectResult, (summarySelectResult)m_isCloudDataOlder);
}

void ProfileSummaryComparer::onCancelUsingOlderData()
{
	gLawnApp->KillPVZ2Dialog();
}

void ProfileSummaryComparer::initUIPositions(bool isCloudLeft)
{
	m_panelToTableGapWidth = UIScaleNum(8);
	m_panelToStarTableGapHeight = UIScaleNum(10);
	m_levelToStarGapHeight = UIScaleNum(20);
	int gapRows = UIScaleNum(2);
	m_leftHeaderPosition.mX = 0;
	m_gapHeightBetween2Rows = gapRows;
	int headerTop = UIScaleNum(40);
	int headerGap = UIScaleNum(15);
	m_leftHeaderPosition.mY = headerTop + headerGap;
	int marginX = mWidth / 20;
	m_leftProgressPanelBGRect.mX = marginX;
	int panelY = headerTop + headerGap + UIScaleNum(60);
	m_leftProgressPanelBGRect.mY = panelY;
	m_leftProgressPanelBGRect.mWidth = (mWidth * 17) / 40;
	int tableWidth = m_leftProgressPanelBGRect.mWidth - m_panelToTableGapWidth * 2;
	m_contentRowWidth = tableWidth;
	m_contentRowHeight = UIScaleNum(30);
	m_leftProgressHeaderPosition.mX = marginX;
	int headerY = UIScaleNum(20);
	m_leftTimePosition.mX = marginX;
	m_leftProgressHeaderPosition.mY = panelY + headerY;
	int timeY = panelY + headerY + UIScaleNum(60);
	int tableY = m_contentRowHeight + timeY;
	int rows2 = m_contentRowHeight * 2;
	int starY = tableY + rows2 + m_levelToStarGapHeight;
	int starH = m_contentRowHeight * 5 + m_gapHeightBetween2Rows * 4;
	m_leftTimePosition.mY = timeY;
	m_leftLevelProgressTableBGRect.mX = m_panelToTableGapWidth + marginX;
	m_leftLevelProgressTableBGRect.mY = tableY;
	m_leftLevelProgressTableBGRect.mWidth = tableWidth;
	m_leftLevelProgressTableBGRect.mHeight = m_gapHeightBetween2Rows + m_contentRowHeight * 2;
	m_leftStarNumTableBGRect.mX = m_panelToTableGapWidth + marginX;
	m_leftStarNumTableBGRect.mY = starY;
	m_leftStarNumTableBGRect.mWidth = tableWidth;
	m_leftStarNumTableBGRect.mHeight = starH;
	int panelRest = starY - panelY;
	m_leftProgressPanelBGRect.mHeight = starH + panelRest + m_panelToStarTableGapHeight;
	if (isCloudLeft)
	{
		m_cloudPanelToLeftDistance = 0;
		m_localPanelToLeftDistance = (mWidth * 19) / 40;
	}
	else
	{
		m_cloudPanelToLeftDistance = (mWidth * 19) / 40;
		m_localPanelToLeftDistance = 0;
	}
	m_isCloudDataOlder = true;
	PlayerInfo* profile = ProfileUtils::Profile();
	if (profile != NULL)
	{
		m_isCloudDataOlder = !profile->IsOlderThanServerData();
	}
}

void ProfileSummaryComparer::ButtonDepress(int i_id)
{
	summarySelectResult result;
	switch (i_id)
	{
	default:
		return;
	case SUMMARYBUTTON_CANCEL:
		result = SSR_CANCEL_SYNC;
	post:
		gMessageRouter->Post(Message::ProfileSummarySelectResult, result);
		return;
	case SUMMARYBUTTON_USECLOUD:
		if (m_isCloudDataOlder) goto warn;
		result = SSR_USE_CLOUD;
		goto post;
	case SUMMARYBUTTON_USELOCAL:
		result = SSR_USE_LOCAL;
		if (!m_isCloudDataOlder) goto warn;
		goto post;
	}
warn:
	PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[SUMMARY_USE_OLDER_DATA_HEADER]"), SexyString(L"[SUMMARY_USE_OLDER_DATA_BODY]"));
	dialog->AddButton(SexyString(L"[BUTTON_OK]"), Sexy::MakeDelegate(*this, &ProfileSummaryComparer::onConfirmUsingOlderData));
	dialog->AddButton(SexyString(L"[BUTTON_CANCEL]"), Sexy::MakeDelegate(*this, &ProfileSummaryComparer::onCancelUsingOlderData));
}

void ProfileSummaryComparer::DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g)
{
	int top = UIScaleNum(40);
	Sexy::Rect rect(0, top, mWidth, (mHeight - UIScaleNum(90)) + UIScaleNum(10));
	Draw9SliceImage(i_g, rect, IMAGE_UI_DIALOG_ASSET_BG_ROUND_GREEN);
	Sexy::WidgetContainer::DrawAll(i_flags, i_g);
}

void ProfileSummaryComparer::Draw(Sexy::Graphics* i_g)
{
	Sexy::Widget::Draw(i_g);
	SexyString title(L"[SUMMARY_TITLE]");
	Sexy::PrimeTypeface* font = PrimeText_Game::Typeface_FZShaoEr_34_ThickOutline->Typeface();
	font->DrawString_Line(i_g, (float)m_leftHeaderPosition.mX, (float)m_leftHeaderPosition.mY, (float)mWidth, TodStringTranslate(title), (EA::Text::HAlignment)1, Color(PrimeText_Game::Color_DangerRoom_LargeLabel), NULL);
	drawLocalSummary(i_g);
	drawCloudSummary(i_g);
	SexyString recommendation(L"[SUMMARY_NEWER_DATA_RECOMMENDATION]");
	Sexy::Image* mark;
	int dy;
	int dx;
	int dist;
	if (m_isCloudDataOlder)
	{
		mark = IMAGE_UI_PROFILE_SELECT_NEW_DATE_MARK;
		dy = UIScaleNum(5);
		dx = m_leftProgressHeaderPosition.mX;
		dist = m_localPanelToLeftDistance;
	}
	else
	{
		mark = IMAGE_UI_PROFILE_SELECT_NEW_DATE_MARK;
		dy = UIScaleNum(5);
		dx = m_leftProgressHeaderPosition.mX;
		dist = m_cloudPanelToLeftDistance;
	}
	i_g->DrawImage(mark, (int)((float)(dist + dx) + 0.8f * (float)m_leftProgressPanelBGRect.mWidth), m_leftProgressHeaderPosition.mY - dy);
}

void ProfileSummaryComparer::setSummaryBtn(PVZ2UIButton* i_btn, Sexy::Image* i_image, const SexyString& i_leftString, const SexyString& i_rightString)
{
	{
		PVZ2UIImage normal(IMAGE_UI_PROFILE_SELECT_SUMMARY_NORMAL, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE);
		PVZ2UIImage down(IMAGE_UI_PROFILE_SELECT_SUMMARY_HOVER, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE);
		i_btn->SetDialogStates(normal, down);
	}
	{
		PVZ2UIImage icon(i_image);
		i_btn->AddImage(icon, BUTTON_JUST_CENTER);
	}
	i_btn->AddText(i_leftString, PrimeText_Game::Typeface_FZCuYuan_20->Typeface(), BUTTON_JUST_LEFT);
	PVZ2UIButton* rightBtn = new PVZ2UIButton(SUMMARYBUTTON_DELEGATE, this, SexyString(L""), Color(Color::White));
	rightBtn->Resize(0, 0, i_btn->mWidth, i_btn->mHeight);
	rightBtn->AddText(i_rightString, PrimeText_Game::Typeface_FZCuYuan_20->Typeface(), BUTTON_JUST_RIGHT);
	i_btn->AddWidget(rightBtn);
}

void ProfileSummaryComparer::initUIs(bool isCloudLeft)
{
	initUIPositions(isCloudLeft);
	m_btn_cancel = new PVZ2UIButton(SUMMARYBUTTON_CANCEL, this, SexyString(L""), Color(Color::White));
	m_btn_cancel->Resize(mWidth - IMAGE_UI_ALMANAC_TABS_CLOSE_TAB->GetWidth() * 2, 0, IMAGE_UI_ALMANAC_TABS_CLOSE_TAB->GetWidth(), IMAGE_UI_ALMANAC_TABS_CLOSE_TAB->GetHeight());
	m_btn_cancel->SetDialogStates(PVZ2UIImage(IMAGE_UI_ALMANAC_TABS_CLOSE_TAB, PVZ2UIIMAGE_SINGLE), PVZ2UIImage(IMAGE_UI_ALMANAC_TABS_CLOSE_TAB, PVZ2UIIMAGE_SINGLE));
	AddWidget(m_btn_cancel);
	m_btn_cancel->SetVisible(false);
	initCloudUIs();
	initLocalUIs();
}

void ProfileSummaryComparer::initCloudUIs()
{
	int days;
	int coins;
	int gems;
	int plants;
	int avatars;
	m_cloudTime = 0;
	PlayerInfo* profile = ProfileUtils::Profile();
	if (profile == NULL)
	{
		days = 0;
		coins = 0;
		gems = 0;
		plants = 0;
		avatars = 0;
	}
	else
	{
		const DeltaInfoSummary& summary = profile->GetDeltaOnlineSummary();
		days = summary.days;
		if (days == 0)
		{
			days = gLawnApp->GetLevelDaysByLevelString(summary.level);
		}
		coins = summary.coins;
		gems = summary.gems;
		m_cloudTime = profile->GetDeltaOnlineSaveTime();
		plants = summary.unlockedplantsize;
		avatars = summary.unlockedavatarsize;
	}
	m_btn_cloud_level = new PVZ2UIButton(SUMMARYBUTTON_CLOUD_LEVEL, this, SexyString(L""), Color(Color::White));
	m_btn_cloud_level->Resize(m_leftLevelProgressTableBGRect.mX + m_cloudPanelToLeftDistance, m_contentRowHeight + m_gapHeightBetween2Rows + m_leftLevelProgressTableBGRect.mY, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_cloud_level, IMAGE_UI_PROFILE_SELECT_EGYPT_ICON, L"[SUMMARY_LEVEL]", TodReplaceNumberString(TodStringTranslate(L"[SUMMARY_DAYS]"), L"{DAY_COUNT}", days));
	AddWidget(m_btn_cloud_level);

	m_btn_cloud_coin_num = new PVZ2UIButton(SUMMARYBUTTON_CLOUD_COIN_NUM, this, SexyString(L""), Color(Color::White));
	m_btn_cloud_coin_num->Resize(m_leftStarNumTableBGRect.mX + m_cloudPanelToLeftDistance, m_contentRowHeight + m_gapHeightBetween2Rows + m_leftStarNumTableBGRect.mY, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_cloud_coin_num, IMAGE_UI_PROFILE_SELECT_COIN_ICON, L"[COIN_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[HOW_MANY_COINS]"), L"{COIN_COUNT}", coins));
	AddWidget(m_btn_cloud_coin_num);

	m_btn_cloud_gem_num = new PVZ2UIButton(SUMMARYBUTTON_CLOUD_GEM_NUM, this, SexyString(L""), Color(Color::White));
	m_btn_cloud_gem_num->Resize(m_leftStarNumTableBGRect.mX + m_cloudPanelToLeftDistance, m_leftStarNumTableBGRect.mY + (m_contentRowHeight + m_gapHeightBetween2Rows) * 2, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_cloud_gem_num, IMAGE_UI_PROFILE_SELECT_GEM_ICON, L"[GEM_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[HOW_MANY_GEMS]"), L"{GEM_COUNT}", gems));
	AddWidget(m_btn_cloud_gem_num);

	m_btn_cloud_plant = new PVZ2UIButton(SUMMARYBUTTON_CLOUD_PLANT, this, SexyString(L""), Color(Color::White));
	m_btn_cloud_plant->Resize(m_leftStarNumTableBGRect.mX + m_cloudPanelToLeftDistance, m_leftStarNumTableBGRect.mY + (m_contentRowHeight + m_gapHeightBetween2Rows) * 3, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_cloud_plant, IMAGE_UI_PROFILE_SELECT_PLANTS_ICON, L"[PLANT_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[SUMMARY_STAR_AMOUNT]"), L"{STAR_COUNT}", plants));
	AddWidget(m_btn_cloud_plant);

	m_btn_cloud_avatar = new PVZ2UIButton(SUMMARYBUTTON_CLOUD_AVATAR, this, SexyString(L""), Color(Color::White));
	m_btn_cloud_avatar->Resize(m_leftStarNumTableBGRect.mX + m_cloudPanelToLeftDistance, m_leftStarNumTableBGRect.mY + (m_contentRowHeight + m_gapHeightBetween2Rows) * 4, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_cloud_avatar, IMAGE_UI_PROFILE_SELECT_AVATAR_ICON, L"[AVATAR_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[SUMMARY_STAR_AMOUNT]"), L"{STAR_COUNT}", avatars));
	AddWidget(m_btn_cloud_avatar);

	m_btn_usecloud = new PVZ2UIButton(SUMMARYBUTTON_USECLOUD, this, SexyString(L""), Color(Color::White));
	if (m_isCloudDataOlder)
	{
		m_btn_usecloud->Resize(m_cloudPanelToLeftDistance + mWidth / 8, mHeight - UIScaleNum(90) - UIScaleNum(30), UIScaleNum(180), UIScaleNum(55));
		m_btn_usecloud->SetDialogStates(PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN_DOWN, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
	}
	else
	{
		m_btn_usecloud->Resize(m_cloudPanelToLeftDistance + mWidth / 8, mHeight - UIScaleNum(90) - UIScaleNum(30), UIScaleNum(180), UIScaleNum(55));
		m_btn_usecloud->SetDialogStates(PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE_DOWN, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
	}
	m_btn_usecloud->AddText(SexyString(L"[SUMMARY_USE_CLOUD]"), PrimeText_Game::Typeface_FZShaoEr_22_HardShadow->Typeface(), BUTTON_JUST_CENTER);
	m_btn_usecloud->SetVisible(true);
	if (AuthMgr::GetInstance().HasNoAuth())
	{
		m_btn_usecloud->SetDisabled(true);
	}
	AddWidget(m_btn_usecloud);
}

void ProfileSummaryComparer::initLocalUIs()
{
	int days;
	int coins;
	int gems;
	int plants;
	int avatars;
	m_localTime = 0;
	PlayerInfo* profile = ProfileUtils::Profile();
	if (profile == NULL)
	{
		days = 0;
		coins = 0;
		gems = 0;
		plants = 0;
		avatars = 0;
	}
	else
	{
		const DeltaInfoSummary& summary = profile->GetDeltaOfflineSummary();
		days = summary.days;
		if (days == 0)
		{
			days = gLawnApp->GetLevelDaysByLevelString(summary.level);
		}
		coins = summary.coins;
		gems = summary.gems;
		m_localTime = profile->GetDeltaOfflineSaveTime();
		plants = summary.unlockedplantsize;
		avatars = summary.unlockedavatarsize;
	}
	m_btn_local_level = new PVZ2UIButton(SUMMARYBUTTON_LOCAL_LEVEL, this, SexyString(L""), Color(Color::White));
	m_btn_local_level->Resize(m_leftLevelProgressTableBGRect.mX + m_localPanelToLeftDistance, m_contentRowHeight + m_gapHeightBetween2Rows + m_leftLevelProgressTableBGRect.mY, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_local_level, IMAGE_UI_PROFILE_SELECT_EGYPT_ICON, L"[SUMMARY_LEVEL]", TodReplaceNumberString(TodStringTranslate(L"[SUMMARY_DAYS]"), L"{DAY_COUNT}", days));
	AddWidget(m_btn_local_level);

	m_btn_local_coin_num = new PVZ2UIButton(SUMMARYBUTTON_LOCAL_COIN_NUM, this, SexyString(L""), Color(Color::White));
	m_btn_local_coin_num->Resize(m_leftStarNumTableBGRect.mX + m_localPanelToLeftDistance, m_contentRowHeight + m_gapHeightBetween2Rows + m_leftStarNumTableBGRect.mY, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_local_coin_num, IMAGE_UI_PROFILE_SELECT_COIN_ICON, L"[COIN_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[HOW_MANY_COINS]"), L"{COIN_COUNT}", coins));
	AddWidget(m_btn_local_coin_num);

	m_btn_local_gem_num = new PVZ2UIButton(SUMMARYBUTTON_LOCAL_GEM_NUM, this, SexyString(L""), Color(Color::White));
	m_btn_local_gem_num->Resize(m_leftStarNumTableBGRect.mX + m_localPanelToLeftDistance, m_leftStarNumTableBGRect.mY + (m_contentRowHeight + m_gapHeightBetween2Rows) * 2, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_local_gem_num, IMAGE_UI_PROFILE_SELECT_GEM_ICON, L"[GEM_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[HOW_MANY_GEMS]"), L"{GEM_COUNT}", gems));
	AddWidget(m_btn_local_gem_num);

	m_btn_local_plant = new PVZ2UIButton(SUMMARYBUTTON_LOCAL_PLANT, this, SexyString(L""), Color(Color::White));
	m_btn_local_plant->Resize(m_leftStarNumTableBGRect.mX + m_localPanelToLeftDistance, m_leftStarNumTableBGRect.mY + (m_contentRowHeight + m_gapHeightBetween2Rows) * 3, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_local_plant, IMAGE_UI_PROFILE_SELECT_PLANTS_ICON, L"[PLANT_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[SUMMARY_STAR_AMOUNT]"), L"{STAR_COUNT}", plants));
	AddWidget(m_btn_local_plant);

	m_btn_local_avatar = new PVZ2UIButton(SUMMARYBUTTON_LOCAL_AVATAR, this, SexyString(L""), Color(Color::White));
	m_btn_local_avatar->Resize(m_leftStarNumTableBGRect.mX + m_localPanelToLeftDistance, m_leftStarNumTableBGRect.mY + (m_contentRowHeight + m_gapHeightBetween2Rows) * 4, m_contentRowWidth, m_contentRowHeight);
	setSummaryBtn(m_btn_local_avatar, IMAGE_UI_PROFILE_SELECT_AVATAR_ICON, L"[AVATAR_NUM_TITLE]", TodReplaceNumberString(TodStringTranslate(L"[SUMMARY_STAR_AMOUNT]"), L"{STAR_COUNT}", avatars));
	AddWidget(m_btn_local_avatar);

	m_btn_uselocal = new PVZ2UIButton(SUMMARYBUTTON_USELOCAL, this, SexyString(L""), Color(Color::White));
	if (m_isCloudDataOlder)
	{
		m_btn_uselocal->Resize(m_localPanelToLeftDistance + mWidth / 8, mHeight - UIScaleNum(90) - UIScaleNum(30), UIScaleNum(180), UIScaleNum(55));
		m_btn_uselocal->SetDialogStates(PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_PURPLE_DOWN, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
	}
	else
{
		m_btn_uselocal->Resize(m_localPanelToLeftDistance + mWidth / 8, mHeight - UIScaleNum(90) - UIScaleNum(30), UIScaleNum(180), UIScaleNum(55));
		m_btn_uselocal->SetDialogStates(PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE), PVZ2UIImage(IMAGE_UI_GENERIC_LIGHT_BUTTON_BROWN_DOWN, PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE));
	}
	m_btn_uselocal->AddText(SexyString(L"[SUMMARY_USE_LOCAL]"), PrimeText_Game::Typeface_FZShaoEr_22_HardShadow->Typeface(), BUTTON_JUST_CENTER);
	m_btn_uselocal->SetVisible(true);
	AddWidget(m_btn_uselocal);
}

void ProfileSummaryComparer::drawCloudSummary(Sexy::Graphics* i_g)
{
	Sexy::Rect panelRect(m_leftProgressPanelBGRect.mX + m_cloudPanelToLeftDistance, m_leftProgressPanelBGRect.mY, m_leftProgressPanelBGRect.mWidth, m_leftProgressPanelBGRect.mHeight);
	Draw9SliceImage(i_g, panelRect, IMAGE_UI_DIALOG_ASSET_BG_GREEN);
	Sexy::Rect levelRect(m_leftLevelProgressTableBGRect.mX + m_cloudPanelToLeftDistance, m_leftLevelProgressTableBGRect.mY, m_leftLevelProgressTableBGRect.mWidth, m_leftLevelProgressTableBGRect.mHeight);
	Draw9SliceImage(i_g, levelRect, IMAGE_UI_PROFILE_SELECT_SUMMARY_BG);
	Sexy::Rect starRect(m_leftStarNumTableBGRect.mX + m_cloudPanelToLeftDistance, m_leftStarNumTableBGRect.mY, m_leftStarNumTableBGRect.mWidth, m_leftStarNumTableBGRect.mHeight);
	Draw9SliceImage(i_g, starRect, IMAGE_UI_PROFILE_SELECT_SUMMARY_BG);

	SexyString title(L"[SUMMARY_CLOUD]");
	Sexy::PrimeTypeface* titleFont = PrimeText_Game::Typeface_FZCuYuan_32_ThickOutline->Typeface();
	titleFont->DrawString_Line(i_g, (float)(m_leftProgressHeaderPosition.mX + m_cloudPanelToLeftDistance), (float)m_leftProgressHeaderPosition.mY, (float)m_leftProgressPanelBGRect.mWidth, TodStringTranslate(title), (EA::Text::HAlignment)1, Color(PrimeText_Game::Color_Popover_Btn_Label), NULL);

	struct tm* time = gLawnApp->BeijingTime(&m_cloudTime);
	SexyString timeText = TodStringTranslate(L"[SUMMARY_LAST_TIME]");
	timeText = TodReplaceNumberString(timeText, L"{MONTH}", time->tm_mon + 1);
	timeText = TodReplaceNumberString(timeText, L"{DAY}", time->tm_mday);
	timeText = TodReplaceNumberString(timeText, L"{HOUR}", time->tm_hour);
	timeText = TodReplaceNumberString(timeText, L"{MIN}", time->tm_min);
	Sexy::PrimeTypeface* timeFont = PrimeText_Game::Typeface_FZCuYuan_20->Typeface();
	timeFont->DrawString_Line(i_g, (float)(m_leftTimePosition.mX + m_cloudPanelToLeftDistance), (float)m_leftTimePosition.mY, (float)panelRect.mWidth, TodStringTranslate(timeText), (EA::Text::HAlignment)1, Color(PrimeText_Game::Color_Description_Brown), NULL);

	SexyString levelLabel(L"[SUMMARY_LEVEL]");
	Sexy::PrimeTypeface* labelFont = PrimeText_Game::Typeface_FZCuYuan_24->Typeface();
	labelFont->DrawString_Line(i_g, (float)(levelRect.mX + UIScaleNum(10)), (float)(levelRect.mY + UIScaleNum(3)), (float)levelRect.mWidth, TodStringTranslate(levelLabel), (EA::Text::HAlignment)0, Color(PrimeText_Game::Color_Description_Brown), NULL);

	SexyString starLabel(L"[SUMMARY_STAR]");
	Sexy::PrimeTypeface* starFont = PrimeText_Game::Typeface_FZCuYuan_24->Typeface();
	starFont->DrawString_Line(i_g, (float)(starRect.mX + UIScaleNum(10)), (float)(starRect.mY + UIScaleNum(3)), (float)starRect.mWidth, TodStringTranslate(starLabel), (EA::Text::HAlignment)0, Color(PrimeText_Game::Color_Description_Brown), NULL);
}

void ProfileSummaryComparer::drawLocalSummary(Sexy::Graphics* i_g)
{
	Sexy::Rect panelRect(m_leftProgressPanelBGRect.mX + m_localPanelToLeftDistance, m_leftProgressPanelBGRect.mY, m_leftProgressPanelBGRect.mWidth, m_leftProgressPanelBGRect.mHeight);
	Draw9SliceImage(i_g, panelRect, IMAGE_UI_DIALOG_ASSET_BG_GREEN);
	Sexy::Rect levelRect(m_leftLevelProgressTableBGRect.mX + m_localPanelToLeftDistance, m_leftLevelProgressTableBGRect.mY, m_leftLevelProgressTableBGRect.mWidth, m_leftLevelProgressTableBGRect.mHeight);
	Draw9SliceImage(i_g, levelRect, IMAGE_UI_PROFILE_SELECT_SUMMARY_BG);
	Sexy::Rect starRect(m_leftStarNumTableBGRect.mX + m_localPanelToLeftDistance, m_leftStarNumTableBGRect.mY, m_leftStarNumTableBGRect.mWidth, m_leftStarNumTableBGRect.mHeight);
	Draw9SliceImage(i_g, starRect, IMAGE_UI_PROFILE_SELECT_SUMMARY_BG);

	SexyString title(L"[SUMMARY_LOCAL]");
	Sexy::PrimeTypeface* titleFont = PrimeText_Game::Typeface_FZCuYuan_32_ThickOutline->Typeface();
	titleFont->DrawString_Line(i_g, (float)(m_leftProgressHeaderPosition.mX + m_localPanelToLeftDistance), (float)m_leftProgressHeaderPosition.mY, (float)panelRect.mWidth, TodStringTranslate(title), (EA::Text::HAlignment)1, Color(PrimeText_Game::Color_Popover_Btn_Label), NULL);

	struct tm* time = gLawnApp->BeijingTime(&m_localTime);
	SexyString timeText = TodStringTranslate(L"[SUMMARY_LAST_TIME]");
	timeText = TodReplaceNumberString(timeText, L"{MONTH}", time->tm_mon + 1);
	timeText = TodReplaceNumberString(timeText, L"{DAY}", time->tm_mday);
	timeText = TodReplaceNumberString(timeText, L"{HOUR}", time->tm_hour);
	timeText = TodReplaceNumberString(timeText, L"{MIN}", time->tm_min);
	Sexy::PrimeTypeface* timeFont = PrimeText_Game::Typeface_FZCuYuan_20->Typeface();
	timeFont->DrawString_Line(i_g, (float)(m_leftTimePosition.mX + m_localPanelToLeftDistance), (float)m_leftTimePosition.mY, (float)panelRect.mWidth, TodStringTranslate(timeText), (EA::Text::HAlignment)1, Color(PrimeText_Game::Color_Description_Brown), NULL);

	SexyString levelLabel(L"[SUMMARY_LEVEL]");
	Sexy::PrimeTypeface* labelFont = PrimeText_Game::Typeface_FZCuYuan_24->Typeface();
	labelFont->DrawString_Line(i_g, (float)(levelRect.mX + UIScaleNum(10)), (float)(levelRect.mY + UIScaleNum(3)), (float)levelRect.mWidth, TodStringTranslate(levelLabel), (EA::Text::HAlignment)0, Color(PrimeText_Game::Color_Description_Brown), NULL);

	SexyString starLabel(L"[SUMMARY_STAR]");
	Sexy::PrimeTypeface* starFont = PrimeText_Game::Typeface_FZCuYuan_24->Typeface();
	starFont->DrawString_Line(i_g, (float)(starRect.mX + UIScaleNum(10)), (float)(starRect.mY + UIScaleNum(3)), (float)starRect.mWidth, TodStringTranslate(starLabel), (EA::Text::HAlignment)0, Color(PrimeText_Game::Color_Description_Brown), NULL);
}
