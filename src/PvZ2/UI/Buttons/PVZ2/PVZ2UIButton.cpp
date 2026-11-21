//
//  PVZ2UIButton.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "PVZ2UIButton.h"
#include "TodStringFile.h"
#include "PrimeText_PotentialTypeface.h"

/////////////// Accessors ///////////////

void PVZ2UIButton::SetFont(PrimeTypeface* theFont)
{
	ButtonWidget::SetFont(theFont);
}

void PVZ2UIButton::SetContentsRect(const Sexy::Rect& i_rect)
{
	m_contentsRect = i_rect;
}

void PVZ2UIButton::SetTextJustification(const PVZButtonJustification i_textJustification)
{
	m_textJustification = i_textJustification;
}

void PVZ2UIButton::SetOnlyDrawParts()
{
	m_buttonType = PVZ2UIBUTTON_DEFAULT;
}

void PVZ2UIButton::SetButtonWithIcons()
{
	m_iconJustification = BUTTON_JUST_LEFT;
	m_textJustification = BUTTON_JUST_RIGHT;
}

void PVZ2UIButton::SetInvisible(bool i_invisible)
{
	m_invisible = i_invisible;
}

void PVZ2UIButton::SetDialogStates(const PVZ2UIImage& i_normalImage, const PVZ2UIImage& i_downImage)
{
	m_normalImage = i_normalImage;
	m_selectedImage = i_downImage;
	m_buttonType = PVZ2UIBUTTON_DIALOG;
}

void PVZ2UIButton::SetLabelText(const SexyString& i_text)
{
	mLabel = i_text;
	if (m_textLabel != NULL)
		m_textLabel->SetText(i_text);
}

void PVZ2UIButton::SetDelayDisabled(float delay_time)
{
	SetDisabled(true);
	if (delay_time > 0.0001f)
		m_delayTime = PVZ_T() + delay_time;
}

void PVZ2UIButton::SetNormalStates(const PVZ2UIImage& i_backgroundImage, const PVZ2UIImage& i_iconImage)
{
	m_normalImage = i_backgroundImage;
	m_iconImage = i_iconImage;
	m_iconJustification = BUTTON_JUST_CENTER;
	m_buttonType = PVZ2UIBUTTON_NORMAL;
}

void PVZ2UIButton::SetRadioButtonSelected()
{
	m_radioButtonSelected = true;
	for (int i = 0; i < m_siblingRadioButtons.size(); i++)
		m_siblingRadioButtons[i]->m_radioButtonSelected = false;
}

/////////////// Logic ///////////////

__attribute__((noclone, noinline)) static int UIScaleNum(int i_num)
{
	return ((ScaledApp*)gSexyApp)->UIScaleNum(i_num);
}

void PVZ2UIButton::MouseDown(int i_x, int i_y, int i_btnNum, int i_clickCount)
{
}

void PVZ2UIButton::ClearButton()
{
	m_parts.clear();
}

void PVZ2UIButton::drawLabel(Graphics* i_g)
{
	if (m_textLabel != NULL)
		m_textLabel->Draw(i_g);
}

DrawStringJustification PVZ2UIButton::getDrawStringJust(const PVZButtonJustification i_justification) const
{
	switch (i_justification)
	{
	case BUTTON_JUST_LEFT:
		return DS_ALIGN_LEFT_VERTICAL_MIDDLE;
	case BUTTON_JUST_RIGHT:
		return DS_ALIGN_RIGHT_VERTICAL_MIDDLE;
	case BUTTON_JUST_CENTER:
		return DS_ALIGN_CENTER_VERTICAL_MIDDLE;
	}
}

void PVZ2UIButton::Resize(const Sexy::Rect& theRect)
{
	Resize(theRect.mX, theRect.mY, theRect.mWidth, theRect.mHeight);
}

