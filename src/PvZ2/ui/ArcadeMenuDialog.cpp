//
//  ArcadeMenuDialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArcadeMenuDialog.h"

ArcadeMenuDialog::ArcadeMenuDialog()
{
}

ArcadeMenuDialog::~ArcadeMenuDialog()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(ArcadeMenuDialog);

void ArcadeMenuDialog::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArcadeMenuDialog);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(ArcadeMenuDialog);
}

ArcadeMenuDialog* ArcadeMenuDialog::Clone() const
{
	return GetClass()->New()->Cast<ArcadeMenuDialog>();
}
