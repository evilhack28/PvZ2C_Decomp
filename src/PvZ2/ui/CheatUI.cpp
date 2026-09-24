//
//  CheatUI.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-24.
//

#include "SexyAppFramework/Common.h"

#include "CheatUI.h"
#include "LawnApp.h"
#include "ScaledApp.h"
#include "UIEditor/StringHelper.h"
#include "ResourceHelpers.h"
#include "UIHelper.h"
#include "PrimeText_Game.h"
#include "NetworkItemMgr.h"
#include "PVZ2UIDialog.h"

static float CheatUIConstant(float i_value)
{
	return i_value;
}

static float s_panelWidth = CheatUIConstant(200.f);
static float s_buttonSize = CheatUIConstant(32.f);
static float s_tabHeight = CheatUIConstant(64.f);
static float s_lineHeight = CheatUIConstant(60.f);
static float s_lineWidth = CheatUIConstant(200.f);
static CachedResourcePtr<Sexy::Image> s_actionImage("IMAGE_UI_CHEATMENU_ACTION");
static CachedResourcePtr<Sexy::Image> s_checkboxOffImage("IMAGE_UI_CHEATMENU_CHECKBOX_OFF");
static CachedResourcePtr<Sexy::Image> s_checkboxOnImage("IMAGE_UI_CHEATMENU_CHECKBOX_ON");
static CachedResourcePtr<Sexy::Image> s_panelLaneImage("IMAGE_UI_CHEATMENU_FOLDER_LANE");
static CachedResourcePtr<Sexy::Image> s_folderCollapsedImage("IMAGE_UI_CHEATMENU_FOLDER_COLLAPSED");
static CachedResourcePtr<Sexy::Image> s_panelFolderImage("IMAGE_UI_CHEATMENU_FOLDER_EXPANDED");

/////////////// CheatUILine ///////////////

RT_CLASS_IMPLEMENT(CheatUILine);

void CheatUILine::Tap(const Point& i_location)
{
	onTap(i_location);
}

Cheat* CheatUILine::GetCheat() const
{
	return m_cheat;
}

CheatUILine* CheatUILine::SetValidContexts(CheatContext i_context)
{
	m_contexts = i_context;
	return this;
}

CheatContext CheatUILine::GetValidContexts() const
{
	return m_contexts;
}

float CheatUILine::GetHeight()
{
	return gCheatUI->GetDefaultLineHeight();
}

Color CheatUILine::getLabelColor() const
{
	return Color(Color::White);
}

std::string CheatUILine::GetLabel()
{
	if (m_labelCallback)
		m_labelCallback(m_label);

	return m_label;
}

void CheatUILine::Draw(Graphics* i_g)
{
	float transY = i_g->mTransY;
	if (transY > (float)gLawnApp->mHeight)
		return;
	if (GetHeight() + transY < 0.0f)
		return;
	onDraw(i_g);
}

void CheatUILine::onDraw(Graphics* i_g)
{
	GraphicsAutoState state(i_g);
	float inset = S(4.f);
	i_g->Translate((int)inset, (int)inset);
	i_g->Translate((int)S(s_tabHeight + 4.0f), 0);
	int width = S(200);
	float lineHeight = gCheatUI->GetDefaultLineHeight();
	float pad = S(4.f);
	int height = (int)(lineHeight - pad * 2.0f);
	Rect rect(0, 0, width, height);
	Color color = getLabelColor();
	SexyString text = UTF8StringToWString(m_label);
	if (m_cheat && m_cheat->GetKeyboardShortcut())
		text = StrFormat(L"%ls (%c)", text.c_str(), (int)m_cheat->GetKeyboardShortcut());

	PrimeText_PotentialTypeface* font = PrimeText_Game::Typeface_CafeteriaBlack_26;
	PrimeTypeface* typeface = font ? font->Typeface() : NULL;
	WriteWordInRect(i_g, text, rect, typeface, color, (DrawStringJustification)3, false);
}

SexyVector2 CheatUILine::getDimensions()
{
	float w = S(s_lineWidth);
	float h = GetHeight();
	return SexyVector2(w, h);
}

/////////////// CheatUILineSeparator ///////////////

RT_CLASS_IMPLEMENT(CheatUILineSeparator);

float CheatUILineSeparator::GetHeight()
{
	return SuperClass::GetHeight() * 0.2f;
}