void PVZ2UIButton::Resize(int theX, int theY, int theWidth, int theHeight)
{
	ButtonWidget::Resize(theX, theY, theWidth, theHeight);
	if (m_bLayout)
		LayoutPart(m_layoutJustification);
}

void PVZ2UIButton::updateFontColor()
{
	if (m_textLabel != NULL)
		m_textLabel->SetColor(0, getFontColor());
}

void PVZ2UIButton::TouchBegan(const Sexy::Touch& i_touch)
{
	if (!m_radioButtonSelected && m_touchIdent == Sexy::InvalidTouchID)
	{
		m_touchIdent = i_touch.ident;
		m_touchIsOver = true;
		if (mButtonListener != NULL)
			mButtonListener->ButtonPress(mId, 1);
	}
}

void PVZ2UIButton::TouchesCanceled()
{
	m_touchIdent = Sexy::InvalidTouchID;
	m_touchIsOver = false;
	if (mButtonListener != NULL)
		mButtonListener->ButtonMouseLeave(mId);
}

void PVZ2UIButton::MouseUp(int theX, int theY, int theClickCount)
{
	ButtonWidget::MouseUp(theX, theY, theClickCount);
	m_touchIdent = Sexy::InvalidTouchID;
	m_touchIsOver = false;
}

void PVZ2UIButton::SetRadioStates(const PVZ2UIImage& i_unselectedImage, const PVZ2UIImage& i_selectedImage, const bool i_selected)
{
	m_normalImage = i_unselectedImage;
	m_selectedImage = i_selectedImage;
	m_radioButtonSelected = i_selected;
	m_buttonType = PVZ2UIBUTTON_RADIO;
	m_bClipDisabled = true;
}

void PVZ2UIButton::Update()
{
	ButtonWidget::Update();
	if (m_delayTime > 0.0f)
	{
		if (m_delayTime < PVZ_T())
		{
			SetDisabled(false);
			m_delayTime = -1.0f;
		}
	}
}

void PVZ2UIButton::TouchEnded(const Sexy::Touch& i_touch)
{
	if (!m_radioButtonSelected && m_touchIdent == i_touch.ident)
	{
		bool wasOver = m_touchIsOver;
		m_touchIdent = Sexy::InvalidTouchID;
		m_touchIsOver = false;
		if (wasOver)
		{
			if (mIsOver && m_buttonType == PVZ2UIBUTTON_RADIO)
				SetRadioButtonSelected();
			if (mButtonListener != NULL)
				mButtonListener->ButtonDepress(mId);
		}
	}
}

void PVZ2UIButton::TouchMoved(const Sexy::Touch& i_touch)
{
	if (m_touchIdent == i_touch.ident)
		m_touchIsOver = Sexy::Rect(0, 0, mWidth, mHeight).Contains(i_touch.location.mX, i_touch.location.mY);
}

void PVZ2UIButton::LinkRadioButtons(std::vector<PVZ2UIButton*> i_buttons)
{
	for (size_t i = 0; i < i_buttons.size(); i++)
	{
		if (i_buttons[i] != this)
			m_siblingRadioButtons.push_back(i_buttons[i]);
	}
}

void PVZ2UIButton::AddImage(const PVZ2UIImage& i_image, const PVZButtonJustification i_justification)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_IMAGE;
	part.m_image = i_image;
	m_parts.push_back(part);
	LayoutPart(i_justification);
}

void PVZ2UIButton::AddImage(const PVZ2UIImage& i_image, const Sexy::Rect& i_drawRect)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_IMAGE;
	part.m_image = i_image;
	part.m_justification = BUTTON_JUST_CENTER;
	part.m_rect = i_drawRect;
	m_parts.push_back(part);
}

void PVZ2UIButton::AddImageScale(const PVZ2UIImage& i_image, const PVZButtonJustification i_justification, float fScale)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_IMAGE;
	part.m_image = i_image;
	part.mfScale = fScale;
	m_parts.push_back(part);
	LayoutPart(i_justification);
}

