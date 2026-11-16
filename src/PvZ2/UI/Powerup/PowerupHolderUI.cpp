//
//  PowerupHolderUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PowerupHolderUI.h"
#include "PowerupUI.h"
namespace MiniGameCollectionUtils { bool IsPlayingMiniGameCollectionLevel(); }
#include "PVZ2UIButton.h"
#include "RedPacketRewardInfo.h"

PowerupHolderUI::PowerupHolderUI()
{
}

PowerupHolderUI::~PowerupHolderUI()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PowerupHolderUI);

/////////////// Functions ///////////////

static WEAKIMAGE(IMAGE_UI_HUD_INGAME_POWERUP_CUKE_FRAME, "IMAGE_UI_HUD_INGAME_POWERUP_CUKE_FRAME")
static WEAKIMAGE(IMAGE_UI_POWERUPS_POWERUP_FRAME_MINIGAMES, "IMAGE_UI_POWERUPS_POWERUP_FRAME_MINIGAMES")

static bool FlagClickable(UIWidgetFlags f) { return TestFlag(f, UIFLAG_CLICKABLE); }
static int UiScaleI(int v) { return UI_S(v); }
static float UiScaleF(float v) { return UI_S(v); }
static int IdentI(int v) { return v; }

void PowerupHolderUI::AddPowerup(PowerupTypePtr i_powerupType, bool i_isLocked)
{
    UIWidget* widget = UIWidget::CreateWidget(Sexy::RtName(L"UIPowerup"), true);
    PowerupUI* powerupUI = widget->CastChecked<PowerupUI>();
    powerupUI->SetPowerupType(i_powerupType);
    powerupUI->SetIsLocked(i_isLocked);
    int index = GetChildCount();
    int offsetX = UiScaleI(15);
    float step = index * 12.5f;
    Sexy::SexyVector2 pos(offsetX - UiScaleF(step) - IdentI(widget->m_boundingRect.mWidth) * index, UiScaleI(-15));
float scaledStep = UiScaleF(step);    m_offset_x = -(IdentI(widget->m_boundingRect.mWidth) * index + scaledStep);
    powerupUI->SetParentWidget(this);
    powerupUI->SetPositionOffset(pos);
}

void PowerupHolderUI::Draw(Graphics* i_g)
{
    UIWidget::Draw(i_g);
    GraphicsAutoState state(i_g);
    translateToWidgetPosition(i_g);
    if (!FlagClickable(m_flags))
    {
        i_g->SetColor(Color(128, 128, 128));
        i_g->SetColorizeImages(true);
    }
    if (!MiniGameCollectionUtils::IsPlayingMiniGameCollectionLevel())
    {
        if (GetChildCount() > 1)
            i_g->DrawImage(IMAGE_UI_POWERUPS_POWERUP_FRAME_MINIGAMES, (int)m_offset_x, 0);
        else
            i_g->DrawImage(IMAGE_UI_HUD_INGAME_POWERUP_CUKE_FRAME, 0, 0);
    }
}