void CheatUILineSeparator::onDraw(Graphics* i_g)
{
	GraphicsAutoState state(i_g);
	SexyVector2 dim = getDimensions();
	float thickness = dim.y * 0.1f;
	i_g->Translate((int)(dim.x * 0.01f), (int)((dim.y - thickness) * 0.5f));
	i_g->SetColor(Color(200, 200, 200, 255));
	i_g->FillRect(0, 0, (int)(dim.x * 0.98f), (int)thickness);
}

/////////////// CheatUILineToggle ///////////////

RT_CLASS_IMPLEMENT(CheatUILineToggle);

void CheatUILineToggle::onTap(const Point& i_location)
{
	GetCheat()->CastChecked<CheatToggle>()->Toggle();
}

void CheatUILineToggle::onDraw(Graphics* i_g)
{
	{
	GraphicsAutoState state(i_g);
	float inset = S(4.f);
	i_g->Translate((int)inset, (int)inset);
	float lineHeight = gCheatUI->GetDefaultLineHeight();
	float size = S(s_tabHeight);
	Rect dest(0, (int)((lineHeight - size) * 0.5f), (int)size, (int)size);
	i_g->SetColor(Color(Color::White));
	CachedResourcePtr<Sexy::Image>* checkbox;
	if (GetCheat()->CastChecked<CheatToggle>()->GetValue())
		checkbox = &s_checkboxOnImage;
	else
		checkbox = &s_checkboxOffImage;
	Image* image = *checkbox;
	Rect src(0, 0, ((Image*)s_checkboxOffImage)->mWidth, ((Image*)s_checkboxOffImage)->mHeight);
	i_g->DrawImage(image, dest, src);
	}
	SuperClass::onDraw(i_g);
}

/////////////// CheatUILineCommand ///////////////

RT_CLASS_IMPLEMENT(CheatUILineCommand);

Color CheatUILineCommand::getLabelColor() const
{
	Color baseColor = SuperClass::getLabelColor();
	static const Color s_flashColor(255, 173, 0, 255);

	float elapsed = PVZ_RealT() - m_lastTapped;
	if (elapsed > 0.2f)
		return baseColor;

	return ColorLerp(s_flashColor, baseColor, elapsed * 5.0f);
}

void CheatUILineCommand::onTap(const Point& i_location)
{
	CrashTracking::Log(StrFormat("PVZ_T: %f - [CHEAT] CheatCommand %s Activated.", PVZ_T(), GetCheat()->GetName().c_str()));
	GetCheat()->CastChecked<CheatCommand>()->GetCommand()();
	m_lastTapped = PVZ_RealT();
}


void CheatUILineCommand::onDraw(Graphics* i_g)
{
	{
		GraphicsAutoState state(i_g);
		float inset = S(4.f);
		i_g->Translate((int)inset, (int)inset);
		float lineHeight = gCheatUI->GetDefaultLineHeight();
		float size = S(s_tabHeight);
		Rect dest(0, (int)((lineHeight - size) * 0.5f), (int)size, (int)size);
		i_g->SetColor(Color(Color::White));
		Image* image = s_actionImage;
		Rect src(0, 0, ((Image*)s_actionImage)->mWidth, ((Image*)s_actionImage)->mHeight);
		i_g->DrawImage(image, dest, src);
	}
	SuperClass::onDraw(i_g);
}

/////////////// CheatAdjusterWidget ///////////////

RT_CLASS_IMPLEMENT(CheatAdjusterWidget);

CheatAdjusterWidget::~CheatAdjusterWidget()
{
	if (m_pEditWidget)
		m_pEditWidget = NULL;

	if (m_pCloseButton)
		m_pCloseButton = NULL;
}

float CheatAdjusterWidget::getValue()
{
	return StringHelper::ToFloat(Sexy::ToString(m_pEditWidget->mString));
}

Rect CheatAdjusterWidget::getNameDrawRect()
{
	return Rect(0, 0, mWidth / 3, mHeight);
}

