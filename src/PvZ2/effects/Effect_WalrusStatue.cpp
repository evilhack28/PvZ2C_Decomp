//
//  Effect_WalrusStatue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "GridItemWalrusStatue.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_WalrusStatue);

void Effect_WalrusStatue::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_WalrusStatue);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Effect_PopAnim);

	REFLECTION_CLASSBUILDER_FIELD(bool, m_bDieExit);

	REFLECTION_CLASSBUILDER_END(Effect_WalrusStatue);
}
