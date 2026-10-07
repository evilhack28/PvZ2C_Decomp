//
//  BoardDlg.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "BoardDlg.h"
#include "PvZ/GameEventMgr.h"
#include "PvZ/UIEditor/UIMessageBox.h"
#include "PvZ/GameCommon.h"
#include "PvZ/UIEditor/StringHelper.h"
#include "PvZ/LawnApp.h"
#include "PvZ/UIEditor/UIScrollControl.h"
#include "PvZ/UIEditor/UIWidgetText.h"
#include "PvZ/UIEditor/UIWidgetImage.h"
#include "PvZ/gameNetWork/NetworkMgr.h"
#include "PvZ/gameNetWork/NetworkMsgProcess.h"
#include "RedPacketRewardInfo.h"

static WEAKIMAGE(IMAGE_UI_BOARD_IMAGE_COMMON, "IMAGE_UI_BOARD_IMAGE_COMMON")
static WEAKIMAGE(IMAGE_UI_CURRENCY_GEM, "IMAGE_UI_CURRENCY_GEM")
static WEAKIMAGE(IMAGE_UI_CURRENCY_COIN, "IMAGE_UI_CURRENCY_COIN")
static WEAKIMAGE(IMAGE_UI_CURRENCY_PVPCOIN, "IMAGE_UI_CURRENCY_PVPCOIN")
static WEAKIMAGE(IMAGE_UI_CURRENCY_PVPMETAL, "IMAGE_UI_CURRENCY_PVPMETAL")

void BoardDlg::Draw(Sexy::Graphics* i_g)
{
	base_type::Draw(i_g);
}


BoardDlg::BoardDlg()
{
	gMessageRouter->Subscribe(Message::NotifyBoardInfoGetReward, Sexy::MakeDelegate(*this, &BoardDlg::onNotifyBoardInfoGetReward));
	s_NeedShow = false;
}

BoardDlg::~BoardDlg()
{
	gMessageRouter->Unsubscribe(this);
	Sexy::PrimeText::Instance()->ClearGlyphCache();
}

std::string BoardDlg::GetLayoutName()
{
	return "board";
}

void BoardDlg::ButtonDepress(int i_id)
{
	switch (i_id)
	{
	case 0:
		CloseDialog();
		break;
	case 1:
		gNetworkMgr->GetNewNetWorkProcess()->RequestBoardInfoGet(m_selectedBoardID, 2);
		break;
	}
}

void BoardDlg::setReward(Sexy::Widget* pParent, Sexy::Image* pImage, int i_num)
{
	if (pParent != NULL && i_num > 0)
	{
		BoardRewardIcon* icon = getNewReward(pParent);
		if (icon != NULL)
		{
			icon->SetReward(pImage, i_num);
		}
	}
}

void BoardDlg::InitInfoList(const S2C_NoticeInfoList& infoList)
{
	m_infoList.clear();
	m_infoList = infoList.m_infoList;
	RefreshTabList();
	if (!m_infoList.empty())
	{
		BoardTabBtn* btn = getTabBtn(m_infoList[0].m_id + 100);
		if (btn != NULL)
		{
			btn->SetSelected(true);
		}
	}
}

BoardTabBtn* BoardDlg::getTabBtn(int i_id)
{
	Sexy::Widget* client = m_pScrollTabs->GetClientWidget();
	WidgetList::iterator it = std::find_if(client->mWidgets.begin(), client->mWidgets.end(), [&](Sexy::Widget* w) { return static_cast<BoardTabBtn*>(w)->mId == i_id; });
	return it != client->mWidgets.end() ? static_cast<BoardTabBtn*>(*it) : NULL;
}

void BoardDlg::hideAllRewards(Sexy::Widget* pParent)
{
	if (pParent != NULL)
	{
		WidgetList::iterator it = pParent->mWidgets.begin();
		WidgetList::iterator end = pParent->mWidgets.end();
		for (; it != end; ++it)
		{
			(*it)->SetVisible(false);
		}
	}
}

