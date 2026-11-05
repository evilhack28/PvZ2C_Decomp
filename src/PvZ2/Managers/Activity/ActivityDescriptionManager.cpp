//
//  ActivityDescriptionManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"

#include "UIUtil.h"
#include "LawnApp.h"

/////////////// Lifecycle ///////////////

ActivityDescriptionManager::ActivityDescriptionManager()
{
	m_descriptionUI = NULL;
}

ActivityDescriptionManager::~ActivityDescriptionManager()
{
}

/////////////// Description ///////////////

ActivityDescriptionUI* ActivityDescriptionManager::ShowDescription(const SexyString& i_des, const SexyString& i_title)
{
	CloseDescription();
	if (m_descriptionUI == NULL)
	{
		m_descriptionUI = new ActivityDescriptionUI();
		m_descriptionUI->InitView(i_des, i_title);
		m_descriptionUI->RegisterTouchCallBackFunc(Sexy::MakeDelegate(*this, &ActivityDescriptionManager::CloseDescription));
		gLawnApp->mWidgetManager->AddWidget(m_descriptionUI);
		gLawnApp->mWidgetManager->BringToFront(m_descriptionUI);
		gLawnApp->PushOverlaysToTop();
		gLawnApp->mWidgetManager->AddBaseModal(m_descriptionUI);
		gLawnApp->mWidgetManager->SetFocus(m_descriptionUI);
	}
	return m_descriptionUI;
}

void ActivityDescriptionManager::CloseDescription()
{
	if (m_descriptionUI)
	{
		gLawnApp->mWidgetManager->RemoveWidget(m_descriptionUI);
		gLawnApp->mWidgetManager->RemoveBaseModal(m_descriptionUI);
		gLawnApp->SafeDeleteWidget(m_descriptionUI);
		m_descriptionUI = NULL;
	}
}