void CheatAdjusterWidget::onCreate(const std::string& i_name, float i_value, Sexy::EditListener* i_pEditListener, Sexy::ButtonListener* i_pButtonListener)
{
	mWidth = UI_S(300);
	mHeight = UI_S(40);
	m_name = i_name;

	m_pEditWidget = new EditWidget(0, i_pEditListener);
	m_pEditWidget->SetText(Sexy::ToSexyString(StrFormat("%f", (double)i_value)), true);
	m_pEditWidget->Resize(mWidth / 3, UI_S(0), mWidth - mWidth / 3 - mHeight, mHeight);
	m_pEditWidget->SetFont(PrimeText_Game::Typeface_FZCuYuan_24->Typeface(), NULL);
	AddWidget(m_pEditWidget);

	m_pCloseButton = new PVZ2UIButton(2, i_pButtonListener, L"", Color(Color::White));
	m_pCloseButton->Resize(mWidth - mHeight, 0, mHeight, mHeight);
	Image* normalImage = StringHelper::ToImage(std::string("IMAGE_UI_GENERIC_RED_CROSS"), true);
	Image* downImage = StringHelper::ToImage(std::string("IMAGE_UI_GENERIC_RED_CROSS"), true);
	m_pCloseButton->SetDialogStates(PVZ2UIImage(normalImage, (PVZ2UIImageType)2), PVZ2UIImage(downImage, (PVZ2UIImageType)2));
	AddWidget(m_pCloseButton);
}

void CheatAdjusterWidget::Draw(Graphics* g)
{
	GraphicsAutoState state(g);
	g->SetDrawMode(0);
	g->SetColorizeImages(true);
	g->SetColor(Color(70, 70, 70, 240));
	g->FillRect(GetClipRect());
	SexyString name = Sexy::ToSexyString(m_name);
	Rect nameRect = getNameDrawRect();
	PrimeTypeface* typeface = PrimeText_Game::Typeface_FZCuYuan_24->Typeface();
	WriteWordInRect(g, name, nameRect, typeface, Color(Color::Cyan), (DrawStringJustification)3, false);
}

void CheatAdjusterWidget::TouchBegan(const Sexy::Touch& i_touch)
{
	Point location(i_touch.location);
	if (getNameDrawRect().Contains(location))
	{
		m_moveStartPoint = location;
		m_isMoving = true;
	}
}

void CheatAdjusterWidget::TouchMoved(const Sexy::Touch& i_touch)
{
	if (m_isMoving)
	{
		Point delta = Point(i_touch.location - m_moveStartPoint);
		if (delta.mX != 0 || delta.mY != 0)
			Move(delta.mX + mX, delta.mY + mY);
	}
}

void CheatAdjusterWidget::TouchEnded(const Sexy::Touch& i_touch)
{
	m_moveStartPoint = Point(0, 0);
	m_isMoving = false;
}

/////////////// CheatUILineAdjuster ///////////////

RT_CLASS_IMPLEMENT(CheatUILineAdjuster);

Color CheatUILineAdjuster::getLabelColor() const
{
	Color baseColor = SuperClass::getLabelColor();
	static const Color s_flashColor(255, 173, 0, 255);

	float elapsed = PVZ_RealT() - m_lastTapped;
	if (elapsed > 0.2f)
		return baseColor;

	return ColorLerp(s_flashColor, baseColor, elapsed * 5.0f);
}

void CheatUILineAdjuster::onDraw(Graphics* i_g)
{
	{
		GraphicsAutoState state(i_g);
		float inset = S(4.f);
		i_g->Translate((int)inset, (int)inset);
		float lineHeight = gCheatUI->GetDefaultLineHeight();
		float size = S(s_tabHeight);
		Rect dest(0, (int)((lineHeight - size) * 0.5f), (int)size, (int)size);
		i_g->SetColor(Color(Color::White));
		Image* image = s_actionImage;
		Rect src(0, 0, ((Image*)s_actionImage)->mWidth, ((Image*)s_actionImage)->mHeight);
		i_g->DrawImage(image, dest, src);
	}
	SuperClass::onDraw(i_g);
}

void CheatUILineAdjuster::ButtonDepress(int theId)
{
	if (theId == 2 && m_pAdjusterWidget != NULL)
	{
		gLawnApp->mWidgetManager->RemoveWidget(m_pAdjusterWidget);
		gLawnApp->SafeDeleteWidget(m_pAdjusterWidget);
		m_pAdjusterWidget = NULL;
	}
}

