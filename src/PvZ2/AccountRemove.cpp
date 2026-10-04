//
//  AccountRemove.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AccountRemove.h"
#include "UserInfo.h"
#include "TGALogMgr.h"
#include "DNode/DButton.h"
#include "DNode/DStringNode.h"
#include "DNode/DAction.h"
#include "TodLib/TodCommon.h"
#include "TodLib/TodStringFile.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"


AccountRemove::~AccountRemove()
{
	s_pWidgetHandler = nullptr;
}

AccountRemove* AccountRemove::get()
{
	return s_pWidgetHandler;
}

void AccountRemove::UserInit()
{
	InitUI(m_status);
}

void AccountRemove::ExitGame()
{
	Android::Device::ExitApp();
}

void AccountRemove::Initialize()
{
	load(std::string("AccountRemove"), false);
}

AccountRemove* AccountRemove::create(AccountStatus i_status)
{
	if (s_pWidgetHandler)
		return s_pWidgetHandler;

	AccountRemove* p = new AccountRemove();
	p->m_status = i_status;
	p->Initialize();
	p->UserInit();
	p->addToWidgetManager(true);
	s_pWidgetHandler = p;
	return p;
}

void AccountRemove::InitUI(AccountStatus i_status)
{
	TGAAccountRemove log;
	log._step = "1";
	TGALogMgr::GetInstance().LogAccountRemove(log);

	if (i_status == AccountStatus_Normal)
	{
		DButton* btnRecover = mainNode->getChildRecursionByName<DButton*>("btnRecover");
		if (btnRecover)
			btnRecover->setVisible(i_status);
		DButton* btnExit = mainNode->getChildRecursionByName<DButton*>("btnExit");
		if (btnExit)
			btnExit->setVisible(false);
		DButton* btnClose = mainNode->getChildRecursionByName<DButton*>("btnClose");
		if (btnClose)
			btnClose->setCallback([this](DRef*) { removeFromWidgetManager(); });
		DButton* btnConfirm = mainNode->getChildRecursionByName<DButton*>("btnConfirm");
		DStringNode* confirmText = mainNode->getChildRecursionByName<DStringNode*>("btnConfirmText");
		DStringNode* content = mainNode->getChildRecursionByName<DStringNode*>("content");
		DStringNode* title = mainNode->getChildRecursionByName<DStringNode*>("displayTitle");
		if (btnConfirm)
		{
			btnConfirm->setEnabled(false);
			btnConfirm->setCallback([this, content, title, btnClose, confirmText](DRef*) { removeFromWidgetManager(); });
			std::string text = confirmText->getString();
			DRefPtr<DUpdateNumberAction> action;
			auto update = [confirmText, text](int) { return true; };
			action->setUpdate(20, 0, update)
				.setDuration(20.0f)
				.onDone([this, btnConfirm, confirmText, text](DTransformNode*) { removeFromWidgetManager(); });
			confirmText->runAction(action);
		}
	}
	else if (i_status == AccountStatus_Frozen)
	{
		DButton* btnRecover = mainNode->getChildRecursionByName<DButton*>("btnRecover");
		if (btnRecover)
		{
			btnRecover->setVisible(i_status);
			btnRecover->setCallback([this](DRef*) { AccountRemoveMgr::GetInstance().RecoverAccount(); });
		}
		DButton* btnExit = mainNode->getChildRecursionByName<DButton*>("btnExit");
		if (btnExit)
		{
			btnExit->setVisible(true);
			btnExit->setCallback([this](DRef*) { ExitGame(); });
		}
		DButton* btnConfirm = mainNode->getChildRecursionByName<DButton*>("btnConfirm");
		if (btnConfirm)
			btnConfirm->setVisible(false);
		DStringNode* content = mainNode->getChildRecursionByName<DStringNode*>("content");
		DStringNode* title = mainNode->getChildRecursionByName<DStringNode*>("displayTitle");
		title->setString("账号已停用");
		SexyString account = UTF8StringToSexyString(UserInfo::getInstance()->getName());
		SexyString time = StringToSexyString(AccountRemoveMgr::GetInstance().GetDeletedTime());
		SexyString text = TodReplaceString(TodStringTranslate(_S("[ACCOUNT_REMOVE_CONTENT_5]")), _S("{ACCOUNT}"), account);
		text = TodReplaceString(text, _S("{TIME}"), time);
		DString str(SexyStringToUTF8String(text));
		content->setString(str);
		DButton* btnClose = mainNode->getChildRecursionByName<DButton*>("btnClose");
		if (btnClose)
			btnClose->setCallback([this](DRef*) { removeFromWidgetManager(); });
	}
	else if (i_status == AccountStatus_Deleted)
	{
		DButton* btnRecover = mainNode->getChildRecursionByName<DButton*>("btnRecover");
		if (btnRecover)
			btnRecover->setVisible(false);
		DButton* btnExit = mainNode->getChildRecursionByName<DButton*>("btnExit");
		if (btnExit)
			btnExit->setVisible(false);
		DButton* btnConfirm = mainNode->getChildRecursionByName<DButton*>("btnConfirm");
		if (btnConfirm)
		{
			btnConfirm->setVisible(true);
			btnConfirm->setCallback([this](DRef*) { removeFromWidgetManager(); });
		}
		DStringNode* confirmText = mainNode->getChildRecursionByName<DStringNode*>("btnConfirmText");
		confirmText->setString("我知道了");
		DStringNode* content = mainNode->getChildRecursionByName<DStringNode*>("content");
		DStringNode* title = mainNode->getChildRecursionByName<DStringNode*>("displayTitle");
		title->setString("账号已删除");
		DString str("[ACCOUNT_REMOVE_CONTENT_6]");
		content->setStringWithFile(str.c_str());
		DButton* btnClose = mainNode->getChildRecursionByName<DButton*>("btnClose");
		if (btnClose)
			btnClose->setCallback([this](DRef*) { removeFromWidgetManager(); });
	}
}
