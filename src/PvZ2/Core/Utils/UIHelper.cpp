//
//  UIHelper.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "UIHelper.h"
#include "WorldMap_BackButton.h"

/////////////// UIHelper ///////////////

bool UIHelper::TriggerWorldMapBackButton()
{
	UIWidget* widget = UIWidget::GetWidgetBySheetName("UIWorldMapBackButton");

	if (widget)
	{
		WorldMap_BackButton* backButton = widget->Cast<WorldMap_BackButton>();

		if (backButton)
		{
			return backButton->OnBackButtonPressed();
		}
	}

	return false;
}
