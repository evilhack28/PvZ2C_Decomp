//
//  CollectableAdBox.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "CollectableAdBox.h"

bool CollectableAdBox::CanChangeColorState()
{
	return true;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(CollectableAdBox);

#include "Collectable.h"
void CollectableAdBox::onUpdate()
{
	 Collectable::onUpdate();
}
