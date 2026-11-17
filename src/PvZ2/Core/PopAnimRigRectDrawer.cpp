//
//  PopAnimRigRectDrawer.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//

#include "SexyAppFramework/Common.h"

#include "PvZ/PopAnimRigHelper.h"

/////////////// Lifecycle ///////////////

PopAnimRigRectDrawer::PopAnimRigRectDrawer(PopAnimRig* i_animRig)
    : m_animRig(i_animRig)
{
    if (m_animRig)
        m_animRig->CalcRigDrawingRect(m_frameRect);
}

PopAnimRigRectDrawer::~PopAnimRigRectDrawer()
{
    if (m_animRig)
        delete m_animRig;
}

/////////////// Logic ///////////////

void PopAnimRigRectDrawer::Update(pvztime_t i_t, pvztime_t i_dt)
{
    m_animRig->UpdateAnim(i_t, i_dt);
}

void PopAnimRigRectDrawer::PlayAndStop(const std::string& i_animLabel, PopAnimRig::AnimStoppedDelegate i_onAnimStopped)
{
    m_animRig->PlayAndStop(i_animLabel, SELECT_EXACT, i_onAnimStopped);
}
