//
//  PopAnimEffectFactory.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "GameObject.h"
#include "RtObject.h"

#include "PopAnimEffectFactory.h"

#include "Board.h"
#include "LawnApp.h"
#include "PopAnim.h"
#include "Effect_PopAnim.h"

using namespace Sexy;

/////////////// PopAnimEffectFactory ///////////////

RtWeakPtr<GameObject> PopAnimEffectFactory::CreateEffect(std::string name, int layer, SexyVector3 position, bool isScreenSpaceEffect, bool isVisible)
{
	Effect_PopAnim* effect = gLawnApp->m_board->AddEffect<Effect_PopAnim>();
	effect->CreatePopAnimRig(GetPAMByName(name), NULL);
	effect->SetBoardSpaceOrigin(position, -1);
	effect->SetRenderLayerOverride(layer);
	effect->SetIsScreenSpaceEffect(isScreenSpaceEffect);
	effect->SetVisibility(isVisible);
	return effect->GetPtr();
}
