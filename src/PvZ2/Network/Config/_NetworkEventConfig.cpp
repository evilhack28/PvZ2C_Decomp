//
//  _NetworkEventConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "NetWorkEvent.h"

std::string _NetworkEventConfig::m_stageURL;

static void (*const s_emit[])() __attribute__((used)) = {
	(void (*)())&_NetworkEventConfig::SetStageURL,
	(void (*)())&_NetworkEventConfig::GetStageURL,
	(void (*)())&_NetworkEventConfig::HasStageURL,
};

static void EmitCtorDtor() __attribute__((used));
static void EmitCtorDtor()
{
	NetworkEventConfig* aConfig = new NetworkEventConfig;
	delete aConfig;
}
