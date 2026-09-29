//
//  GridItemFlame.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemFlame.h"

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemFlame);

void GridItemFlame::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemFlame);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<PopAnimRig>, m_flamePopAnimRig);
		REFLECTION_CLASSBUILDER_FIELD(int32, m_row);
		REFLECTION_CLASSBUILDER_FIELD(bool, m_doDisappear);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<RtWeakPtr<Projectile> >, m_affectedProjectiles);
		REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<BoardEntity>, m_attachedEntity);
	REFLECTION_CLASSBUILDER_END(GridItemFlame);
}
