//
//  AdaptorPerkSelectionDialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "AdaptorPerkSelectionDialog.h"

AdaptorPerkSelectionDialog::AdaptorPerkSelectionDialog()
{
	m_difficultyList = 0;
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(AdaptorPerkSelectionDialog);

void AdaptorPerkSelectionDialog::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(AdaptorPerkSelectionDialog);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(AdaptorPerkSelectionDialog);
}

#include "AdaptorPerkSelectionDialog.h"
void AdaptorPerkSelectionDialog::onPerkSelected(std::string i_perkName, bool i_needsAnimation, Point& i_startPoint)
{
	 AdaptorPerkSelectionDialog::refresh();
}

#include "AdaptorPerkSelectionDialog.h"
void AdaptorPerkSelectionDialog::onPerkSelectionChanged(std::string i_perkName)
{
	 AdaptorPerkSelectionDialog::refresh();
}

#include "AdaptorPerkSelectionDialog.h"
void AdaptorPerkSelectionDialog::Close()
{
	 AdaptorPerkSelectionDialog::verifySelectedPerksAndContinue();
}