void CheatUILineAdjuster::onTap(const Point& i_location)
{
	CheatVariable* variable = GetCheat()->Cast<CheatVariable>();
	if (m_pAdjusterWidget == NULL)
	{
		m_pAdjusterWidget = new CheatAdjusterWidget();
		m_pAdjusterWidget->onCreate(GetLabel(), variable->GetValue(), this, this);
	}

	m_pAdjusterWidget->Resize(UI_S(100), UI_S(50), m_pAdjusterWidget->mWidth, m_pAdjusterWidget->mHeight);
	gLawnApp->mWidgetManager->AddWidget(m_pAdjusterWidget);
}

void CheatUILineAdjuster::EditWidgetText(int theId, const SexyString& theString)
{
	GetCheat()->Cast<CheatVariable>()->SetValue2(StringHelper::ToFloat(Sexy::ToString(theString)));
}

/////////////// CheatUILineFolder ///////////////

RT_CLASS_IMPLEMENT(CheatUILineFolder);

CheatUILineFolder::~CheatUILineFolder()
{
	for (size_t i = 0; i < m_contained.size(); i++)
	{
		CheatUILineTracker& tracker = m_contained[i];
		if (tracker.Line)
			delete tracker.Line;
	}

	m_contained.clear();
}

void CheatUILineFolder::AddLine(CheatUILine* i_line)
{
	CheatUILineTracker tracker;
	tracker.Line = i_line;
	tracker.TargetHeight = tracker.Height = i_line->GetHeight();
	m_contained.push_back(tracker);
}

void CheatUILineFolder::onTap(const Point& i_location)
{
	int headerHeight = 0;
	if (GetLabel().length() != 0)
	{
		float lineHeight = gCheatUI->GetDefaultLineHeight();
		headerHeight = (int)lineHeight;
		if ((float)i_location.mY < lineHeight)
		{
			m_expanded = !m_expanded;
			return;
		}
	}

	float panelWidth = S(s_panelWidth);
	Rect rect(0, headerHeight, (int)panelWidth, 0);
	for (size_t i = 0; i < m_contained.size(); i++)
	{
		CheatUILineTracker& tracker = m_contained[i];
		if (TestFlag(tracker.Line->GetValidContexts(), gCheats->GetCurrentContext()))
		{
			Cheat* cheat = tracker.Line->GetCheat();
			if (cheat && !gCheats->IsCheatValidForCurrentContext(cheat))
				continue;

			float height = m_contained[i].Line->GetHeight();
			rect.mHeight = (int)height;
			int step = (int)height;
			if (rect.Contains(i_location))
			{
				Point local(i_location.mX, i_location.mY - rect.mY);
				m_contained[i].Line->Tap(local);
				step = rect.mHeight;
			}

			rect.mY += step;
		}
	}
}

void CheatUILineFolder::onDraw(Graphics* i_g)
{
	float headerHeight = 0.0f;
	GraphicsAutoState state(i_g);
	if (GetLabel().length() != 0)
	{
		GraphicsAutoState headerState(i_g);
		headerHeight = gCheatUI->GetDefaultLineHeight();
		float inset = S(4.f);
		i_g->Translate((int)inset, (int)inset);
		float lineHeight = gCheatUI->GetDefaultLineHeight();
		float size = S(s_tabHeight);
		Rect dest(0, (int)((lineHeight - size) * 0.5f), (int)size, (int)size);
		i_g->SetColor(Color(Color::White));
		CachedResourcePtr<Sexy::Image>* icon;
		if (m_expanded)
			icon = &s_panelFolderImage;
		else
			icon = &s_folderCollapsedImage;
		Image* image = *icon;
		Rect src(0, 0, ((Image*)s_folderCollapsedImage)->mWidth, ((Image*)s_folderCollapsedImage)->mHeight);
		i_g->DrawImage(image, dest, src);
		SuperClass::onDraw(i_g);
	}

	if (m_expanded)
	{
		if (m_contained.size() == 0)
			return;

		i_g->Translate(0, (int)headerHeight);
		if (m_useIndent)
		{
			float pad = S(4.f);
			float indent = S(s_tabHeight);
			i_g->Translate((int)(indent * 0.5f + pad * 2.0f), 0);
		}

		size_t i = 0;
		goto body;
	next:
		i++;
		if (m_contained.size() <= i)
			return;
	body:
		{
			CheatUILineTracker& tracker = m_contained[i];
			if (TestFlag(tracker.Line->GetValidContexts(), gCheats->GetCurrentContext()))
			{
				Cheat* cheat = tracker.Line->GetCheat();
				if (cheat && !gCheats->IsCheatValidForCurrentContext(cheat))
					goto next;

				tracker.Line->Draw(i_g);
				i_g->Translate(0, (int)tracker.Line->GetHeight());
			}
			goto next;
		}
	}
}