Sexy::Rect PVZ2UIButton::getContentsRect()
{
	if (m_contentsRect.mWidth < 0 || m_contentsRect.mHeight < 0)
		return Sexy::Rect(UIScaleNum(5), UIScaleNum(0), mWidth - UIScaleNum(10), mHeight);

	return m_contentsRect;
}

int PVZ2UIButton::getPositionFromJustification(const PVZButtonJustification i_justification, const int i_xOff, const int i_width)
{
	Sexy::Rect contentsRect = getContentsRect();
	int x = 0;
	if (i_justification == BUTTON_JUST_LEFT)
		x = contentsRect.mX + i_xOff;
	else if (i_justification == BUTTON_JUST_CENTER)
		x = contentsRect.mX + (i_xOff + contentsRect.mWidth - i_width) / 2;
	else if (i_justification == BUTTON_JUST_RIGHT)
		x = contentsRect.mX + contentsRect.mWidth - i_width + i_xOff;
	return x;
}

PrimeTypeface* PVZ2UIButton::GetTextFontDrawn()
{
	if (mLabel.size() == 0)
		return mPrimeFont;

	Sexy::Rect contentsRect = getContentsRect();
	if (mPrimeFont == NULL)
		return NULL;

	int resultHeight;
	return mPrimeFont->FitString_Paragraph(mLabel, contentsRect.mWidth, contentsRect.mHeight, resultHeight);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, const PVZButtonJustification i_justification)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_STRING;
	part.m_string = TodStringTranslate(i_textString);
	part.m_justification = i_justification;
	m_parts.push_back(part);
	LayoutPart(i_justification);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, const PVZButtonJustification i_justification)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_STRING;
	part.m_string = TodStringTranslate(i_textString);
	part.m_justification = i_justification;
	part.m_rect = i_drawRect;
	m_parts.push_back(part);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, Font* i_font, const PVZButtonJustification i_justification)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_STRING;
	part.m_string = TodStringTranslate(i_textString);
	part.m_justification = i_justification;
	part.mFont = i_font;
	m_parts.push_back(part);
	LayoutPart(i_justification);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, PrimeTypeface* i_font, const PVZButtonJustification i_justification)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_STRING;
	part.m_string = TodStringTranslate(i_textString);
	part.m_justification = i_justification;
	part.mPrimeFont = i_font;
	m_parts.push_back(part);
	LayoutPart(i_justification);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, class PrimeText_PotentialTypeface* i_font, const PVZButtonJustification i_justification)
{
	AddText(i_textString, i_font->Typeface(), i_justification);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, Font* i_font, const PVZButtonJustification i_justification)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_STRING;
	part.m_string = TodStringTranslate(i_textString);
	part.m_justification = i_justification;
	part.m_rect = i_drawRect;
	part.mFont = i_font;
	m_parts.push_back(part);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, PrimeTypeface* i_font, const PVZButtonJustification i_justification)
{
	PVZ2UIButtonPart part;
	part.m_type = PVZ2UIButtonPart::PVZ2UIBUTTONPARTTYPE_STRING;
	part.m_string = TodStringTranslate(i_textString);
	part.m_justification = i_justification;
	part.m_rect = i_drawRect;
	part.mPrimeFont = i_font;
	m_parts.push_back(part);
}

void PVZ2UIButton::AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, class PrimeText_PotentialTypeface* i_font, const PVZButtonJustification i_justification)
{
	AddText(i_textString, i_drawRect, i_font->Typeface(), i_justification);
}

void PVZ2UIButton::UnlinkRadioButton(PVZ2UIButton* pBtnUnlink)
{
	std::vector<PVZ2UIButton*>::iterator it = m_siblingRadioButtons.begin();
	while (it != m_siblingRadioButtons.end())
	{
		if (*it == pBtnUnlink)
			it = m_siblingRadioButtons.erase(it);
		else
			++it;
	}
}
