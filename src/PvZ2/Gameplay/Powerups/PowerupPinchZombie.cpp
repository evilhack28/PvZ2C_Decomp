//
//  PowerupPinchZombie.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PowerupPinchZombie.h"
#include "LawnApp.h"
#include "Board.h"
#include "ScaledApp.h"
#include "Zombie.h"
#include "EntityFinder.h"
#include "ZombieAnimRig.h"
#include "Effect_PopAnim.h"
#include "DamageInfo.h"
#include "AudioMgr.h"
#include <limits>

PowerupPinchZombie::~PowerupPinchZombie()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupPinchZombie);

void PowerupPinchZombie::registerForEvents()
{
	gLawnApp->m_board->RegisterGesture(Sexy::MakeDelegate(*this, &PowerupPinchZombie::handlePinch));
}

void PowerupPinchZombie::unregisterForEvents()
{
	gLawnApp->m_board->UnregisterGesture(this);
}

/////////////// Pinch ///////////////

template <class T>
static T Pass(T i_value)
{
	return i_value;
}

static int ScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->ScaleNum(i_num);
}

static int ScreenScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->ScreenScaleNum(i_num);
}

static SexyVector2 ToScreen(SexyVector3 i_position)
{
	return SexyVector2(i_position.x, i_position.y - i_position.z);
}

void PowerupPinchZombie::handlePinch(Sexy::Point i_center, int i_distanceBetweenFingersSquared, float i_scaleDelta)
{
	if (isInState(1) || isInState(2))
	{
		int maxDistance = ScaleNum(98);
		bool isPad = IsDeviceIOS();
		if (isPad)
		{
			if (!(!(i_scaleDelta >= 0) && i_distanceBetweenFingersSquared <= maxDistance * maxDistance))
				return;
		}
		else
		{
			maxDistance = ScaleNum(250);
			if (!(!(i_scaleDelta >= 0) && i_distanceBetweenFingersSquared <= maxDistance * maxDistance))
				return;
		}
		{
			Board* board = gLawnApp->m_board;
			int x = ScreenScaleNum(i_center.mX - board->mX);
			int y = ScreenScaleNum(i_center.mY - board->mY);
			SexyVector2 touch((float)x, (float)y);
			std::vector<BoardEntity*> entities;
			EntityFinder::GetEntitiesTouchingCircle2D(entities, ENTITYTYPE_ZOMBIE, touch, 20.0f, -1, -1);
			float best = std::numeric_limits<float>::max();
			Zombie* closest = NULL;
			for (size_t i = 0; i < entities.size(); i++)
			{
				Zombie* zombie = (Zombie*)entities[i];
				SexyVector2 head = zombie->GetAnimRig()->GetHeadOffset();
				float dist = (ToScreen(zombie->m_position) + head - touch).MagnitudeSquared();
				if (zombie->IsDying() || (best > dist) <= zombie->IsBleedingOut() || !zombie->IsValidPinchTarget() || Pass((int)zombie->m_helm) - 4U < 2)
					continue;
				best = dist;
				closest = zombie;
			}

			if (closest != NULL)
			{
				if (closest->HasHead())
				{
					do
					{
						if (Pass(m_timeRemaining) <= 0.0f)
							break;
						ResilienceDamageInfo resilience(1.0f, 0.0f);
						DamageInfo damage(0.0f, DAMAGE_NONE, NULL, Point(-1, -1), false, resilience);
						switch (Pass((int)closest->m_helm))
						{
						case HELMTYPE_NONE:
						case 6:
						case 7:
						case 8:
							damage.Amount = closest->GetHitpointsUntilBleedout() + 1.0f;
							break;
						case HELMTYPE_CONE:
							damage.Amount = Pass(closest->m_helmHitpoints);
							damage.Flags = DAMAGE_HITS_ONLY_SHIELD;
							break;
						case HELMTYPE_BUCKET:
						case 10:
							damage.Amount = Pass(closest->m_maxHelmHitpoints) * 0.5f;
							damage.Flags = DAMAGE_HITS_ONLY_SHIELD;
							break;
						}
						closest->TakeDamage(damage);
						gMessageRouter->Post(&Message::ZombiePinched, closest);
						if (isInState(1))
							Activate();
						DecrementTimeByUseCost();
					} while (closest->HasHead());
				}

				Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>()->CastChecked<Effect_PopAnim>();
				effect->CreatePopAnimRig(GetPAMByName("POPANIM_EFFECTS_POWER_UP_HEAD_PINCH"), NULL);
				effect->SetCentered(true);
				effect->PlaySingleAnimation("animation");
				effect->SetBoardSpaceOrigin(SexyVector3(touch.x, touch.y, 0), 800000);
				effect->SetOrientation(RandRangeFloat(0.0f, 6.2831855f));
				if (!isPad)
					effect->SetScale(1.5f);
				AudioMgr::GetInstancePtr()->SendEvent("Play_UI_PowerUP_Pincher", NULL);
			}
		}
	}
}