float CheatUILineFolder::GetHeight()
{
	float height = 0.0f;
	if (GetLabel().length() != 0)
	{
		height = gCheatUI->GetDefaultLineHeight();
		if (!m_expanded)
			return height;
	}

	for (size_t i = 0; i < m_contained.size(); i++)
	{
		CheatUILineTracker& tracker = m_contained[i];
		if (TestFlag(tracker.Line->GetValidContexts(), gCheats->GetCurrentContext()))
		{
			Cheat* cheat = tracker.Line->GetCheat();
			if (cheat && !gCheats->IsCheatValidForCurrentContext(cheat))
				continue;

			height += tracker.Line->GetHeight();
		}
	}

	return height;
}

static bool s_cheatUILineFolderSortReverse = false;

static int CompareCheatUILineByTitle(const void* i_a, const void* i_b)
{
	const CheatUILineTracker* a = (const CheatUILineTracker*)i_a;
	const CheatUILineTracker* b = (const CheatUILineTracker*)i_b;

	if (s_cheatUILineFolderSortReverse)
		return b->Line->GetLabel().compare(a->Line->GetLabel());

	return a->Line->GetLabel().compare(b->Line->GetLabel());
}

void CheatUILineFolder::SortByTitle(bool i_reverse)
{
	s_cheatUILineFolderSortReverse = i_reverse;
	size_t n = m_contained.size();
	if (n == 0)
		return;

	qsort(&m_contained[0], n, sizeof(CheatUILineTracker), CompareCheatUILineByTitle);
}

void CheatUILineFolder::SetUseIndent(bool i_useIndent)
{
	m_useIndent = i_useIndent;
}

void CheatUILineFolder::SetExpanded(bool i_expanded)
{
	m_expanded = i_expanded;
}

/////////////// CheatUIPanel ///////////////

CheatUIPanel::CheatUIPanel()
	: m_initialTouch()
	, m_scroll(0)
	, m_partialOpenTime(PVZ_EOT())
	, m_visible(false)
	, m_keyboardUp(false)
	, m_scrolling(false)
	, m_scrollingStartedAt(0)
	, m_sliderMoving(false)
{
	m_initialTouch.ident = 0;
}

CheatUIPanel::~CheatUIPanel()
{
	for (size_t i = 0; i < m_lines.size(); i++)
	{
		CheatUILine* line = m_lines[i].Line;
		if (line)
			delete line;
	}

	m_lines.clear();
}

bool CheatUIPanel::IsVisible() const
{
	return m_visible;
}

void CheatUIPanel::TouchesCanceled()
{
	m_initialTouch.ident = 0;
	m_scrolling = false;
	m_scrollingStartedAt = 0;
	m_sliderMoving = false;
}

float CheatUIPanel::GetDefaultLineHeight() const
{
	return S(s_lineHeight);
}

CheatUILine* CheatUIPanel::AddLine(CheatUILine* i_line)
{
	return i_line;
}

CheatUILine* CheatUIPanel::AddLine(const std::string& i_cheatName, const std::string& i_cheatLabel)
{
	return NULL;
}

CheatUILine* CheatUIPanel::AddSeparator()
{
	return AddLine(new CheatUILineSeparator());
}

Rect CheatUIPanel::GetScreenRect() const
{
	int screenWidth = gLawnApp->mWidth;
	int screenHeight = gLawnApp->mHeight;
	float width = S(s_panelWidth);
	return Rect((int)(screenWidth - width), 0, (int)width, screenHeight);
}

Rect CheatUIPanel::getCloseButtonRect() const
{
	Rect screen = GetScreenRect();
	Rect r(screen);
	r.mX = (int)(r.mX - S(s_buttonSize + 8.0f));
	r.mY = (int)(S(0.0f) + r.mY);
	r.mWidth = (int)S(s_buttonSize);
	r.mHeight = (int)S(s_buttonSize);
	return r;
}

Rect CheatUIPanel::getCollapseButtonRect() const
{
	Rect screen = GetScreenRect();
	Rect r(screen);
	float offset = s_buttonSize + 8.0f;
	r.mX = (int)(r.mX - S(offset));
	r.mY = (int)(S(offset) + r.mY);
	r.mWidth = (int)S(s_buttonSize);
	r.mHeight = (int)S(s_buttonSize);
	return r;
}

