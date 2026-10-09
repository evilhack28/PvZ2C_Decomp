//
//  Dialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-09.
//

#include "SexyAppFramework/Common.h"

#include "UIEditor/UIDialog.h"
#include "LawnApp.h"
#include "ScaledApp.h"
#include "PVZ2UIButton.h"
#include "AudioMgr.h"
#include "UIEditor/UIWidgetType.h"
#include "UIEditor/UILayoutDefinition.h"
#include "Precompile.h"

extern bool gUIDebug;

/////////////// UI::Dialog ///////////////

UI::Dialog::Dialog() :
	m_bDeleted(false),
	m_bNeedDarkenBG(false),
	m_bNeedAttachLawnApp(true)
{
}

UI::Dialog::~Dialog()
{
	std::vector<Sexy::Widget*>::iterator it = m_CustomWidgets.begin();
	std::vector<Sexy::Widget*>::iterator end = m_CustomWidgets.end();
	for (; it != end; ++it)
	{
		Sexy::Widget*& widget = *it;
		RemoveWidget(widget);
		delete widget;
	}
	m_CustomWidgets.clear();
	RemoveAllWidgets(true, true);
	gMessageRouter->Unsubscribe(this);
	UnloadGroups();
}

void UI::Dialog::SetDarkBgAlpha(float alpha)
{
	m_darkenBgAlpha = alpha;
}

bool UI::Dialog::OnCreate()
{
	bool result = CreateFromLayout();
	if (result)
	{
		bool needAttach = m_bNeedAttachLawnApp;
		if (needAttach)
		{
			AttachLawnApp();
			result = needAttach;
		}
	}
	return result;
}

void UI::Dialog::OnClose()
{
	DetachLawnApp();
	m_bDeleted = true;
}

void UI::Dialog::Draw(Sexy::Graphics* i_g)
{
	if (m_bNeedDarkenBG)
		gLawnApp->DrawDarkeningLayer(i_g, m_darkenBgAlpha);
	Sexy::Widget::Draw(i_g);
}

void UI::Dialog::AttachLawnApp()
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Dialog_Open", NULL);
	gLawnApp->mWidgetManager->AddWidget(this);
	gLawnApp->mWidgetManager->SetFocus(this);
	gLawnApp->mWidgetManager->BringToFront(this);
	gLawnApp->PushOverlaysToTop();
}

void UI::Dialog::DetachLawnApp()
{
	if (gLawnApp->mWidgetManager->HasWidget(this))
	{
		AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Dialog_Close", NULL);
		gLawnApp->mWidgetManager->RemoveWidget(this);
		gLawnApp->SafeDeleteWidget(this);
	}
}

/////////////// Resource groups ///////////////

void UI::Dialog::UnloadGroups()
{
	for (std::set<std::string>::const_iterator it = m_resGroups.begin(); it != m_resGroups.end(); ++it)
		gLawnApp->DeleteGroup(*it);
	m_resGroups.clear();
}

void UI::Dialog::AddResGroup(const std::string& group_name)
{
	std::set<std::string>::iterator it = m_resGroups.find(group_name);
	if (it != m_resGroups.end())
		return;
	m_resGroups.insert(group_name);
	gLawnApp->LoadGroup(group_name);
}

/////////////// Widget helpers ///////////////

void UI::Dialog::SetWidgetVisible(const std::string& name, bool bVisible)
{
	Sexy::Widget* widget = GetWidget(name);
	if (widget)
		widget->SetVisible(bVisible);
}

void UI::Dialog::SetCenter(Sexy::Widget* pWidget, bool ignoreY)
{
	if (pWidget)
	{
		int width = pWidget->mWidth;
		int height = pWidget->mHeight;
		LawnApp* app = gLawnApp;
		int screenWidth = app->mWidth;
		int screenHeight = app->mHeight;
		int x = (screenWidth - width) / 2;
		int y = UI_S(50) + (screenHeight - height) / 2;
		if (ignoreY)
			y = pWidget->mY;
		pWidget->Move(x, y);
	}
}

