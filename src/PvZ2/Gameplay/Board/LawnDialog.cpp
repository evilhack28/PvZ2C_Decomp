//
//  LawnDialog.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "LawnDialog.h"
#include "AudioMgr.h"
#include "LawnApp.h"
#include "PlantType.h"
#include "PlantAnimRig.h"
#include "PopAnimRigHelper.h"
#include "GameButton.h"
#include "ScaledApp.h"
#include "PrimeText_Game.h"
#include "ResourceHelpers.h"
#include "TodLib/TodStringFile.h"
#include "RedPacketRewardInfo.h"
#include "PlantPropertySheet.h"
#include "SexyAppFramework/PopAnim.h"
#include "SexyAppFramework/Graphics.h"

static int gDialogColors[][3] =
{
	{255, 255, 255},
	{255, 255, 0},
	{255, 255, 255},
	{255, 255, 255},
	{255, 255, 255},
	{80, 80, 80},
	{255, 255, 255}
};

static WEAKIMAGE(IMAGE_UI_BUTTONS_GREEN, "IMAGE_UI_BUTTONS_GREEN")
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_TOPLEFT("IMAGE_DIALOG_TOPLEFT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_TOPRIGHT("IMAGE_DIALOG_TOPRIGHT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_TOPMIDDLE("IMAGE_DIALOG_TOPMIDDLE");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_BOTTOMLEFT("IMAGE_DIALOG_BOTTOMLEFT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_BIGBOTTOMLEFT("IMAGE_DIALOG_BIGBOTTOMLEFT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_CENTERLEFT("IMAGE_DIALOG_CENTERLEFT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_BOTTOMMIDDLE("IMAGE_DIALOG_BOTTOMMIDDLE");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_BOTTOMRIGHT("IMAGE_DIALOG_BOTTOMRIGHT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_BIGBOTTOMMIDDLE("IMAGE_DIALOG_BIGBOTTOMMIDDLE");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_BIGBOTTOMRIGHT("IMAGE_DIALOG_BIGBOTTOMRIGHT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_CENTERRIGHT("IMAGE_DIALOG_CENTERRIGHT");
static CachedResourcePtr<Sexy::Image> IMAGE_DIALOG_CENTERMIDDLE("IMAGE_DIALOG_CENTERMIDDLE");

__attribute__((noclone)) static int ScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->ScaleNum(i_num);
}

__attribute__((noclone)) static float ScaleNum(float i_num)
{
	return ((ScaledApp*)gSexyApp)->ScaleNum(i_num);
}

/////////////// Lifecycle ///////////////

LawnDialog::LawnDialog(int i_id, bool isModal, const SexyString& i_dialogHeader, const SexyString& i_dialogLines, const SexyString& i_dialogFooter, int i_buttonMode) :
	Dialog(i_id, isModal, i_dialogHeader, i_dialogLines, _S(""), Dialog::BUTTONS_NONE)
{
	m_lawnYesButton = NULL;
	m_lawnNoButton = NULL;
	m_buttonDelay = -1;
	m_drawStandardBack = true;
	m_popAnimRig = NULL;
	m_tallBottom = false;
	m_verticalCenterText = true;
	m_onYesButtonPressed = ButtonPressDelegate();
	m_onNoButtonPressed = ButtonPressDelegate();
	mDialogHeader = TodStringTranslate(i_dialogHeader);
	mDialogLines = TodStringTranslate(i_dialogLines);
	SetHeaderFont(FONT_DIALOG_LABEL);
	SetLinesFont(FONT_DIALOG_LINES);
	mContentInsets = Insets(ScaleNum(56), ScaleNum(25), ScaleNum(56), ScaleNum(36));
	mSpaceAfterHeader = ScaleNum(3);
	SetButtonImage(IMAGE_UI_BUTTONS_GREEN, i_buttonMode, i_dialogFooter);
	gLawnApp->SetCursor(CURSOR_POINTER);
}

LawnDialog::~LawnDialog()
{
	delete m_lawnYesButton;
	delete m_lawnNoButton;
	if (m_popAnimRig)
	{
		if (m_plantType)
			gLawnApp->DeleteGroup(m_plantType->PlantFramework);
		SAFE_DELETE(m_popAnimRig);
	}
}

/////////////// Accessors ///////////////

int LawnDialog::GetLeft()
{
	return mContentInsets.mLeft + mBackgroundInsets.mLeft;
}

int LawnDialog::GetWidth()
{
	return mWidth - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight;
}

int LawnDialog::GetTop()
{
	return mContentInsets.mTop + mBackgroundInsets.mTop + 99;
}

void LawnDialog::SetStaticImage(ImagePtr i_img)
{
	m_staticImage = i_img;
}

void LawnDialog::SetPopAnim(PopAnim* i_pam, const std::string& i_animName)
{
	SAFE_DELETE(m_popAnimRig);
	m_popAnimRig = PopAnimRig::CreateRigOutsideTable(i_pam);
	m_popAnimRig->PlayAndContinue(i_animName);
	CalcSize(0, ScaleNum(0));
}

/////////////// Logic ///////////////

void LawnDialog::OrderInManagerChanged()
{
}

void LawnDialog::ButtonPress(int i_id)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_UI_Menu_Button_Select", NULL);
}

void LawnDialog::CheckboxChecked(int i_id, bool cheked)
{
	AudioMgr::GetInstancePtr()->SendEvent("Play_Buttonclick", NULL);
}

void LawnDialog::CalcSize(int i_extraX, int i_extraY, bool i_padDialogWidth)
{
	if (mHeaderFont && mLinesFont)
		CalcSizeWithFont(i_extraX, i_extraY, i_padDialogWidth);
	else if (mHeaderPrimeFont && mLinesPrimeFont)
		CalcSizeWithPrimeFont(i_extraX, i_extraY, i_padDialogWidth);
}

void LawnDialog::KeyDown(KeyCode i_key)
{
	if (i_key == KEYCODE_SPACE || i_key == KEYCODE_RETURN || i_key == (KeyCode)'Y' || i_key == (KeyCode)'y')
	{
		Dialog::ButtonDepress(Dialog::ID_YES);
	}
	else if ((i_key == (KeyCode)'N' || i_key == (KeyCode)'n' || i_key == KEYCODE_ESCAPE) && m_lawnNoButton)
	{
		Dialog::ButtonDepress(Dialog::ID_NO);
	}
}

void LawnDialog::SetButtonDelay(int i_delay)
{
	m_buttonDelay = i_delay;
	if (m_lawnYesButton)
		m_lawnYesButton->SetDisabled(true);
	if (m_lawnNoButton)
		m_lawnNoButton->SetDisabled(true);
}

void LawnDialog::AddedToManager(WidgetManager* i_widgetManager)
{
	Dialog::AddedToManager(i_widgetManager);
	if (m_lawnYesButton)
		AddWidget(m_lawnYesButton);
	if (m_lawnNoButton)
		AddWidget(m_lawnNoButton);
}

void LawnDialog::RemovedFromManager(WidgetManager* i_widgetManager)
{
	Dialog::RemovedFromManager(i_widgetManager);
	if (m_lawnYesButton)
		RemoveWidget(m_lawnYesButton);
	if (m_lawnNoButton)
		RemoveWidget(m_lawnNoButton);
}

void LawnDialog::ButtonDepress(int i_id)
{
	if (i_id == Dialog::ID_YES && m_onYesButtonPressed)
		m_onYesButtonPressed();
	else if (i_id == Dialog::ID_NO && m_onNoButtonPressed)
		m_onNoButtonPressed();
	else
		Dialog::ButtonDepress(i_id);
}

void LawnDialog::Update()
{
	Dialog::Update();
	if (mUpdateCnt == m_buttonDelay)
	{
		if (m_lawnYesButton)
			m_lawnYesButton->SetDisabled(false);
		if (m_lawnNoButton)
			m_lawnNoButton->SetDisabled(false);
	}
	if (m_popAnimRig)
		m_popAnimRig->UpdateAnim(PVZ_T(), PVZ_Dt());
	MarkDirty();
}

void LawnDialog::SetPlant(const PlantTypePtr i_plantType)
{
	SAFE_DELETE(m_popAnimRig);
	if (m_plantType)
		gLawnApp->DeleteGroup(m_plantType->PlantFramework);
	PlantAnimRig* rig = CreateStandalonePlantAnimRig(i_plantType, true);
	m_popAnimRig = rig;
	m_plantType = i_plantType;
	rig->PlayPreviewAnim();
	CalcSize(0, ScaleNum(0));
}

void LawnDialog::Resize(int i_x, int i_y, int i_width, int i_height)
{
	Dialog::Resize(i_x, i_y, i_width, i_height);
	int buttonHeight = 0;
	if (m_lawnYesButton)
	{
		buttonHeight = m_lawnYesButton->mButtonImage->GetCelHeight();
		m_lawnYesButton->mButtonImage->GetCelWidth();
	}
	int buttonAreaX = mContentInsets.mLeft + mBackgroundInsets.mLeft + ScaleNum(26);
	int buttonAreaY = ScaleNum(-10) + mHeight - mContentInsets.mBottom - mBackgroundInsets.mBottom - buttonHeight;
	int buttonAreaWidth = mWidth - mContentInsets.mLeft - mBackgroundInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mRight - ScaleNum(52);
	int buttonGap = ScaleNum(5);
	if (m_tallBottom)
		buttonAreaY += 5;
	if (m_lawnYesButton && m_lawnNoButton)
	{
		int buttonWidth = (buttonAreaWidth - buttonGap) / 2;
		m_lawnYesButton->Resize(buttonAreaX, buttonAreaY, buttonWidth, buttonHeight);
		m_lawnNoButton->Resize(buttonAreaX + buttonAreaWidth - buttonWidth + ScaleNum(5), buttonAreaY, buttonWidth, buttonHeight);
	}
	else if (m_lawnYesButton)
	{
		m_lawnYesButton->Resize(buttonAreaX, buttonAreaY, buttonAreaWidth, buttonHeight);
	}
}

int MakeMultiple(int i_value, int i_multiple)
{
	if (i_value <= 0)
		return 0;
	if (i_multiple > 0)
	{
		int remainder = i_value % i_multiple;
		if (remainder != 0)
			i_value = i_value + i_multiple - remainder;
	}
	return i_value;
}

void LawnDialog::CalcSizeWithFont(int i_extraX, int i_extraY, bool i_padDialogWidth)
{
	int width = mContentInsets.mLeft + mContentInsets.mRight + mBackgroundInsets.mLeft + mBackgroundInsets.mRight + ScaleNum(i_extraX);
	if (mDialogHeader.length() > 0)
		width += mHeaderFont->StringWidth(mDialogHeader);
	int dialogWidth = ((Image*)IMAGE_DIALOG_TOPLEFT)->mWidth + ((Image*)IMAGE_DIALOG_TOPRIGHT)->mWidth + ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth;
	if (width >= dialogWidth)
		dialogWidth += MakeMultiple(width - dialogWidth, ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth);

	int height = ScaleNum(45) + mContentInsets.mTop + mContentInsets.mBottom + mBackgroundInsets.mTop + mBackgroundInsets.mBottom + ScaleNum(i_extraY);
	if (mDialogHeader.length() > 0)
	{
		height += mHeaderFont->GetHeight() - mHeaderFont->GetAscentPadding();
		height += mSpaceAfterHeader;
	}
	if (mDialogLines.length() > 0)
	{
		if (i_padDialogWidth)
			dialogWidth += ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth;
		if (mLinesFont)
		{
			Graphics g;
			g.SetFont(mLinesFont);
			height += GetWordWrappedHeight(&g, dialogWidth - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - ScaleNum(4), mDialogLines, mLinesFont->GetLineSpacing() + mLineSpacingOffset);
		}
		height += ScaleNum(30);
	}
	height += mButtonHeight;
	height += ScaleNum(8);

	float scale = gLawnApp->GetScaleAmount();
	int dialogHeight = (float)((Image*)IMAGE_DIALOG_TOPLEFT)->mHeight + ((Image*)IMAGE_DIALOG_BOTTOMLEFT)->mHeight + scale * 45.0f;
	if (m_tallBottom)
	{
		scale = gLawnApp->GetScaleAmount();
		float topHeight = ((Image*)IMAGE_DIALOG_TOPLEFT)->mHeight;
		dialogHeight = ((Image*)IMAGE_DIALOG_BIGBOTTOMLEFT)->mHeight + topHeight + scale * 45.0f;
	}
	if (height >= dialogHeight)
		dialogHeight += MakeMultiple(height - dialogHeight, ((Image*)IMAGE_DIALOG_CENTERLEFT)->mHeight);
	Resize(mX, mY, dialogWidth, dialogHeight);
}

void LawnDialog::CalcSizeWithPrimeFont(int i_extraX, int i_extraY, bool i_padDialogWidth)
{
	int width = mContentInsets.mLeft + mContentInsets.mRight + mBackgroundInsets.mLeft + mBackgroundInsets.mRight + ScaleNum(i_extraX);
	if (mDialogHeader.length() > 0)
		width += mHeaderPrimeFont->StringWidth(mDialogHeader);
	int dialogWidth = ((Image*)IMAGE_DIALOG_TOPLEFT)->mWidth + ((Image*)IMAGE_DIALOG_TOPRIGHT)->mWidth + ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth;
	if (width >= dialogWidth)
		dialogWidth += MakeMultiple(width - dialogWidth, ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth);

	int height = ScaleNum(45) + mContentInsets.mTop + mContentInsets.mBottom + mBackgroundInsets.mTop + mBackgroundInsets.mBottom + ScaleNum(i_extraY);
	if (mDialogHeader.length() > 0)
	{
		float fontHeight = mHeaderPrimeFont->GetHeight();
		float ascentPadding = mHeaderPrimeFont->GetAscentPadding();
		float fheight = height;
		height = fontHeight + fheight - ascentPadding;
		height += mSpaceAfterHeader;
	}
	if (mDialogLines.length() > 0)
	{
		if (i_padDialogWidth)
			dialogWidth += ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth;
		if (mLinesPrimeFont)
		{
			int textWidth = dialogWidth - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - ScaleNum(4);
			int linesWidth, linesHeight;
			mLinesPrimeFont->SizeString_Paragraph(mDialogLines, linesWidth, linesHeight, textWidth);
			height += linesHeight;
		}
		height += ScaleNum(30);
	}
	height += mButtonHeight;
	height += ScaleNum(8);

	float scale = gLawnApp->GetScaleAmount();
	int dialogHeight = (float)((Image*)IMAGE_DIALOG_TOPLEFT)->mHeight + ((Image*)IMAGE_DIALOG_BOTTOMLEFT)->mHeight + scale * 45.0f;
	if (m_tallBottom)
	{
		scale = gLawnApp->GetScaleAmount();
		float topHeight = ((Image*)IMAGE_DIALOG_TOPLEFT)->mHeight;
		dialogHeight = ((Image*)IMAGE_DIALOG_BIGBOTTOMLEFT)->mHeight + topHeight + scale * 45.0f;
	}
	if (height >= dialogHeight)
		dialogHeight += MakeMultiple(height - dialogHeight, ((Image*)IMAGE_DIALOG_CENTERLEFT)->mHeight);
	Resize(mX, mY, dialogWidth, dialogHeight);
}

void LawnDialog::SetButtonImage(ImagePtr i_image, int i_buttonMode, const SexyString& i_dialogFooter)
{
	SetButtonComponentImage(i_image);
	SetColors(gDialogColors, Dialog::NUM_COLORS);
	SetColor(Dialog::COLOR_HEADER, Color(224, 187, 98));
	SetColor(Dialog::COLOR_LINES, Color(224, 187, 98));
	delete m_lawnYesButton;
	delete m_lawnNoButton;
	if (i_buttonMode == Dialog::BUTTONS_YES_NO)
	{
		m_lawnYesButton = MakeStretchableNewLawnButton(Dialog::ID_YES, this, _S("[BUTTON_YES]"), FONT_GENERAL_BUTTON, i_image, NULL, NULL, i_image->GetWidth() / 3, i_image->GetWidth() / 3);
		m_lawnYesButton->mTextOffsetY = ScaleNum(-3);
		m_lawnNoButton = MakeStretchableNewLawnButton(Dialog::ID_NO, this, _S("[BUTTON_NO]"), FONT_GENERAL_BUTTON, i_image, NULL, NULL, i_image->GetWidth() / 3, i_image->GetWidth() / 3);
		m_lawnNoButton->mTextOffsetY = ScaleNum(-3);
	}
	else if (i_buttonMode == Dialog::BUTTONS_OK_CANCEL)
	{
		m_lawnYesButton = MakeStretchableNewLawnButton(Dialog::ID_OK, this, _S("[BUTTON_OK]"), FONT_GENERAL_BUTTON, i_image, NULL, NULL, i_image->GetWidth() / 3, i_image->GetWidth() / 3);
		m_lawnYesButton->mTextOffsetY = ScaleNum(-3);
		m_lawnNoButton = MakeStretchableNewLawnButton(Dialog::ID_CANCEL, this, _S("[BUTTON_CANCEL]"), FONT_GENERAL_BUTTON, i_image, NULL, NULL, i_image->GetWidth() / 3, i_image->GetWidth() / 3);
		m_lawnNoButton->mTextOffsetY = ScaleNum(-3);
	}
	else if (i_buttonMode == Dialog::BUTTONS_FOOTER)
	{
		m_lawnYesButton = MakeStretchableNewLawnButton(Dialog::ID_FOOTER, this, i_dialogFooter, FONT_GENERAL_BUTTON, i_image, NULL, NULL, i_image->GetWidth() / 3, i_image->GetWidth() / 3);
		m_lawnYesButton->mTextOffsetY = ScaleNum(-3);
		m_lawnNoButton = NULL;
	}
	else
	{
		m_lawnYesButton = NULL;
		m_lawnNoButton = NULL;
	}
	CalcSize(0, 0);
}

void LawnDialog::Draw(Graphics* g)
{
	if (!m_drawStandardBack)
		return;

	Image* bottomLeft = IMAGE_DIALOG_BOTTOMLEFT;
	Image* bottomMiddle = IMAGE_DIALOG_BOTTOMMIDDLE;
	Image* bottomRight = IMAGE_DIALOG_BOTTOMRIGHT;
	if (m_tallBottom)
	{
		bottomLeft = IMAGE_DIALOG_BIGBOTTOMLEFT;
		bottomMiddle = IMAGE_DIALOG_BIGBOTTOMMIDDLE;
		bottomRight = IMAGE_DIALOG_BIGBOTTOMRIGHT;
	}

	int topCount = (mWidth - ((Image*)IMAGE_DIALOG_TOPLEFT)->mWidth - ((Image*)IMAGE_DIALOG_TOPRIGHT)->mWidth) / ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth;
	int bottomCount = (mWidth - bottomLeft->mWidth - bottomRight->mWidth) / bottomMiddle->mWidth;
	int centerCountX = (mWidth - ((Image*)IMAGE_DIALOG_CENTERLEFT)->mWidth - ((Image*)IMAGE_DIALOG_CENTERRIGHT)->mWidth) / ((Image*)IMAGE_DIALOG_CENTERMIDDLE)->mWidth;
	int centerCount = (mHeight - ScaleNum(45) - ((Image*)IMAGE_DIALOG_TOPLEFT)->mHeight - bottomLeft->mHeight) / ((Image*)IMAGE_DIALOG_CENTERMIDDLE)->mHeight;

	int y = ScaleNum(45);
	g->DrawImage(IMAGE_DIALOG_TOPLEFT, 0, y);
	int x = ((Image*)IMAGE_DIALOG_TOPLEFT)->mWidth;
	for (int i = 0; i < topCount; i++)
	{
		g->DrawImage(IMAGE_DIALOG_TOPMIDDLE, x, y);
		x += ((Image*)IMAGE_DIALOG_TOPMIDDLE)->mWidth;
	}
	g->DrawImage(IMAGE_DIALOG_TOPRIGHT, x, y);
	y += ((Image*)IMAGE_DIALOG_TOPRIGHT)->mHeight;

	if (centerCount > 0)
	{
		g->DrawImage(IMAGE_DIALOG_CENTERLEFT, 0, y);
		x = ((Image*)IMAGE_DIALOG_CENTERLEFT)->mWidth;
		for (int row = 0; row < centerCount; row++)
		{
			x = ((Image*)IMAGE_DIALOG_CENTERLEFT)->mWidth;
			for (int i = 0; i < centerCountX; i++)
			{
				g->DrawImage(IMAGE_DIALOG_CENTERMIDDLE, x, y);
				x += ((Image*)IMAGE_DIALOG_CENTERMIDDLE)->mWidth;
			}
			y += ((Image*)IMAGE_DIALOG_CENTERMIDDLE)->mHeight;
		}
		y = ScaleNum(45) + ((Image*)IMAGE_DIALOG_TOPLEFT)->mHeight;
		g->DrawImage(IMAGE_DIALOG_CENTERRIGHT, x, y);
	}

	y += centerCount * ((Image*)IMAGE_DIALOG_CENTERMIDDLE)->mHeight;
	g->DrawImage(bottomLeft, 0, y);
	x = bottomLeft->mWidth;
	for (int i = 0; i < bottomCount; i++)
	{
		g->DrawImage(bottomMiddle, x, y);
		x += bottomMiddle->mWidth;
	}
	g->DrawImage(bottomRight, x, y);

	int curY = ScaleNum(45) + mContentInsets.mTop + mBackgroundInsets.mTop;
	if (mDialogHeader.length() > 0)
	{
		if (mHeaderFont)
		{
			curY += mHeaderFont->GetAscent() - mHeaderFont->GetAscentPadding();
			Widget::WriteCenteredLine(g, mColors[0], curY, mDialogHeader);
			curY += mHeaderFont->GetHeight() - mHeaderFont->GetAscent();
		}
		else if (mHeaderPrimeFont)
		{
			float ascent = mHeaderPrimeFont->GetAscent();
			float ascentPadding = mHeaderPrimeFont->GetAscentPadding();
			float fy = curY;
			curY = ascent + fy - ascentPadding;
			Widget::WriteCenteredLine(g, mHeaderPrimeFont, mColors[0], curY, mDialogHeader);
			float height = mHeaderPrimeFont->GetHeight();
			float ascent2 = mHeaderPrimeFont->GetAscent();
			curY = height - ascent2 + curY;
		}
		curY += mSpaceAfterHeader;
	}

	int textWidth = mWidth - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - ScaleNum(4);
	Rect rect(mContentInsets.mLeft + mBackgroundInsets.mLeft + ScaleNum(2), curY, textWidth, PrimeTypeface::ParagraphHeightUnlimited);
	if (m_verticalCenterText)
	{
		int textHeight;
		if (mLinesFont)
			textHeight = GetWordWrappedHeight(g, textWidth, mDialogLines, mLinesFont->GetLineSpacing() + mLineSpacingOffset);
		else if (mLinesPrimeFont)
			textHeight = GetWordWrappedHeight(g, mLinesPrimeFont, textWidth, mDialogLines, mLinesPrimeFont->GetLineSpacing() + mLineSpacingOffset);
		else
			textHeight = 0;
		float scale = gLawnApp->GetScaleAmount();
		int space = mHeight - mContentInsets.mBottom - mBackgroundInsets.mBottom - curY - mButtonHeight - 55.0f * scale;
		if (m_tallBottom)
			space = space - 36.0f * scale;
		rect.mY += (space - textHeight) / 2;
	}
	if (mLinesFont)
		curY += WriteWordWrapped(g, mColors[1], rect, mDialogLines, mLinesFont->GetLineSpacing() + mLineSpacingOffset, mTextAlign);
	else if (mLinesPrimeFont)
		curY += WriteWordWrapped(g, mLinesPrimeFont, mColors[1], rect, mDialogLines, mLinesPrimeFont->GetLineSpacing() + mLineSpacingOffset, mTextAlign);

	if (m_popAnimRig)
	{
		if (m_plantType.IsValid())
		{
			const SexyVector2& artCenter = m_plantType->Properties->ArtCenter;
			float artX = ScaleNum(artCenter.x);
			int animY = ScaleNum(186);
			float artY = ScaleNum(artCenter.y);
			g->Translate(mWidth / 2 - artX, animY + curY - artY);
		}
		else
		{
			Point center = m_popAnimRig->GetPAM()->mAnimRect.GetCenter() * m_popAnimRig->GetDrawScale();
			g->Translate(mWidth / 2 - center.mX, ScaleNum(186) + curY - center.mY);
		}
		m_popAnimRig->Draw(g);
	}
	if (m_staticImage)
	{
		g->Translate(mWidth / 2 - m_staticImage->mWidth / 2, ScaleNum(186) + curY - m_staticImage->mWidth / 2);
		g->DrawImage(m_staticImage, 0, 0);
	}
}