Rect CheatUIPanel::getSliderButtonRect()
{
	Rect r;
	r.mX = (int)(gLawnApp->mWidth - S(18.f));
	r.mWidth = (int)S(16.f);

	int y = 0;
	float total = getTotalHeight();
	float screenHeight = (float)gLawnApp->mHeight;
	if (total <= screenHeight)
		total = screenHeight;

	float thumbHeight = (screenHeight / total) * screenHeight;
	if (screenHeight != thumbHeight)
	{
		float range = total - screenHeight;
		y = (int)((screenHeight - thumbHeight) * ((float)abs(m_scroll) / range));
	}

	r.mY = y;
	r.mHeight = (int)thumbHeight;
	return r;
}

void CheatUIPanel::SetVisible(bool i_visible)
{
	if (!NetworkItemMgr::GetInstance().HasNetworkCacheSyncComplete())
	{
		if (!NetworkItemMgr::GetInstance().IsSyncComplete())
		{
			PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[SYNCING_WAITING_TITLE]"), SexyString(L"[SYNCING_WAITING_TEXT]"));
			dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog));
			return;
		}
	}

	m_visible = i_visible;
	if (!i_visible)
		SetKeyboardMode(false);
}

void CheatUIPanel::DoPartialOpenOrClose()
{
	if (IsVisible())
	{
		SetVisible(false);
	}
	else if (NetworkItemMgr::GetInstance().HasNetworkCacheSyncComplete() || NetworkItemMgr::GetInstance().IsSyncComplete())
	{
		float now = PVZ_EOT();
		if (m_partialOpenTime < now && PVZ_RealT() - m_partialOpenTime < 1.0f)
		{
			m_partialOpenTime = now;
			SetVisible(true);
		}
		else
		{
			m_partialOpenTime = PVZ_RealT();
		}
	}
	else
	{
		PVZ2UIDialog* dialog = gLawnApp->ShowPVZ2Dialog(SexyString(L"[SYNCING_WAITING_TITLE]"), SexyString(L"[SYNCING_WAITING_TEXT]"));
		dialog->AddButton(SexyString(L"[DIALOG_STRING_OK]"), MakeDelegate(*gLawnApp, &LawnApp::KillPVZ2Dialog));
	}
}

void CheatUIPanel::Tap(Point i_loc)
{
	i_loc.mY -= m_scroll;
	float panelWidth = S(s_panelWidth);
	Rect rect(0, 0, (int)panelWidth, 0);
	for (size_t i = 0; i < m_lines.size(); i++)
	{
		CheatUILineTracker& tracker = m_lines[i];
		if (TestFlag(tracker.Line->GetValidContexts(), gCheats->GetCurrentContext()))
		{
			Cheat* cheat = tracker.Line->GetCheat();
			if (cheat && !gCheats->IsCheatValidForCurrentContext(cheat))
				continue;

			float lineHeight = m_lines[i].Line->GetHeight();
			rect.mHeight = (int)lineHeight;
			int step = (int)lineHeight;
			if (rect.Contains(i_loc))
			{
				Point local(i_loc.mX, i_loc.mY - rect.mY);
				m_lines[i].Line->Tap(local);
				step = rect.mHeight;
			}

			rect.mY += step;
		}
	}
}

void CheatUIPanel::SetKeyboardMode(bool i_keyboardMode)
{
	m_keyboardUp = i_keyboardMode;
	if (i_keyboardMode)
		gLawnApp->ShowKeyboard();
	else
		gLawnApp->HideKeyboard();
}

static CheatUILine* BuildUILineFromLabel(const std::string& i_label)
{
	return NULL;
}

CheatUILine* CheatUIPanel::BuildUILineForCheat(const std::string& i_cheatName, const std::string& i_cheatLabel)
{
	std::string label = i_cheatLabel;
	return BuildUILineFromLabel(label);
}

float CheatUIPanel::getTotalHeight()
{
	float total = 0.0f;
	for (size_t i = 0; i < m_lines.size(); i++)
	{
		Cheat* cheat = m_lines[i].Line->GetCheat();
		if (!cheat || gCheats->IsCheatValidForCurrentContext(cheat))
			total += m_lines[i].Line->GetHeight();
	}
	return total;
}

