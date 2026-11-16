//
//  DinosaurRaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "DinosaurRaptor.h"

DinosaurRaptor::DinosaurRaptor()
{
}

DinosaurRaptor::~DinosaurRaptor()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurRaptor);

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(DinosaurRaptorPropertySheet);

void DinosaurRaptorPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(DinosaurRaptorPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(DinosaurPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(Rect, FlipAttackRect);
	REFLECTION_CLASSBUILDER_END(DinosaurRaptorPropertySheet);
}
