//
//  CUIAnim.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "LuaEngine/CUIAnim.h"
#include "UIEditor/StringHelper.h"

using namespace Lua;

/////////////// CUIAnim ///////////////

CUIAnim::CUIAnim(const std::string& i_name)
{
	m_effect = nullptr;
	m_effect = GameObject::CreateOutsideTable<Effect_PopAnim>();
	PopAnim* rig = StringHelper::ToAnimRig(i_name);
	m_effect->CreatePopAnimRig(rig, nullptr);
	m_effect->SetCentered(true);
	m_effect->SetVisibility(true);
}

CUIAnim::~CUIAnim()
{
	if (m_effect)
	{
		delete m_effect;
		m_effect = nullptr;
	}
}

void CUIAnim::SetScale(float i_x, float i_y)
{
	if (m_effect)
		m_effect->SetScale(i_x, i_y);
}

void CUIAnim::Move(int i_x, int i_y)
{
	if (m_effect)
		m_effect->SetScreenSpaceOrigin(SexyVector2((float)i_x, (float)i_y), 900000);
}

void CUIAnim::PlayAction(std::string i_action, bool i_loop)
{
	if (m_effect)
	{
		if (i_loop)
			m_effect->PlayLoopingAnimation(i_action, PVZ_EOT());
		else
			m_effect->PlaySingleAnimation(i_action);
	}
}

void CUIAnim::Update()
{
	Widget::Update();
	if (m_effect)
		m_effect->Update();
}

void CUIAnim::Draw(Sexy::Graphics* g)
{
	Widget::Draw(g);
	if (m_effect)
		m_effect->Draw(g);
}