__attribute__((noclone)) static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

BoardRewardIcon* BoardDlg::getNewReward(Sexy::Widget* pParent)
{
	if (pParent == NULL)
	{
		return NULL;
	}
	WidgetList::iterator it = pParent->mWidgets.begin();
	WidgetList::iterator end = pParent->mWidgets.end();
	for (; it != end; ++it)
	{
		BoardRewardIcon* icon = static_cast<BoardRewardIcon*>(*it);
		if (icon != NULL && !icon->mVisible)
		{
			icon->SetVisible(true);
			return icon;
		}
	}
	BoardRewardIcon* icon = new BoardRewardIcon();
	pParent->AddWidget(icon);
	icon->SetVisible(true);
	int size = UIScaleNum(63);
	icon->Resize(0, 0, size, size);
	return icon;
}

void BoardDlg::DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g)
{
	gLawnApp->DrawDarkeningLayer(i_g, 0.5f);
	base_type::DrawAll(i_flags, i_g);
}

void BoardDlg::layoutAllRewards(Sexy::Widget* pParent)
{
	if (pParent != NULL)
	{
		WidgetList& widgets = pParent->mWidgets;
		int count = 0;
		for (WidgetList::iterator it = widgets.begin(), end = widgets.end(); it != end; ++it)
	{
		Sexy::Widget* w = *it;
		if (w != NULL && w->mVisible)
			count++;
	}
		if (count > 0)
		{
	int iconSize = UIScaleNum(63);
	int gap = UIScaleNum(10);
			int step = iconSize + gap;
	int h = pParent->mHeight;
	int w0 = pParent->mWidth;
	int y = (h - iconSize) / 2;
	int x = (w0 - step * count) / 2;
			for (WidgetList::iterator it = widgets.begin(), end = widgets.end(); it != end; ++it)
	{
		Sexy::Widget* w = *it;
		if (w != NULL && w->mVisible)
		{
			w->Resize(x, y, UIScaleNum(63), UIScaleNum(63));
			x += step;
		}
	}
		}
	}
}

void BoardDlg::RefreshTabList()
{
	m_pScrollTabs->GetClientWidget()->RemoveAllWidgets(false, false);
	for (std::vector<S2C_NoticeInfo>::iterator it = m_infoList.begin(), end = m_infoList.end(); it != end; ++it)
	{
		S2C_NoticeInfo& info = *it;
		BoardTabBtn* btn = new BoardTabBtn(info.m_id + 100, Sexy::WStringToSexyString(info.m_wstrTitle));
		m_pScrollTabs->AddWidget(btn);
		btn->mX = m_rectBoardTabBtn.mX;
		btn->SetNew(info.m_readStatus == 0);
		btn->SetReward(info.m_rewardStatus == 0);
		btn->m_RadioListener = this;
	}
	m_pScrollTabs->Layout();
}

void BoardDlg::RadioSelectionChanged(UIWidgetRadio* pRadioBtn)
{
	if (pRadioBtn != NULL && pRadioBtn->IsSelected())
	{
		m_selectedBoardID = pRadioBtn->mId - 100;
		std::vector<S2C_NoticeInfo>::iterator it = std::find_if(m_infoList.begin(), m_infoList.end(), [this](const S2C_NoticeInfo& info) { return info.m_id == m_selectedBoardID; });
		if (it != m_infoList.end() && it->m_readStatus == 0)
		{
			gNetworkMgr->GetNewNetWorkProcess()->RequestBoardInfoGet(it->m_id, 1);
		}
		Sexy::PrimeText::Instance()->ClearGlyphCache();
		RefreshContent();
	}
}

