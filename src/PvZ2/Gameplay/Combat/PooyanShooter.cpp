//
//  PooyanShooter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PooyanShooter.h"

PooyanShooter::~PooyanShooter()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PooyanShooter);

void PooyanShooter::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PooyanShooter);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(BoardEntity);

		REFLECTION_CLASSBUILDER_FIELD(Plant *, m_plantPtr);
	REFLECTION_CLASSBUILDER_END(PooyanShooter);
}

#include "BoardEntity.h"
void PooyanShooter::onInitialized()
{
	 BoardEntity::onInitialized();
}
