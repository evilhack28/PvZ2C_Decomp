//
//  UIWidget.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "UIWidget.h"
#include "UIWidgetType.h"
#include "LawnApp.h"
#include "UIWidgetSheet.h"
#include "ScaledApp.h"
#include "ProfileMgr.h"
#include "PlayerInfo.h"
#include "StateMachineTableBuilder.h"
#include "ReflectionBuilder.h"
#include "PVZDB.h"

namespace Lua
{
class CLuaEngine : public Sexy::LazySingleton<CLuaEngine>
{
public:
	void ExecuteTableFunction(const char* i_table, const char* i_function);
};
}

/////////////// Lifecycle ///////////////

UIWidget::~UIWidget()
{
	UnloadResources();
}

/////////////// Accessors ///////////////

const AnchorType UIWidget::GetAnchorType()
{
	if (m_overrideSelfAnchor)
		return m_overrideSelfAnchor;
	return m_propertySheetPtr->Anchor;
}

const AnchorType UIWidget::GetParentAnchorType()
{
	if (m_overrideSelfAnchor)
		return m_overrideParentAnchor;
	return m_propertySheetPtr->ParentAnchor;
}

const uint8 UIWidget::GetInputPriority()
{
	if (m_inputPriorityOverriden)
		return m_overrideInputPriority;
	return m_propertySheetPtr->InputPriority;
}

void UIWidget::SetPositionOffset(const SexyVector2 i_positionOffset)
{
	m_positionOffsetOverriden = true;
	m_overridePositionOffset = i_positionOffset;
	calculatePosition();
}

RtId UIWidget::GetChildId(const int i_childIndex)
{
	return m_childIdList[i_childIndex];
}

UIWidget* UIWidget::GetUIWidgetByRtId(const RtId i_id)
{
	return PVZDB::GetInstance().GetTable(PVZDB::TABLE_UIWIDGETS)->GetObjectForId(i_id)->CastChecked<UIWidget>();
}

/////////////// Logic ///////////////

void UIWidget::initLoadingResourcesGroupList()
{
}

void UIWidget::Draw(Graphics* i_g)
{
}

void UIWidget::ClearPositionOffsetOverride()
{
	m_positionOffsetOverriden = false;
	calculatePosition();
}

void UIWidget::setStateHelper(const StateDefinition<WidgetState>& i_newStateDefinition)
{
	if (m_stateMachine.SetState(i_newStateDefinition))
	{
		m_stateEnterTime = PVZ_T();
	}
}

void UIWidget::updateState_Loading()
{
	if (IsLoadComplete())
	{
		CompleteLoad();
	}
}

void UIWidget::addToLoadingResourcesGroupList(const std::string& i_groupName)
{
	if (std::find(m_loadingResourcesList.begin(), m_loadingResourcesList.end(), i_groupName) == m_loadingResourcesList.end())
	{
		m_loadingResourcesList.push_back(i_groupName);
	}
}

bool UIWidget::isInState(uint32 i_state) const
{
	return m_stateMachine.GetState() == i_state;
}

void UIWidget::onEnterState_Loading(WidgetState i_fromState)
{
	StartLoad();
}

void UIWidget::onExitState_Loading(WidgetState i_toState)
{
}

void UIWidget::onEnterState_Initializing(WidgetState i_fromState)
{
}

void UIWidget::updateState_Initializing()
{
	setState(WS_Ready);
}

void UIWidget::onExitState_Initializing(WidgetState i_toState)
{
}

void UIWidget::onEnterState_Ready(WidgetState i_fromState)
{
}

void UIWidget::updateState_Ready()
{
}

void UIWidget::onExitState_Ready(WidgetState i_toState)
{
}

void UIWidget::onEnterState_NotReady(WidgetState i_fromState)
{
}

void UIWidget::updateState_NotReady()
{
}

void UIWidget::onExitState_NotReady(WidgetState i_toState)
{
}

void UIWidget::onEnterState_Pressed(WidgetState i_fromState)
{
}

void UIWidget::updateState_Pressed()
{
}

void UIWidget::onExitState_Pressed(WidgetState i_toState)
{
}