void BoardDlg::showReward(Sexy::Widget* pParent, const S2C_CurrencyInfo& currencyInfo)
{
	hideAllRewards(pParent);
	setReward(pParent, IMAGE_UI_CURRENCY_GEM, currencyInfo.m_gem);
	setReward(pParent, IMAGE_UI_CURRENCY_COIN, currencyInfo.m_coin);
	setReward(pParent, IMAGE_UI_CURRENCY_PVPCOIN, currencyInfo.m_pvpCoin);
	setReward(pParent, IMAGE_UI_CURRENCY_PVPMETAL, currencyInfo.m_pvpMedal);
	if (!currencyInfo.m_rewardList.empty())
	{
		AddResGroup("UI_Fragment_Material");
		AddResGroup("UI_Fragment_Pieces");
		std::vector<S2C_ItemInfo>::const_iterator it = currencyInfo.m_rewardList.begin();
		std::vector<S2C_ItemInfo>::const_iterator end = currencyInfo.m_rewardList.end();
		for (; it != end; ++it)
		{
			const S2C_ItemInfo& item = *it;
			int num = item.m_num;
			int id = item.m_id;
			if (num > 0)
			{
				GAME_ITEM_INFO info = GetGameItemInfo(id, FIND_ITEM_SET_ALL, 0);
				setReward(pParent, StringHelper::ToImage(info.m_strImageId, false), num);
			}
		}
	}
	layoutAllRewards(pParent);
}

void BoardDlg::onNotifyBoardInfoGetReward(const S2C_NoticeInfoGet* pData)
{
	if (pData != NULL)
	{
		int id = pData->m_id;
		std::vector<S2C_NoticeInfo>::iterator it = std::find_if(m_infoList.begin(), m_infoList.end(), [&](const S2C_NoticeInfo& info) { return info.m_id == id; });
		if (it != m_infoList.end())
		{
			it->m_readStatus = pData->m_readStatus;
			int oldRewardStatus = it->m_rewardStatus;
			it->m_rewardStatus = pData->m_rewardStatus;
			int newReward = oldRewardStatus != pData->m_rewardStatus && pData->m_rewardStatus == 1;
			BoardTabBtn* btn = getTabBtn(id + 100);
			if (btn != NULL)
			{
				btn->SetNew(pData->m_readStatus == 0);
				btn->SetReward(pData->m_rewardStatus == 0);
			}
			RefreshContent();
			if (newReward > 0)
			{
				UIMessageBox* box = UISingletonDialog<UIMessageBox>::ShowDialog();
				if (box != NULL)
				{
					box->SetMessage("", "[AWARD_SCREEN_NEW_BONUS]");
					box->SetShowType(2);
					box->SetBackgroundDarken(true, 0.5f);
					showReward(box->GetTextWidget(), it->m_currency);
				}
			}
		}
	}
}

static bool ResizeDialogWidget(UI::Dialog* dlg, const char* name, const Rect& rect)
{
	if (dlg != NULL)
	{
		Sexy::Widget* w = dlg->GetWidget(name);
		if (w != NULL)
		{
			w->Resize(rect);
			return true;
		}
	}
	return false;
}

void BoardDlg::RefreshContent()
{
	std::vector<S2C_NoticeInfo>::iterator it(NULL);
	it = std::find_if(m_infoList.begin(), m_infoList.end(), [this](const S2C_NoticeInfo& info) { return info.m_id == m_selectedBoardID; });
	if (!(it == m_infoList.end()))
	{
		m_pContentText->SetString(Sexy::WStringToSexyString(it->m_wstrContent));
		Sexy::Image* image = StringHelper::ToImage(it->m_strImage, false);
		if (image == NULL)
		{
			image = IMAGE_UI_BOARD_IMAGE_COMMON;
		}
		m_pContentImage->SetImage(image);
		m_pContentText->FormatByWidth();
		if (it->m_rewardStatus == -1)
		{
			ResizeDialogWidget(this, "UIImage_4", m_rectBgMore);
			ResizeDialogWidget(this, "UIScroll_Content", m_rectScrollMore);
		}
		else
		{
			ResizeDialogWidget(this, "UIImage_4", m_rectBg);
			ResizeDialogWidget(this, "UIScroll_Content", m_rectScroll);
		}
		m_pScrollContent->SetScrollOffset(Sexy::FPoint(0, 0), false);
		m_pScrollContent->Layout();
		PVZ2UIButton* button = GetWidget<PVZ2UIButton>("UIButton_1");
		if (button != NULL)
		{
			button->SetVisible(it->m_rewardStatus != -1);
			button->SetDisabled(it->m_rewardStatus == 1);
			const char* labelKey = it->m_rewardStatus == 1 ? "[PLANT_OBTAINED]" : "[PLANT_OBTAIN]";
			std::string label = labelKey;
			button->mLabel = StringHelper::ToStringValue(label);
		}
		if (it->m_rewardStatus == -1)
		{
			m_pRewardWidget->SetVisible(false);
		}
		else
		{
			m_pRewardWidget->SetVisible(true);
			showReward(m_pRewardWidget, it->m_currency);
		}
	}
}

