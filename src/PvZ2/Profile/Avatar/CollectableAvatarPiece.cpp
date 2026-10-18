//
//  CollectableAvatarPiece.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-18.
//

#include "SexyAppFramework/Common.h"

#include "CollectableSpring.h"
#include "Board.h"
#include "Effect_StaticImage.h"
#include "LawnApp.h"
#include "Renderable.h"
#include "CollectableType.h"

CollectableAvatarPiece::CollectableAvatarPiece()
{
}

CollectableAvatarPiece::~CollectableAvatarPiece()
{
}

std::string CollectableAvatarPiece::GetPlantName() const
{
	return GetType()->CastChecked<CollectableAvatarPieceType>()->PlantName;
}

std::string CollectableAvatarPiece::GetTypeName() const
{
	return GetType()->CastChecked<CollectableAvatarPieceType>()->TypeName;
}

PlantAvatarType CollectableAvatarPiece::GetPlantAvatarType() const
{
	return GetType()->CastChecked<CollectableAvatarPieceType>()->AvatarType;
}

void CollectableAvatarPiece::onUpdate()
{
	Collectable::onUpdate();
	if (GetexpirationStartTime() < PVZ_EOT())
	{
		pvztime_t age = PVZ_T() - GetexpirationStartTime();
		if (GetType()->ExpireDuration - age <= 0.5f)
			TryToCollect();
	}
}

void CollectableAvatarPiece::initializeRenderEffect()
{
	const CollectableType* type = m_type;
	if (type->StandaloneImage.size())
	{
		Effect_StaticImage* effect = NULL;
		{
			ImagePtr image = gLawnApp->GetUIImageFromStringId(type->StandaloneImage);
			bool hasImage = image;
			if (__builtin_expect(!!hasImage, 1))
			{
				effect = gLawnApp->m_board->AddEffect<Effect_StaticImage>();
				Effect_StaticImage* staticImage = effect->CastChecked<Effect_StaticImage>();
				staticImage->SetImage(image);
				staticImage->SetCentered(true);
			}
		}
		if (__builtin_expect(!!(effect), 1))
		{
			m_renderEffect = effect->GetPtr();
			effect->SetAttached(this, type->RenderOffset, 2);
			effect->SetRenderLayerOverride(RENDER_LAYER_ABOVE_UI + 1);
			effect->SetScale(type->Scale);
			m_scale = type->Scale;
		}
	}
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableAvatarPiece);