void UIWidget::onEnterState_Paused(WidgetState i_fromState)
{
}

void UIWidget::updateState_Paused()
{
}

void UIWidget::onExitState_Paused(WidgetState i_toState)
{
}

void UIWidget::updateStateMachine()
{
	m_stateMachine.UpdateState();
}

WidgetState UIWidget::getState() const
{
	return m_stateMachine.GetState();
}

int32 UIWidget::getWidgetStateSerialization()
{
	return m_stateMachine.GetState();
}

const SexyVector2& UIWidget::GetPositionOffset()
{
	if (m_positionOffsetOverriden)
		return m_overridePositionOffset;
	if (m_propertySheetPtr->ScalePositionOffset)
		return m_scaledPositionOffset;
	return m_propertySheetPtr->PositionOffset;
}

void UIWidget::onDestroy()
{
	DestroyChildren();
	DetachFromParent();
}

void UIWidget::Update()
{
	updateStateMachine();
	(this->*(&UIWidget::onUpdate))();
}

void UIWidget::StartLoad()
{
	if (!m_loadingResourcesList.empty())
		gLawnApp->PrepareLoadGroups(m_loadingResourcesList);
}

void UIWidget::UnloadResources()
{
	if (!m_loadingResourcesList.empty())
	{
		gLawnApp->DeleteGroups(m_loadingResourcesList);
		m_loadingResourcesList.clear();
	}
}

void UIWidget::TryUnlock(const std::string& i_levelName)
{
	UIWidgetSheet* sheet = m_propertySheetPtr->Cast<UIWidgetSheet>();
	if (!sheet->UnlockFrom.empty() && i_levelName.compare(sheet->UnlockFrom) == 0)
		m_unlocked = true;
}

void UIWidget::checkUnlocked()
{
	UIWidgetSheet* sheet = m_propertySheetPtr->Cast<UIWidgetSheet>();
	if (!sheet->UnlockFrom.empty())
	{
		PlayerInfo* profile = ProfileMgr::GetInstance().GetCurrentProfile();
		if (!profile || profile->GetWorldMapEventStatus(sheet->UnlockFrom) <= EVENTSTATUS_UNLOCKED)
			return;
	}
	m_unlocked = true;
	SetFlag(m_flags, UIFLAG_VISIBLE, true);
}

void UIWidget::CompleteLoad()
{
	if (isInState(WS_Loading))
	{
		if (!m_loadingResourcesList.empty())
			gLawnApp->FinalizeGroupLoads(m_loadingResourcesList);
		onLoadComplete();
		setState(WS_Initializing);
	}
}

void UIWidget::DestroyChildren()
{
	while (GetChildCount() > 0)
	{
		UIWidget* child = GetUIWidgetByRtId(GetChildId(0));
		child->DetachFromParent();
		child->Destroy();
	}
}

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(UIWidget);

void UIWidget::DetachFromParent()
{
	if (m_parentPtr)
	{
		RtWeakPtr<UIWidget> parent = m_parentPtr;
		m_parentPtr = RtWeakPtr<UIWidget>();
		calculatePosition();
		parent->RemoveChildWidget(this);
	}
}

void UIWidget::AddChildWidget(UIWidget* i_childPtr)
{
	RtId childId = i_childPtr->GetPtr().GetId();
	for (uint i = 0; i < m_childIdList.size(); i++)
	{
		if (m_childIdList[i] == childId)
			return;
	}
	m_childIdList.push_back(childId);
	i_childPtr->SetParentWidget(this);
}

void UIWidget::RemoveChildWidget(UIWidget* i_childPtr)
{
	RtId childId = i_childPtr->GetPtr().GetId();
	for (uint i = 0; i < m_childIdList.size(); i++)
	{
		if (m_childIdList[i] == childId)
		{
			m_childIdList.erase(m_childIdList.begin() + i);
			i_childPtr->DetachFromParent();
			return;
		}
	}
}

