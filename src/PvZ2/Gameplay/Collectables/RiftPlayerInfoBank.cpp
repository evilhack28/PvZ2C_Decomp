//
//  RiftPlayerInfoBank.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "RiftPlayerInfoBank.h"

RiftPlayerInfoBank::RiftPlayerInfoBank()
{
}

RiftPlayerInfoBank::~RiftPlayerInfoBank()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(RiftPlayerInfoBank);

void RiftPlayerInfoBank::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(RiftPlayerInfoBank);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(UIWidget);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Image>, m_leagueImg);
	REFLECTION_CLASSBUILDER_END(RiftPlayerInfoBank);
}
