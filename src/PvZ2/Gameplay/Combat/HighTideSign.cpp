//
//  HighTideSign.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "HighTideSign.h"

HighTideSign::HighTideSign()
{
}

HighTideSign::~HighTideSign()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(HighTideSign);

void HighTideSign::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(HighTideSign);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

	REFLECTION_CLASSBUILDER_FIELD(float, m_highTideLevel);
	REFLECTION_CLASSBUILDER_FIELD(int, m_signType);

	REFLECTION_CLASSBUILDER_END(HighTideSign);
}