CheatUILineFolder* CheatUIPanel::BeginFolder(const std::string& i_folderLabel, bool i_expanded)
{
	CheatUILineFolder* folder = new CheatUILineFolder(i_folderLabel, i_expanded);
	AddLine(folder);
	m_folderStack.push_back(folder);
	return folder;
}

CheatUILineFolder* CheatUIPanel::EndFolder()
{
	CheatUILineFolder* folder = m_folderStack[m_folderStack.size() - 1];
	m_folderStack.erase(m_folderStack.begin() + m_folderStack.size() - 1);
	return folder;
}

void CheatUIPanel::collapseTopLevelFolder()
{
	for (size_t i = 0; i < m_lines.size(); i++)
	{
		CheatUILineFolder* folder = m_lines[i].Line->Cast<CheatUILineFolder>();
		if (folder)
			folder->SetExpanded(false);
	}
}

void CheatUIPanel::SetScrollAmount(int i_scrollAmount)
{
	if ((float)i_scrollAmount > 0.0f)
	{
		m_scroll = 0;
		return;
	}

	m_scroll = i_scrollAmount;

	float total = 0.0f;
	for (size_t i = 0; i < m_lines.size(); i++)
	{
		Cheat* cheat = m_lines[i].Line->GetCheat();
		if (!cheat || gCheats->IsCheatValidForCurrentContext(cheat))
			total += m_lines[i].Line->GetHeight();
	}

	float screenHeight = (float)gLawnApp->mHeight;
	if (total > screenHeight)
		total = 0.0f;
	else
		total = screenHeight - total;

	if ((float)m_scroll < total)
		m_scroll = (int)total;
}

bool CheatUIPanel::TouchMoved(const Sexy::Touch& i_touch)
{
	if (i_touch.ident != m_initialTouch.ident)
		return false;

	if (!m_scrolling)
	{
		TPoint<int> delta = m_initialTouch.location - i_touch.location;
		int magnitude = delta.Magnitude();
		double elapsed = i_touch.timestamp - m_initialTouch.timestamp;
		int threshold = S(10);
		if (elapsed > 0.25 || magnitude > threshold)
		{
			m_scrollingStartedAt = m_scroll;
			m_scrolling = true;
			if (getSliderButtonRect().Contains(m_initialTouch.location))
				m_sliderMoving = true;
		}

		if (!m_scrolling)
			return true;
	}

	int dy = i_touch.location.mY - m_initialTouch.location.mY;
	if (m_sliderMoving)
	{
		float total = getTotalHeight();
		int screenHeight = gLawnApp->mHeight;
		dy = (int)((total * (float)-dy) / (float)screenHeight);
	}

	SetScrollAmount(dy + m_scrollingStartedAt);
	return true;
}

bool CheatUIPanel::TouchEnded(const Sexy::Touch& i_touch)
{
	if (i_touch.ident != m_initialTouch.ident)
		return false;

	Rect closeRect = getCloseButtonRect();
	Rect collapseRect = getCollapseButtonRect();
	if (closeRect.Contains(i_touch.location))
	{
		gLawnApp->SetCheatsEnabled(false);
	}
	else if (collapseRect.Contains(i_touch.location))
	{
		collapseTopLevelFolder();
	}
	else if (!m_scrolling)
	{
		Rect screen = GetScreenRect();
		Tap(i_touch.location - Point(screen.mX, screen.mY));
	}

	m_initialTouch.ident = 0;
	m_scrolling = false;
	m_scrollingStartedAt = 0;
	m_sliderMoving = false;
	return true;
}

bool CheatUIPanel::TouchBegan(const Sexy::Touch& i_touch)
{
	bool result = m_visible;
	if (result)
	{
		if (m_keyboardUp)
		{
			result = false;
		}
		else
		{
			long long ident = m_initialTouch.ident;
			if (ident != 0)
			{
				result = false;
			}
			else
			{
				const Point& location = i_touch.location;
				Rect screen = GetScreenRect();
				if (!screen.Contains(location))
				{
					Rect close = getCloseButtonRect();
					if (!close.Contains(location))
					{
						Rect collapse = getCollapseButtonRect();
						if (!collapse.Contains(location))
						{
							m_scrolling = false;
							return ident != 0;
						}
					}
				}

				m_initialTouch = i_touch;
			}
		}
	}

	return result;
}

