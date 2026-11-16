//
//  ArcadePowerUpTemplateAdaptor.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "ArcadePowerUpTemplateAdaptor.h"

#include "PowerUpUIButton.h"
#include "HotUIPowerUpButton.h"
#include "HotUIAnim.h"
#include "HotUILabel.h"
#include "HotUIManager.h"
#include "ReflectionBuilder.h"
#include "ArcadePropertySheet.h"
#include "ArcadeProgressDatabase.h"
#include "ProfileUtils.h"

RT_CLASS_IMPLEMENT(ArcadePowerUpTemplateAdaptor);

void ArcadePowerUpTemplateAdaptor::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(ArcadePowerUpTemplateAdaptor);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(HotUIAdaptor);

	REFLECTION_CLASSBUILDER_END(ArcadePowerUpTemplateAdaptor);
}

/////////////// Methods ///////////////

void ArcadePowerUpTemplateAdaptor::Configure(WidgetContainer* i_parent, const std::string& i_collectionID, const std::string& i_powerUpID)
{
	m_parent = i_parent;
	m_collectionID = i_collectionID;
	m_powerUpID = i_powerUpID;
}

bool ArcadePowerUpTemplateAdaptor::IsConfiguredForPowerUp(const std::string& i_collectionID, const std::string& i_powerUpID) const
{
	return m_collectionID == i_collectionID && m_powerUpID == i_powerUpID;
}

void ArcadePowerUpTemplateAdaptor::onLinkToUIViewCreated()
{
	PowerUpUIButton* button = GetPowerUpUIButton();
	if (button != nullptr)
		button->SetType(m_collectionID, m_powerUpID);
	RefreshUnlockStatus();
}

std::string ArcadePowerUpTemplateAdaptor::getUIFileName()
{
	return "ArcadePowerUpTemplate";
}

HotUIAnim* ArcadePowerUpTemplateAdaptor::GetLockAnimation() const
{
	return getUIFile()->GetWidgetByName<HotUIAnim>("LockAnim");
}

PowerUpUIButton* ArcadePowerUpTemplateAdaptor::GetPowerUpUIButton() const
{
	HotUIWidget* widget = getUIFile()->GetWidgetByType(HotUIPowerUpButton::StaticGetClass());
	if (widget != nullptr && widget->IsA<HotUIPowerUpButton>())
		return widget->Cast<HotUIPowerUpButton>()->GetWrappedWidget();
	return nullptr;
}

void ArcadePowerUpTemplateAdaptor::onLoadUIView()
{
	HotUIStringMap overrides;
	HotUIFile* file = HotUIManager::GetInstance().LoadUIFile(getUIFileName(), overrides, m_parent);
	addLinkToUIFile(file);
}

std::string ArcadePowerUpTemplateAdaptor::getProgressText() const
{
	int current = 0;
	int goal = 0;
	getProgressTowardPowerUp(current, goal);
	if (current > goal)
		current = goal;
	if (goal > 0)
		return Sexy::StrFormat("%d / %d", current, goal);
	return "";
}

void ArcadePowerUpTemplateAdaptor::getProgressTowardPowerUp(int& o_currentValue, int& o_goalValue) const
{
	o_goalValue = 0;
	o_currentValue = 0;
	const ArcadePropertySheet* props = ArcadePropertySheet::Get();
	ArcadeProgressDatabase database(ProfileUtils::Profile(), props);
	std::vector<ArcadePropertySheetHelpers::UnlockSource> sources = props->GetUnlockSourcesForPowerUp(m_powerUpID, m_collectionID);
	if (!sources.empty())
	{
		const ArcadePropertySheetHelpers::UnlockSource& source = sources.front();
		o_goalValue = source.CompletionValue;
		if (source.Type == ArcadePropertySheetHelpers::LevelPack)
		{
			const ArcadePropertySheetHelpers::ArcadeLevelPack& pack = props->GetLevelPackByID(source.ID);
			for (const ArcadePropertySheetHelpers::ArcadeLevel& level : pack.Levels)
			{
				if (database.IsLevelComplete(level.ID))
					o_currentValue++;
			}
		}
		else if (source.Type == ArcadePropertySheetHelpers::EndlessLevel)
		{
			o_currentValue = database.GetHighestCompletedEndlessWave(source.ID);
		}
	}
}

void ArcadePowerUpTemplateAdaptor::RefreshUnlockStatus()
{
	ArcadeProgressDatabase database(ProfileUtils::Profile(), ArcadePropertySheet::Get());
	bool unlocked = database.IsPowerUpUnlocked(m_powerUpID, m_collectionID);
	HotUIFile* file = getUIFile();
	HotUIAnim* lockAnim = GetLockAnimation();
	lockAnim->PlayAndStop(unlocked ? "unlocked" : "locked");
	HotUILabel* label = file->GetWidgetByName<HotUILabel>("ProgressLabel");
	label->SetText(Sexy::UTF8StringToWString(getProgressText()));
	PowerUpUIButton* button = GetPowerUpUIButton();
	if (button != nullptr)
		button->RefreshUnlockState();
}
