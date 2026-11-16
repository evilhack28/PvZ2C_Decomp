//
//  CustomLevelTemplate.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "CustomLevelTemplate.h"

/////////////// CustomLevelTemplate ///////////////

CustomLevelTemplate::CustomLevelTemplate(CustomLevelMgr* i_manager)
{
	m_manager = i_manager;
}

CustomLevelMgr* CustomLevelTemplate::getManager()
{
	return m_manager;
}