void UIWidget::SetParentWidget(UIWidget* i_parentPtr)
{
	if (i_parentPtr == NULL)
	{
		DetachFromParent();
	}
	else if (!(i_parentPtr->GetPtr() == m_parentPtr))
	{
		DetachFromParent();
		m_parentPtr = i_parentPtr->GetPtr();
		i_parentPtr->AddChildWidget(this);
		calculatePosition();
	}
}

void UIWidget::PrepForLoading()
{
	if (getWidgetStateSerialization() == -1)
	{
		const std::string& resourceGroup = m_propertySheetPtr->ResourceGroup;
		if (resourceGroup.size())
			m_loadingResourcesList.push_back(resourceGroup);
		initLoadingResourcesGroupList();
		setState(WS_Loading);
	}
}

void UIWidget::setState(const WidgetState i_newState)
{
	StateDefinition<WidgetState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<WidgetState>(GetClass())->GetStateDefinition(i_newState);
	newState.SetContext(this);
	setStateHelper(newState);
}

void UIWidget::setWidgetStateSerialization(int32 i_state)
{
	StateDefinition<WidgetState> newState =
		StateMachineTableBuilder::GetInstancePtr()->GetTable<WidgetState>(GetClass())->GetStateDefinition((WidgetState)i_state);
	newState.SetContext(this);
	m_stateMachine.SetStateNoTransition(newState);
}

void UIWidget::UpdateUI()
{
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_UIWIDGETS); it; ++it)
	{
		RtWeakPtr<UIWidget> widget(*it);
		widget.GetObject()->Cast<UIWidget>()->Update();
	}
}

const Sexy::Rect UIWidget::GetDrawRect()
{
	Sexy::Rect rect = GetRect();
	if (m_parentPtr)
	{
		Sexy::Rect parentRect = m_parentPtr->GetDrawRect();
		rect.mX += parentRect.mX;
		rect.mY += parentRect.mY;
	}
	return rect;
}

const Sexy::Point UIWidget::GetCenterPointOnScreen()
{
	Sexy::Rect rect = GetDrawRect();
	return Sexy::Point(rect.mX + GetWidth() / 2, rect.mY + GetHeight() / 2);
}

void UIWidget::translateToWidgetPosition(Graphics* i_g)
{
	i_g->mTransX = 0;
	i_g->mTransY = 0;
	Sexy::Rect rect = GetDrawRect();
	i_g->Translate(rect.mX, rect.mY);
}

void UIWidget::SetAtlasImageRectToRect(Sexy::Rect& io_rect, ImagePtr i_atlasedImage)
{
	io_rect.mX = i_atlasedImage->mAtlasStartX;
	io_rect.mY = i_atlasedImage->mAtlasStartY;
	io_rect.mWidth = i_atlasedImage->mAtlasEndX - i_atlasedImage->mAtlasStartX;
	io_rect.mHeight = i_atlasedImage->mAtlasEndY - i_atlasedImage->mAtlasStartY;
}

void UIWidget::ProcessedMouseMove(const int i_mouseX, const int i_mouseY, const uint8 i_maxInputPriority)
{
	if (m_mouseFocusWidget)
		m_mouseFocusWidget->OnMouseMove(i_mouseX, i_mouseY);
}

bool UIWidget::ProcessedMouseDown(const int i_mouseX, const int i_mouseY, const uint8 i_maxInputPriority)
{
	UIWidget* widget = GetMouseOverWidget(i_mouseX, i_mouseY, i_maxInputPriority);
	if (widget == NULL)
		return false;

	widget->OnMouseDown(i_mouseX, i_mouseY);
	m_mouseFocusWidget = widget->GetPtr();
	return true;
}

void UIWidget::ResetUI()
{
	m_mouseFocusWidget = NULL;
	for (Sexy::RtDbTable::Iterator it = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_UIWIDGETS); it; ++it)
	{
		Sexy::RtWeakPtr<UIWidget> widget = *it;
		if (UIWidget* w = widget)
			w->CastChecked<UIWidget>()->Destroy();
	}
	PVZDB::GetInstance().RunDeferredDeletions();
	Sexy::LazySingleton<Lua::CLuaEngine>::GetInstancePtr()->ExecuteTableFunction("luaApp", "ResetUIWidget");
}
