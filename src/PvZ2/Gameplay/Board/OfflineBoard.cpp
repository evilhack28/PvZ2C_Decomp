//
//  OfflineBoard.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "OfflineBoard.h"
#include "PvZ/GameCommon.h"
#include "PvZ/UIEditor/StringHelper.h"
#include "PvZ/LawnApp.h"
#include "PvZ/UIEditor/UIScrollControl.h"
#include "PvZ/UIEditor/UIWidgetText.h"
#include "PvZ/UIEditor/UIWidgetImage.h"

/////////////// Lifecycle ///////////////

OfflineBoard::OfflineBoard()
{
}

OfflineBoard::~OfflineBoard()
{
	Sexy::PrimeText::Instance()->ClearGlyphCache();
}

/////////////// Accessors ///////////////

std::string OfflineBoard::GetLayoutName()
{
	return "board_offline";
}

/////////////// Logic ///////////////

static WEAKIMAGE(IMAGE_UI_BOARD_IMAGE_COMMON, "IMAGE_UI_BOARD_IMAGE_COMMON")

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

void OfflineBoard::ButtonDepress(int i_id)
{
	if (i_id == 0)
		CloseDialog();
}

OfflineBoardTabBtn* OfflineBoard::getTabBtn(int i_id)
{
	Sexy::Widget* client = m_pScrollTabs->GetClientWidget();
	WidgetList::iterator it = std::find_if(client->mWidgets.begin(), client->mWidgets.end(), [&](Sexy::Widget* w) { return static_cast<OfflineBoardTabBtn*>(w)->mId == i_id; });
	return it != client->mWidgets.end() ? static_cast<OfflineBoardTabBtn*>(*it) : NULL;
}

void OfflineBoard::InitInfoList(const std::vector<OfflineNoticeInfo>& i_list)
{
	m_infoList.clear();
	m_infoList = i_list;
	RefreshTabList();
	if (!m_infoList.empty())
	{
		OfflineBoardTabBtn* btn = getTabBtn(m_infoList[0].m_id + 100);
		if (btn != NULL)
		{
			btn->SetSelected(true);
		}
	}
}

void OfflineBoard::DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g)
{
	gLawnApp->DrawDarkeningLayer(i_g, 0.5f);
	base_type::DrawAll(i_flags, i_g);
}

void OfflineBoard::RefreshTabList()
{
	m_pScrollTabs->GetClientWidget()->RemoveAllWidgets(false, false);
	for (std::vector<OfflineNoticeInfo>::iterator it = m_infoList.begin(), end = m_infoList.end(); it != end; ++it)
	{
		OfflineNoticeInfo& info = *it;
		OfflineBoardTabBtn* btn = new OfflineBoardTabBtn(info.m_id + 100, info.m_wstrTitle);
		m_pScrollTabs->AddWidget(btn);
		btn->mX = m_rectBoardTabBtn.mX;
		btn->m_RadioListener = this;
	}
	m_pScrollTabs->Layout();
}

void OfflineBoard::RefreshContent()
{
	std::vector<OfflineNoticeInfo>::iterator it = std::find_if(m_infoList.begin(), m_infoList.end(), [this](const OfflineNoticeInfo& info) { return info.m_id == m_selectedBoardID; });
	if (it == m_infoList.end())
		return;
	m_pTitleText->SetString(it->m_wstrTitle);
	m_pContentText->SetString(Sexy::WStringToSexyString(it->m_wstrContent));
	Sexy::Image* image = IMAGE_UI_BOARD_IMAGE_COMMON;
	m_pContentImage->SetImage(image);
	m_pContentText->FormatByWidth();
	ResizeDialogWidget(this, "UIImage_4", m_rectBg);
	ResizeDialogWidget(this, "UIScroll_Content", m_rectScroll);
	m_pScrollContent->SetScrollOffset(Sexy::FPoint(0, 0), false);
	m_pScrollContent->Layout();
}

bool OfflineBoard::OnCreate()
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
	m_pTitleText = GetWidget<UIWidgetText>("Content_Title");
	m_pContentImage = GetWidget<UIWidgetImage>("Content_Image");
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
	SetCenter(GetWidget("WidgetBack"), false);
	return true;
}

void OfflineBoard::RadioSelectionChanged(UIWidgetRadio* pRadioBtn)
{
	if (pRadioBtn == NULL || !pRadioBtn->IsSelected())
		return;
	m_selectedBoardID = pRadioBtn->mId - 100;
	Sexy::PrimeText::Instance()->ClearGlyphCache();
	RefreshContent();
}

void OfflineBoard::Draw(Sexy::Graphics* i_g)
{
	base_type::Draw(i_g);
}
