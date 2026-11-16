//
//  PlantPropertySheet.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-16.
//

#include "SexyAppFramework/Common.h"

#include "PlantPropertySheet.h"
#include "Plant.h"

bool PlantPropertySheet::IsAbstract() const
{
	return false;
}


float PlantPropertySheet::GetPacketCoolDownTime(int iStarLv) const
{
	return PacketCooldown;
}

Sexy::Rect PlantPropertySheet::GetCollisionRect(Plant *plant) const
{
	const SexyVector3 &aPos = plant->GetPosition();
	float aPosX = aPos.x;
	int aX = (int)((HitRectAdjust.mX + aPosX) - (float)(plant->GetWidth() / 2));
	float aPosY = aPos.y;
	int aY = (int)(((aPosY + 10.0f) + HitRectAdjust.mY) - (float)plant->GetHeight());
	int aWidth = plant->GetWidth() + HitRectAdjust.mWidth;
	int aHeight = plant->GetHeight() + HitRectAdjust.mHeight;
	return Sexy::Rect(aX, aY, aWidth, aHeight);
}
