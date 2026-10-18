//
//  NetworkRichManConfig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "RichmanDefine.h"
#include "RichmanTileEvent.h"
#include "RichManUIMgr.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////


RT_CLASS_IMPLEMENT(NetworkRichManConfig);

void NetworkRichManConfig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(NetworkRichManConfig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Sexy::RtObject);

	REFLECTION_CLASSBUILDER_END(NetworkRichManConfig);
}

/////////////// Operators ///////////////

static void EmitCopyAssign(NetworkRichManConfig& o_dst, const NetworkRichManConfig& i_src) __attribute__((used));
static void EmitCopyAssign(NetworkRichManConfig& o_dst, const NetworkRichManConfig& i_src)
{
	o_dst = i_src;
}
