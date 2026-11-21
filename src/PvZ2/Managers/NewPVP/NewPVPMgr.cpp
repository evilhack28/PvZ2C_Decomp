//
//  NewPVPMgr.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "NewPVPGame.h"

/////////////// Lifecycle ///////////////

void NewPVPMgr::Update()
{
	updateFrameCalc();
}

bool NewPVPMgr::canStartFrameCalc()
{
	return m_nextFramesCalcTime == PVZ_EOT();
}

bool NewPVPMgr::IsPreviousMatchingTimeout()
{
	return true;
}

void NewPVPMgr::StartFrameCalc()
{
	if (canStartFrameCalc())
	{
		ResetFrameInfo();
		m_nextFramesCalcTime = PVZ_RealT();
	}
}

void NewPVPMgr::ResetFrameInfo()
{
	m_frames = 0.0f;
	m_nextFramesCalcTime = PVZ_EOT();
	m_totalFramesFragment = 0.0f;
	m_framesCalcCount = 0;
	m_currentFrames = 0.0f;
	m_totalFrameFragmentCount = 0;
	for (int i = 0; i < MAX_FRAME_ARRAY_SIZE; i++)
		m_framesArray[i] = 0.0f;
}

void NewPVPMgr::updateFrameCalc()
{
	if (m_nextFramesCalcTime == PVZ_EOT())
		return;

	float aFPS = TimeMgr::GetInstancePtr()->GetCurrentFPS();
	if (m_frames != aFPS)
	{
		m_frames = aFPS;
		m_totalFrameFragmentCount++;
		m_totalFramesFragment += aFPS;
	}

	if (PVZ_RealT() - m_nextFramesCalcTime >= 1.0f)
	{
		float anAverage = m_totalFramesFragment / m_totalFrameFragmentCount;
		m_framesArray[m_framesCalcCount % MAX_FRAME_ARRAY_SIZE] = anAverage;
		m_framesCalcCount++;
		m_totalFrameFragmentCount = 0;
		m_frames = 0.0f;
		m_totalFramesFragment = 0.0f;
		m_currentFrames = anAverage;
		m_nextFramesCalcTime = PVZ_RealT();
	}
}