void UI::Dialog::setWindowCenter(Sexy::Widget* pWidget)
{
	if (pWidget)
		pWidget->Move((gLawnApp->mWidth - pWidget->mWidth) / 2, (gLawnApp->mHeight - pWidget->mHeight) / 2);
}

void UI::Dialog::SetButtonListener(PVZ2UIButton* pButton, int buttonID, Sexy::ButtonListener* pListener)
{
	if (pButton)
	{
		pButton->mId = buttonID;
		pButton->mButtonListener = pListener;
	}
}

Sexy::Widget* UI::Dialog::GetWidget(const std::string& name)
{
	return GetChildWidget(this, name);
}

Sexy::Widget* UI::Dialog::GetChildWidget(Sexy::Widget* pWidget, const std::string& name)
{
	if (pWidget && !name.empty() && !pWidget->mWidgets.empty())
	{
		Sexy::WidgetList::iterator it = pWidget->mWidgets.begin();
		Sexy::WidgetList::iterator end = pWidget->mWidgets.end();
		for (; it != end; ++it)
		{
			Sexy::Widget* child = *it;
			if (child->mWidgetName == name)
				return child;
			Sexy::Widget* found = GetChildWidget(child, name);
			if (found)
				return found;
		}
	}
	return NULL;
}

Sexy::Widget* UI::Dialog::CloneWidget(Sexy::Widget* pSrcWidget, bool bRecursive)
{
	if (!pSrcWidget)
		return NULL;

	UIWidgetType widgetType;
	widgetType.FromWidget(pSrcWidget, bRecursive);
	Sexy::Widget* clone = widgetType.ToWidget(NULL);
	if (clone && bRecursive && !widgetType.m_Childs.empty())
		InstantiateWidget_Recursively(clone, widgetType.m_Childs);
	return clone;
}

/////////////// Layout ///////////////

bool UI::Dialog::CreateFromLayout()
{
	UILayoutDefinition* layout;
	if (gUIDebug)
	{
		std::string path = GetFolder(Sexy::IFileDriver::PathType_NoBackup) + "layout/" + GetLayoutName() + ".json";
		layout = UILayoutDefinition::GetLayoutByPath(path);
		if (layout == NULL)
			layout = UILayoutDefinition::GetLayout(GetLayoutName());
	}
	else
	{
		layout = UILayoutDefinition::GetLayout(GetLayoutName());
	}

	if (layout == NULL)
		return false;

	UnloadGroups();
	std::vector<std::string>& resGroups = layout->GetResGroups();
	for (size_t i = 0; i < resGroups.size(); i++)
		AddResGroup(resGroups[i]);
	InstantiateWidget_Recursively(this, layout->GetWidgets());
	Sexy::Widget::Resize(0, 0, gLawnApp->mWidth, gLawnApp->mHeight);
	m_bNeedDarkenBG = layout->IsNeedDarkenBG();
	m_bNeedAttachLawnApp = layout->NeedAttachLawnApp();
	return true;
}

void UI::Dialog::InstantiateWidget_Recursively(Sexy::Widget* pRoot, VecUIWidgetType& vecWidgetType)
{
	if (pRoot && !vecWidgetType.empty())
	{
		VecUIWidgetType::iterator it = vecWidgetType.begin();
		for (; it != vecWidgetType.end(); ++it)
		{
			Sexy::Widget* widget = it->ToWidget(NULL);
			if (widget)
			{
				pRoot->AddWidget(widget);
				if (WidgetFactory<PVZ2UIButton*>::GetWidget(widget))
					SetButtonListener((PVZ2UIButton*)widget, it->m_ID, this);
			}
			InstantiateWidget_Recursively(widget, it->m_Childs);
		}
	}
}

/////////////// Empty overrides ///////////////

void UI::Dialog::DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g)
{
	Sexy::Widget::DrawAll(i_flags, i_g);
}

void UI::Dialog::ButtonPress(int i_id)
{
}

void UI::Dialog::ButtonDepress(int i_id)
{
}
