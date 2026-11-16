//
//  CypripediumPlantfoodAvatar.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "Plant_Cypripedium.h"
#include "Board.h"
#include "Effect_PopAnim.h"
#include "EntityFinder.h"
#include "LawnApp.h"
#include "Renderable.h"
#include "Zombie.h"

CypripediumPlantfoodAvatar::CypripediumPlantfoodAvatar()
{
}

CypripediumPlantfoodAvatar::~CypripediumPlantfoodAvatar()
{
}

bool CypripediumPlantfoodAvatar::OnCollideEntity(BoardEntity* i_entity)
{
	if (i_entity)
	{
		SexyVector3 position = i_entity->GetPosition();
		position.y -= 30.0f;
		Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
		effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_CYPRIPEDIUM_PLANTFOOD_AVATAR"), NULL);
		effect->SetBoardSpaceOrigin(position, -1);
		effect->SetCentered(true);
		effect->SetRenderLayerOverride(RENDER_LAYER_ABOVE_UI + 1);
		effect->PlaySingleAnimation("smoke");

		std::vector<BoardEntity*> entities;
		BoardEntityTypeFlag types = ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM;
		int column = i_entity->CalcColumnPosition();
		int row = i_entity->CalcRowPosition();
		EntityFinder::GetEntitiesInGridSquares(entities, types, Sexy::Rect(column - 2, row - 2, 5, 5));
		std::vector<BoardEntity*>::iterator it = entities.begin();
		std::vector<BoardEntity*>::iterator end = entities.end();
		for (; it != end; ++it)
		{
			BoardEntity* entity = *it;
			Zombie* zombie = entity->Cast<Zombie>();
			if (zombie)
			{
				zombie->ApplyCondition(ZCONDITION_BadSmell, 3.0f, 0.0f, true);
				zombie->ApplyCondition(ZCONDITION_Stucked, 2.0f, 0.0f, true);
			}
			if (entity != i_entity)
				healEntity(entity);
		}
	}
	return Projectile::OnCollideEntity(i_entity);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CypripediumPlantfoodAvatar);

void CypripediumPlantfoodAvatar::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(CypripediumPlantfoodAvatar);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(Projectile);

	REFLECTION_CLASSBUILDER_END(CypripediumPlantfoodAvatar);
}