void CheatUIPanel::Draw(Graphics* i_g)
{
	if (!m_visible)
	{
		if (m_partialOpenTime < PVZ_EOT() && PVZ_RealT() - m_partialOpenTime < 1.0f)
		{
			GraphicsAutoState state(i_g);
			i_g->SetDrawMode(0);
			i_g->SetColorizeImages(true);
			i_g->SetColor(Color(70, 70, 70, 240));
			int width = S(10);
			i_g->FillRect(gLawnApp->mWidth - width, 0, width, gLawnApp->mHeight);
			i_g->Translate(gLawnApp->mWidth - S(10), (int)(((float)gLawnApp->mHeight - S(s_tabHeight)) * 0.5f));
			i_g->DrawImage(s_panelLaneImage, 0, 0);
		}
	}
	else if (m_keyboardUp)
	{
		if (!gLawnApp->IsKeyboardShowing())
			SetVisible(false);
	}
	else
	{
		SetScrollAmount(m_scroll);
		GraphicsAutoState outer(i_g);
		i_g->Translate((int)(gLawnApp->mWidth - S(s_panelWidth)), 0);
		i_g->SetDrawMode(0);
		i_g->SetColorizeImages(true);
		i_g->SetColor(Color(70, 70, 70, 240));
		i_g->FillRect(0, 0, (int)S(s_panelWidth), gLawnApp->mHeight);

		{
			GraphicsAutoState inner(i_g);
			i_g->Translate((int)-S(s_buttonSize + 8.0f), (int)S(0.0f));
			i_g->SetColor(Color(70, 70, 70, 240));
			int size = (int)S(s_buttonSize + 8.0f);
			i_g->FillRect(0, 0, size, size);
			i_g->SetColor(Color(Color::White));
			CachedResourcePtr<Sexy::Image>& imageRef = s_panelFolderImage;
			Image* image = imageRef;
			Rect dest((int)S(4.0f), (int)S(4.0f), (int)S(s_buttonSize), (int)S(s_buttonSize));
			Rect src(0, 0, ((Image*)imageRef)->mWidth, ((Image*)imageRef)->mHeight);
			i_g->DrawImage(image, dest, src);
		}

		{
			GraphicsAutoState inner(i_g);
			float offset = S(s_buttonSize + 8.0f);
			i_g->Translate((int)-offset, (int)offset);
			i_g->SetColor(Color(70, 70, 70, 240));
			int size = (int)S(s_buttonSize + 8.0f);
			i_g->FillRect(0, 0, size, size);
			i_g->SetColor(Color(Color::White));
			CachedResourcePtr<Sexy::Image>& imageRef = s_panelLaneImage;
			Image* image = imageRef;
			float buttonSize = s_buttonSize;
			Rect dest((int)S(buttonSize * 0.25f + 4.0f), (int)S(4.0f), (int)S(buttonSize * 0.5f), (int)S(buttonSize));
			Rect src(0, 0, ((Image*)imageRef)->mWidth, ((Image*)imageRef)->mHeight);
			i_g->DrawImage(image, dest, src);
		}

		{
			GraphicsAutoState inner(i_g);
			i_g->Translate((int)S(s_panelWidth - 20.0f), S(0));
			i_g->SetColor(Color(140, 140, 140, 240));
			i_g->FillRect(0, 0, S(20), gLawnApp->mHeight);
			i_g->SetColor(Color(70, 70, 70, 240));
			Rect first = getSliderButtonRect();
			float sliderWidth = S(16.f);
			Rect second = getSliderButtonRect();
			i_g->FillRect(2, first.mY, (int)sliderWidth, second.mHeight);
		}

		if (m_lines.size() != 0)
		{
			i_g->Translate(0, m_scroll);
			size_t i = 0;
			goto body;
		next:
			i++;
			if (m_lines.size() <= i)
				return;
		body:
			{
				CheatUILineTracker& tracker = m_lines[i];
				if (TestFlag(tracker.Line->GetValidContexts(), gCheats->GetCurrentContext()))
				{
					Cheat* cheat = tracker.Line->GetCheat();
					if (cheat && !gCheats->IsCheatValidForCurrentContext(cheat))
						goto next;

					tracker.Line->Draw(i_g);
					i_g->Translate(0, (int)tracker.Line->GetHeight());
				}
				goto next;
			}
		}
	}
}