static Rect GetDialogWidgetRect(UI::Dialog* dlg, const char* name, const Rect& defaultRect)
{
	Rect rect = defaultRect;
	if (dlg != NULL)
	{
		Sexy::Widget* w = dlg->GetWidget(name);
		if (w != NULL)
		{
			return w->GetRect();
		}
	}
	return rect;
}

static bool IgnoreDialogWidgetMouse(UI::Dialog* dlg, const char* name)
{
	if (dlg != NULL)
	{
		Sexy::Widget* w = dlg->GetWidget(name);
		if (w != NULL)
		{
			w->SetIgnoreMouseInput(true);
			return true;
		}
	}
	return false;
}

bool BoardDlg::OnCreate()
{
	base_type::OnCreate();
	if (gLawnApp->CanLoadGroup("LUA_UI_Board"))
	{
		AddResGroup("LUA_UI_Board");
	}
	m_pScrollContent = GetWidget<UIScrollControl>("UIScroll_Content");
	m_pScrollContent->GetClientWidget()->mWidth = m_pScrollContent->mWidth;
	m_pScrollContent->SetScrollMode(Sexy::ScrollWidget::SCROLL_VERTICAL);
	m_pContentText = GetWidget<UIWidgetText>("Content_Text");
	m_pContentImage = GetWidget<UIWidgetImage>("Content_Image");
	m_pRewardWidget = GetWidget("UIImage_2");
	m_pContentText->mParent->RemoveWidget(m_pContentText);
	m_pScrollContent->AddWidget(m_pContentText);
	m_pContentText->Resize(0, 0, m_pScrollContent->mWidth, m_pScrollContent->mHeight);
	m_pScrollContent->Layout();
	m_pScrollTabs = GetWidget<UIScrollControl>("UIScroll_Tab");
	m_pScrollTabs->SetScrollMode(Sexy::ScrollWidget::SCROLL_VERTICAL);
	m_pScrollTabs->GetClientWidget()->mWidth = m_pScrollTabs->mWidth;
	Rect defaultRect;
	m_rectBg = GetDialogWidgetRect(this, "UIImage_4", defaultRect);
	m_rectBgMore = GetDialogWidgetRect(this, "Cfg_BgMore", m_rectBg);
	m_rectScroll = GetDialogWidgetRect(this, "UIScroll_Content", defaultRect);
	m_rectScrollMore = GetDialogWidgetRect(this, "Cfg_ContentMore", m_rectScroll);
	m_rectBoardTabBtn = GetDialogWidgetRect(this, "Cfg_BoardTabBtn", defaultRect);
	IgnoreDialogWidgetMouse(this, "Cfg_BgMore");
	IgnoreDialogWidgetMouse(this, "Cfg_ContentMore");
	UIWidgetImage* back = GetWidget<UIWidgetImage>("WidgetBack");
	back->mX = (mWidth - back->mWidth) / 2;
	back->mY = (mHeight - back->mHeight) / 2;
	return true;
}
