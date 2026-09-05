// Reconstructed by EvilHack28 on 2026-09-05
#include "ViewContainerMgr.h"
#include "IViewContainer.h"

ViewContainerMgr::ViewContainerMgr()
	: m_viewContainerMgr(nullptr)
{
}

ViewContainerMgr::~ViewContainerMgr()
{
}

void ViewContainerMgr::InitializeSDK()
{
	m_viewContainerMgr = IViewContainer::CreateViewContainerManager();
	m_viewContainerMgr->Initialize();
}

void ViewContainerMgr::ShowWebView(const std::string& i_url)
{
	m_viewContainerMgr->ShowWebView(i_url);
}

void ViewContainerMgr::PassCallSettlement(const std::string& i_key, int i_count)
{
	m_viewContainerMgr->PassCallSettlement(i_key, i_count);
}

void ViewContainerMgr::PassCallLottery(const std::string& i_key, int i_id, int i_quantity, int i_index)
{
	m_viewContainerMgr->PassCallLottery(i_key, i_id, i_quantity, i_index);
}

void ViewContainerMgr::PassCallScoreStoreInfo(const std::string& i_key, const std::string& i_info)
{
	m_viewContainerMgr->PassCallScoreStoreInfo(i_key, i_info);
}

void ViewContainerMgr::PassCallScoreStoreBuy(const std::string& i_key, int i_id)
{
	m_viewContainerMgr->PassCallScoreStoreBuy(i_key, i_id);
}

void ViewContainerMgr::PassCallConsumeCash(const std::string& i_key, int i_num)
{
	m_viewContainerMgr->PassCallConsumeCash(i_key, i_num);
}

void ViewContainerMgr::PassCallAddPlayTimes(const std::string& i_key, int i_result)
{
	m_viewContainerMgr->PassCallAddPlayTimes(i_key, i_result);
}
