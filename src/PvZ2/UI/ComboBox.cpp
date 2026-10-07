//
//  ComboBox.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UIButton.h"
#include "ComboBox.h"
#include "UIHelper.h"
#include "RedPacketRewardInfo.h"

/////////////// Construction ///////////////

ComboBox::ComboBox(BoxClickEvent func)
{
	m_menuClickedCallback = func;
}

void ComboBox::ButtonDepress(int i_id)
{
}

ComboBox::~ComboBox()
{
	m_pMenu = NULL;
	m_pPanel = NULL;
	m_menuClickedCallback = BoxClickEvent();
	m_currentWidgetID = 0;
	m_currentWidgetName = L"";
	m_subMenuCount = 0;
}

/////////////// Menu ///////////////

void ComboBox::HideMenu()
{
	m_pPanel->SetVisible(false);
}

void ComboBox::SetDisabled(bool isDisabled)
{
	HideMenu();
	if (m_pMenu != NULL)
		m_pMenu->SetDisabled(isDisabled);
}

void ComboBox::ClickComboBoxMain(int id)
{
	if (m_pPanel->mVisible)
		HideMenu();
	else
		ShowMenu();
}

void ComboBox::ClickComboBox(int id)
{
	m_currentWidgetID = id;
	ComboBoxItem* item = GetSubMenu(id);
	if (item != NULL)
	{
		m_currentWidgetName = item->GetWidgetName();
		if (m_pMenu != NULL)
			m_pMenu->SetWidgetName(m_currentWidgetName);
	}
	HideMenu();
}

/////////////// Layout ///////////////

static WEAKIMAGE(IMAGE_UI_DIALOG_ASSET_COMBO_BOX_BG, "IMAGE_UI_DIALOG_ASSET_COMBO_BOX_BG")
static WEAKIMAGE(IMAGE_UI_DIALOG_ASSET_COMBO_BOX_ARROW, "IMAGE_UI_DIALOG_ASSET_COMBO_BOX_ARROW")

void ComboBox::Resize(int i_x, int i_y, int i_w, int i_h)
{
	Widget::Resize(i_x, i_y, i_w, i_h);
	if (m_pMenu != NULL)
		m_pMenu->Resize(0, 0, i_w, i_h);
	if (m_pPanel != NULL)
		m_pPanel->Resize(0, i_h, i_w, i_h);
}

void ComboBox::Draw(Sexy::Graphics* i_g)
{
	Widget::Draw(i_g);
	if (m_pPanel != NULL && m_pPanel->mVisible)
		Draw9SliceImage(i_g, Sexy::Rect(0, mHeight, mWidth, m_pPanel->mHeight), IMAGE_UI_DIALOG_ASSET_COMBO_BOX_BG);
}

/////////////// Sub menus ///////////////

ComboBoxItem* ComboBox::AddSubMenu(int i_id, const SexyString& text)
{
	ComboBoxItem* item = new ComboBoxItem(i_id);
	item->Resize(0, mHeight * m_subMenuCount, mWidth, mHeight);
	item->SetWidgetName(text);
	item->SetClickFunc(Sexy::MakeDelegate(*this, &ComboBox::ClickComboBox));
	item->SetCustomClickFunc(m_menuClickedCallback);
	m_pPanel->AddWidget(item);
	m_subMenuCount++;
	return item;
}

ComboBoxItem* ComboBox::GetSubMenu(int i_id)
{
	Sexy::WidgetList& list = m_pPanel->mWidgets;
	Sexy::WidgetList::iterator it = list.begin();
	Sexy::WidgetList::iterator end = list.end();
	for (; it != end; ++it)
	{
		ComboBoxItem* item = (ComboBoxItem*)*it;
		if (item != NULL && item->GetWidgetID() == i_id)
			return item;
	}
	return NULL;
}

void ComboBox::ShowMenu()
{
	if (m_pPanel->mWidgets.empty())
	{
		HideMenu();
		return;
	}
	m_pPanel->SetVisible(true);
	int maxWidth = 0;
	int y = 0;
	Sexy::WidgetList& list = m_pPanel->mWidgets;
	Sexy::WidgetList::iterator it = list.begin();
	Sexy::WidgetList::iterator end = list.end();
	for (; it != end; ++it)
	{
		Sexy::Widget* w = *it;
		w->mY = y;
		w->mX = 0;
		y += w->mHeight;
		maxWidth = std::max(maxWidth, w->mWidth);
	}
	m_pPanel->mHeight = y;
}

void ComboBox::OnCreate(int i_id, const SexyString& text)
{
	mClip = false;
	m_pMenu = new ComboBoxItem(i_id);
	m_pMenu->SetWidgetName(text);
	m_pMenu->SetBgImage(IMAGE_UI_DIALOG_ASSET_COMBO_BOX_BG);
	m_pMenu->SetArrowImage(IMAGE_UI_DIALOG_ASSET_COMBO_BOX_ARROW);
	m_pMenu->SetMainClickFunc(Sexy::MakeDelegate(*this, &ComboBox::ClickComboBoxMain));
	m_pMenu->Resize(0, 0, mWidth, mHeight);
	AddWidget(m_pMenu);
	m_pPanel = new Sexy::Widget();
	AddWidget(m_pPanel);
	HideMenu();
}
