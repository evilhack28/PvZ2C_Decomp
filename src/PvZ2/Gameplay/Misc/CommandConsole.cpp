//
//  CommandConsole.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-08.
//

#include "SexyAppFramework/Common.h"

#include "CommandConsole.h"
#include "SexyAppFramework/SysFont.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"

bool StrEquals(const SexyString& a, const SexyString& b, bool ignoreCase);
void SplitStr(SexyString str, CCStringVector& out);

/////////////// CommandConsoleEdit ///////////////

CommandConsole::CommandConsoleEdit::CommandConsoleEdit(int i_id, Sexy::EditListener* i_editListener) : Sexy::EditWidget(i_id, i_editListener)
{
}

CommandConsole::CommandConsoleEdit::~CommandConsoleEdit()
{
}

void CommandConsole::CommandConsoleEdit::KeyDown(Sexy::KeyCode i_key)
{
	if (m_console != NULL && m_console->EditKeyCodeDown(i_key))
		return;
	SuperClass::KeyDown(i_key);
}

void CommandConsole::CommandConsoleEdit::ProcessKey(Sexy::KeyCode i_key, SexyChar i_char)
{
	SuperClass::ProcessKey(i_key, i_char);
	if (m_console != NULL)
		m_console->EditProcessKey(i_key);
}

/////////////// Accessors ///////////////

void CommandConsole::AddLine(const SexyString& str, int num_nl, bool i_doDrawText)
{
	addLineHelper(str, LINETYPE_NORMAL, num_nl, i_doDrawText);
}

void CommandConsole::AddLineWarn(const SexyString& str, int num_nl, bool i_doDrawText)
{
	addLineHelper(str, LINETYPE_WARNING, num_nl, i_doDrawText);
}

void CommandConsole::AddLineErr(const SexyString& str, int num_nl, bool i_doDrawText)
{
	addLineHelper(str, LINETYPE_ERROR, num_nl, i_doDrawText);
}

bool CommandConsole::AllowChar(int i_id, SexyChar i_char)
{
	return (i_char != '`') && (i_char != '\\');
}

void CommandConsole::SetContext(int context)
{
	if (m_currentContext != context)
	{
		m_currentContext = context;
		RefreshButtons();
	}
}

void CommandConsole::ResetCompletion()
{
	m_displayingCompletion = false;
	m_curCompletionIdx = 0;
	ClearLastCompletionHelp();
}

void CommandConsole::Draw(Sexy::Graphics* g)
{
	if (m_font != NULL)
		DrawWithFont(g);
	else if (m_primeFont != NULL)
		DrawWithPrimeFont(g);
}

void CommandConsole::DrawWithFont(Sexy::Graphics* g)
{
	g->SetFont(m_font);
	if ((double)m_hideYPct != 1.0)
	{
		g->SetColor(Sexy::Color(10, 10, 10, 220));
		g->FillRect(0, 0, mWidth, m_windowHeight);
		g->SetColor(Sexy::Color(Sexy::Color::White));
		int y = m_edit->mY - m_font->GetHeight();
		if (m_startIndex >= 0 && mY <= y)
		{
			int i = m_startIndex;
			goto check;
		draw:
			g->WriteWordWrapped(Sexy::Rect(mX + 10, y, mWidth - 10, m_windowHeight), m_displayLines[i]);
			y -= m_font->GetHeight();
			if (i == 0)
				goto done;
			i--;
			if (y < mY)
				goto done;
		check:
			if (m_font->GetHeight() < 10)
				y -= 30 - m_font->GetHeight();
			goto draw;
		done:;
		}
	}
	else
	{
		g->SetColor(Sexy::Color(Sexy::Color::White));
		g->Translate(0, -mY);
		int y = 20;
		for (int i = (int)m_drawScreenTexts.size() - 1; i >= 0; i--)
		{
			DrawScreenText& text = m_drawScreenTexts[i];
			int index = text.m_textIdx;
			if (index >= (int)m_displayLines.size() || index < 0)
				continue;
			int updatesRemaining = text.m_updatesRemaining;
			if (Sexy::gSexyAppBase->mHeight < y)
				break;
			int halfHeight = GetDisplayLineHeight(i, g) / 2;
			if (m_font->GetHeight() < halfHeight)
				y += halfHeight - m_font->GetHeight() + 20;
			if (updatesRemaining < m_drawScreenTextFadeAt)
			{
				g->SetColor(Sexy::Color::FAlpha((float)updatesRemaining / (float)m_drawScreenTextFadeAt));
				g->SetColorizeImages(true);
			}
			else
			{
				g->SetColor(Sexy::Color(0xffffffff));
			}
			g->SetColor(Sexy::Color(0, g->mColor.mAlpha));
			g->WriteString(m_displayLines[index], mX + 11, y + 1, -1, -1, true, 0, -1, -1);
			g->SetColor(Sexy::Color(-1, g->mColor.mAlpha));
			g->WriteString(m_displayLines[index], mX + 10, y, -1, -1, true, 0, -1, -1);
			g->SetColor(Sexy::Color(0xffffffff));
			g->SetColorizeImages(false);
			y += m_font->GetHeight();
		}
		g->Translate(0, mY);
	}
}

void CommandConsole::DrawWithPrimeFont(Sexy::Graphics* g)
{
	if ((double)m_hideYPct != 1.0)
	{
		g->SetColor(Sexy::Color(10, 10, 10, 220));
		g->FillRect(0, 0, mWidth, m_windowHeight);
		g->SetColor(Sexy::Color(Sexy::Color::White));
		int y = (int)((float)m_edit->mY - m_primeFont->GetHeight());
		if (m_startIndex >= 0 && mY <= y)
		{
			int i = m_startIndex;
			goto check;
		draw:
			{
				float height = (float)m_windowHeight;
				float width = (float)(mWidth - 10);
				float left = (float)(mX + 10);
				m_primeFont->DrawString_Paragraph(g, left, (float)y, width, height, m_displayLines[i]);
			}
			y = (int)((float)y - m_primeFont->GetHeight());
			if (i == 0)
				goto done;
			i--;
			if (y < mY)
				goto done;
		check:
			if (m_primeFont->GetHeight() < 10.0f)
				y = (int)((float)y + -30.0f + m_primeFont->GetHeight());
			goto draw;
		done:;
		}
	}
	else
	{
		g->SetColor(Sexy::Color(Sexy::Color::White));
		g->Translate(0, -mY);
		int y = 20;
		for (int i = (int)m_drawScreenTexts.size() - 1; i >= 0; i--)
		{
			DrawScreenText& text = m_drawScreenTexts[i];
			int index = text.m_textIdx;
			if (index >= (int)m_displayLines.size() || index < 0)
				continue;
			int updatesRemaining = text.m_updatesRemaining;
			if (Sexy::gSexyAppBase->mHeight < y)
				break;
			int halfHeight = GetDisplayLineHeight(i, g) / 2;
			if (m_font->GetHeight() < halfHeight)
				y += halfHeight - m_font->GetHeight() + 20;
			if (updatesRemaining < m_drawScreenTextFadeAt)
			{
				g->SetColor(Sexy::Color::FAlpha((float)updatesRemaining / (float)m_drawScreenTextFadeAt));
				g->SetColorizeImages(true);
			}
			else
			{
				g->SetColor(Sexy::Color(0xffffffff));
			}
			float fy = (float)y;
			Sexy::Color shadow(0, g->mColor.mAlpha);
			Sexy::Color color(-1, g->mColor.mAlpha);
			m_primeFont->DrawString_Simple(g, (float)(mX + 11), (float)(y + 1), m_displayLines[index], shadow, NULL);
			m_primeFont->DrawString_Simple(g, (float)(mX + 10), fy, m_displayLines[index], color, NULL);
			g->SetColor(Sexy::Color(0xffffffff));
			g->SetColorizeImages(false);
			y = (int)(m_primeFont->GetHeight() + fy);
		}
		g->Translate(0, mY);
	}
}

/////////////// History ///////////////

void CommandConsole::AddHistory(const SexyString& str, bool mod_index)
{
	SexyString trimmed = Sexy::Trim(str);
	if (trimmed.length() == 0)
		return;
	m_history.push_back(trimmed);
	if (mod_index)
		m_historyIndex = (int)m_history.size();
}

void CommandConsole::ShowError(const SexyString& msg)
{
	AddLine(_S("^FF00FF^ERROR: ^FFFFFF^") + msg);
}

/////////////// Completion ///////////////

void CommandConsole::UpdateCompletionHelp()
{
	ClearLastCompletionHelp();
	ConsoleContext* context = FindCurrentContext();
	if (context != NULL)
	{
		CCStringVector completions;
		GetAllCompletionStrings(completions);
		const SexyString& text = m_edit->mString;
		if (!text.empty())
		{
			const SexyChar* message;
			size_t space = text.find(_S(' '), 0);
			if (space != SexyString::npos)
			{
				{
					SexyString name = text.substr(0, space);
					ConsoleActionMap::iterator it = context->m_actions.find(name);
					if (it == context->m_actions.end())
						goto miss;
					m_completionHelpLength++;
					AddLine(Sexy::StrFormat(_S("^44f744^%ls:^99f799^%ls^ffffff^"), name.c_str(), it->second.m_description.c_str()), 0, false);
					goto done;
				}
			miss:
			noMatch:
				m_completionHelpLength++;
				message = _S("^ffff66^No matching commands^ffffff^");
			addMessage:
				AddLine(message);
				goto done;
			}
			else
			{
				if (completions.empty())
					goto noMatch;
				AddLine(_S(""));
				AddLine(_S("Available Commands"));
				AddLine(_S("--------------------"));
				m_completionHelpLength += 3;
				int maxLength = 0;
				for (CCStringVector::iterator it = completions.begin(); it != completions.end(); ++it)
					maxLength = std::max(maxLength, (int)it->length());
				maxLength = std::min(31, maxLength + 1);
				for (CCStringVector::iterator it = completions.begin(); it != completions.end(); ++it)
				{
					if (m_completionHelpLength > 20)
					{
						message = _S(" ^fff71f^[...]^ffffff^");
						goto addMessage;
					}
					SexyChar padding[33];
					uint padLength = maxLength - it->length();
					for (uint i = 0; i < padLength; i++)
						padding[i] = ' ';
					padding[padLength] = 0;
					if (*it == text)
						AddLine(Sexy::StrFormat(_S("^44f744^%ls:^99f799^%ls%ls^ffffff^"), it->c_str(), padding, context->m_actions[*it].m_description.c_str()));
					else
						AddLine(Sexy::StrFormat(_S("^fff71f^%ls^ffffff^:%ls%ls"), it->c_str(), padding, context->m_actions[*it].m_description.c_str()));
					m_completionHelpLength++;
				}
			}
		}
	done:;
	}
}

void CommandConsole::ClearLastCompletionHelp()
{
	if (m_completionHelpLength > 0)
	{
		m_displayLines.resize(m_displayLines.size() - m_completionHelpLength);
		m_startIndex = (int)m_displayLines.size() - 1;
	}
	m_completionHelpLength = 0;
}

/////////////// Context ///////////////

ConsoleContext* CommandConsole::FindCurrentContext()
{
	for (int i = 0; i < (int)m_context.size(); i++)
	{
		if (m_context[i].m_contextNum == m_currentContext)
			return &m_context[i];
	}
	return NULL;
}

/////////////// Contexts ///////////////

void CommandConsole::EraseContext(int context)
{
	for (int i = 0; i < (int)m_context.size(); i++)
	{
		if (m_context[i].m_contextNum == context)
		{
			m_context.erase(m_context.begin() + i);
			if (m_currentContext == context)
				m_currentContext = 0;
			break;
		}
	}
}

/////////////// Buttons ///////////////

void CommandConsole::ClearButtons()
{
	for (uint i = 0; i < m_btnWidgets.size(); i++)
	{
		if (mWidgetManager->mFocusWidget == m_btnWidgets[i])
			Sexy::gSexyAppBase->mWidgetManager->SetFocus(NULL);
		RemoveWidget(m_btnWidgets[i]);
		Sexy::gSexyApp->SafeDeleteWidget(m_btnWidgets[i]);
	}
	m_btnWidgets.clear();
}

/////////////// Layout ///////////////

void CommandConsole::RefreshSize(bool i_forced)
{
	if (!m_autosetSize)
		return;
	if (!i_forced && mWidth == Sexy::gSexyAppBase->mWidth && m_windowHeight == Sexy::gSexyAppBase->mHeight / 2)
		return;
	m_windowHeight = Sexy::gSexyAppBase->mHeight / 2;
	Resize(0, 0, Sexy::gSexyAppBase->mWidth, m_windowHeight);
	if (m_edit != NULL)
	{
		int editHeight = m_font->GetHeight() + 10;
		m_edit->Resize(10, m_windowHeight - editHeight - 5, mWidth - 20, editHeight);
	}
	RefreshButtonPositions();
}

/////////////// Lifecycle ///////////////

CommandConsole::CommandConsole(Sexy::PrimeTypeface* font)
{
	m_autosetSize = true;
	m_edit = NULL;
	m_font = NULL;
	RefreshSize(true);
	m_completionHelpLength = 0;
	m_drawScreenTextFadeAt = 50;
	mWidgetFlagsMod.mRemoveFlags |= Sexy::WIDGETFLAGS_CLIP;
	m_drawScreenTextDur = 500;
	m_currentContext = 0;
	m_needDeleteFont = false;
	m_updateCnt = 0;
	m_baseY = 0;
	m_hideYPct.SetConstant(1.0);
	ResetCompletion();
	m_edit = new CommandConsoleEdit(1, this);
	m_edit->mBlinkDelay = 0x7fffffff;
	m_edit->mShowingCursor = true;
	m_edit->m_console = this;
	m_edit->mClipInset = 0;
	SetFont(font);
	m_displayingCompletion = false;
	mPriority = 100000;
	mZOrder = 100000;
	m_edit->mPriority = 100001;
	m_edit->mZOrder = 100001;
	m_lastFocusWidget = NULL;
	m_startIndex = 0;
	m_historyIndex = 0;
	mHasAlpha = true;
	m_edit->mHasTransparencies = true;
	AddWidget(m_edit);
	AddLine(_S("*** Command Console ***"));
	AddLine(_S("^fff71f^/?^FFFFFF^         List commands in current context"));
	AddLine(_S("^fff71f^ctrl-UP^FFFFFF^:   Scrolls the currently displayed text up a line"));
	AddLine(_S("^fff71f^ctrl-DOWN^FFFFFF^: Scrolls the currently displayed text down a line"));
	AddLine(_S("^fff71f^UP^FFFFFF^:        Scrolls up in the command history buffer"));
	AddLine(_S("^fff71f^DOWN^FFFFFF^:      Scrolls down in the command history buffer"));
	AddLine(_S("^fff71f^/clear^ffffff^:    Clears the console"));
	AddLine(_S("^fff71f^ctrl-` key^FFFFFF^:Closes/opens this window"), 1);
	m_hidden = false;
	Hide(true);
}

CommandConsole::~CommandConsole()
{
	RemoveAllWidgets(true, true);
	if (m_lastFocusWidget != NULL)
		Sexy::gSexyAppBase->mWidgetManager->SetFocus(m_lastFocusWidget);
	if (m_needDeleteFont && m_font != NULL)
		delete m_font;
}

void CommandConsole::RefreshButtonPositions()
{
	int maxWidth = 0;
	int btnHeight = m_font != NULL ? m_font->GetHeight() + 10 : 30;
	for (uint i = 0; i < m_btnWidgets.size(); i++)
	{
		int width = m_font->StringWidth(m_btnWidgets[i]->mLabel) + 16;
		maxWidth = std::max(maxWidth, width);
	}
	int column = 1;
	int row = 0;
	for (uint i = 0; i < m_btnWidgets.size(); i++)
	{
		m_btnWidgets[i]->Resize(mWidth + (-6 - maxWidth) * column, (btnHeight + 4) * row + 6, maxWidth, btnHeight);
		row++;
		if (mHeight - m_edit->mHeight < m_btnWidgets[i]->mY + m_btnWidgets[i]->mHeight)
		{
			column++;
			i--;
			row = 0;
		}
	}
}

void CommandConsole::RefreshButtons()
{
	ClearButtons();
	for (uint i = 0; i < m_context.size(); i++)
	{
		if (m_context[i].m_contextNum != m_currentContext)
			continue;
		ConsoleActionMap& actions = m_context[i].m_actions;
		for (ConsoleActionMap::iterator it = actions.begin(); it != actions.end(); ++it)
		{
			if (!it->second.m_hasBtn)
				continue;
			Sexy::ButtonWidget* btn = new Sexy::ButtonWidget(m_btnWidgets.size() + BTN_WIDGET_START_ID, this);
			btn->mDoFinger = true;
			btn->SetFont(m_font);
			btn->SetFont(m_primeFont);
			btn->mLabel = it->first;
			AddWidget(btn);
			m_btnWidgets.push_back(btn);
		}
		RefreshButtonPositions();
		break;
	}
}

/////////////// Output ///////////////

void CommandConsole::addLineHelper(const SexyString& str, ELineType i_lineType, int num_nl, bool i_doDrawText)
{
	switch (i_lineType)
	{
	case LINETYPE_WARNING:
		m_displayLines.push_back(Sexy::StrFormat(_S("%S%ls%S"), "^FFFF44^", str.c_str(), "^FFFFFF^"));
		break;
	case LINETYPE_NORMAL:
		m_displayLines.push_back(str);
		break;
	case LINETYPE_ERROR:
		m_displayLines.push_back(Sexy::StrFormat(_S("%S%ls%S"), "^FF4444^", str.c_str(), "^FFFFFF^"));
		break;
	}
	if (i_doDrawText && m_displayLines.size() != 0)
	{
		DrawScreenText text;
		text.m_textIdx = m_displayLines.size() - 1;
		text.m_updatesRemaining = m_drawScreenTextDur;
		m_drawScreenTexts.push_back(text);
	}
	for (int i = 0; i < num_nl; i++)
		m_displayLines.push_back(_S(""));
	m_startIndex = (int)m_displayLines.size() - 1;
}

////////////// Update ///////////////

void CommandConsole::Update()
{
	m_edit->SetVisible((double)m_hideYPct != 1.0);
	mY = m_baseY - (int)((double)m_hideYPct * m_windowHeight);
	SuperClass::Update();
	MarkDirty();
	for (uint i = 0; i < m_drawScreenTexts.size();)
	{
		if (--m_drawScreenTexts[i].m_updatesRemaining < 1)
			m_drawScreenTexts.erase(m_drawScreenTexts.begin() + i);
		else
			i++;
	}
	m_updateCnt++;
}

/////////////// Help ///////////////

void CommandConsole::DoHelp()
{
	ConsoleContext* context = FindCurrentContext();
	if (context != NULL)
	{
		AddLine(_S(""));
		AddLine(_S("Commands valid in the current context:"));
		for (ConsoleActionMap::iterator it = context->m_actions.begin(); it != context->m_actions.end(); ++it)
			AddLine(_S("^fff71f^") + it->first + _S("^ffffff^:     ") + it->second.m_description);
	}
}

void CommandConsole::EditWidgetText(int id, const SexyString& str)
{
	AddHistory(str, true);
	if (StrEquals(str, _S("/help"), true) || StrEquals(str, _S("help"), true) || StrEquals(str, _S("/?"), true) || StrEquals(str, _S("?"), true))
	{
		DoHelp();
		m_edit->mString = _S("");
		return;
	}
	if (StrEquals(str.substr(0, 6), _S("/clear"), true))
	{
		m_displayLines.clear();
		m_startIndex = -1;
		m_edit->mString = _S("");
		return;
	}
	CCStringVector args;
	SplitStr(str, args);
	SexyString name = str.substr(0, str.find(_S(' '), 0));
	for (int i = 0; i < (int)m_context.size(); i++)
	{
		if (m_context[i].m_contextNum != m_currentContext)
			continue;
		ConsoleActionMap& actions = m_context[i].m_actions;
		for (ConsoleActionMap::iterator it = actions.begin(); it != actions.end(); ++it)
		{
			if (StrEquals(name, it->first, true))
			{
				it->second.m_callback(name, args);
				m_edit->mString = _S("");
				return;
			}
		}
		AddLine(_S("Error: unknown command \"") + name + _S("\""));
		m_edit->mString = _S("");
		return;
	}
	AddLine(_S("Error: unknown command \"") + name + _S("\""));
	m_edit->mString = _S("");
}

int CommandConsole::GetDisplayLineHeight(int i, Sexy::Graphics* g)
{
	if ((int)m_displayLinesHeight.size() <= i)
		m_displayLinesHeight.resize(i + 1, -1);
	if (m_displayLinesHeight[i] == -1)
	{
		if (m_font != NULL)
		{
			g->SetFont(m_font);
			m_displayLinesHeight[i] = g->GetWordWrappedHeight(mWidth - 10, m_displayLines[i], -1, NULL, NULL);
		}
		else if (m_primeFont != NULL)
		{
			int width;
			m_primeFont->SizeString_Paragraph(m_displayLines[i], width, m_displayLinesHeight[i], 0.0f);
		}
	}
	return m_displayLinesHeight[i];
}

void CommandConsole::GetAllCompletionStrings(CCStringVector& i_completionStrings)
{
	ConsoleContext* context = FindCurrentContext();
	if (context == NULL)
		return;
	SexyString text = m_edit->mString;
	if (m_displayingCompletion)
		text = text.substr(0, m_edit->mHilitePos);
	for (ConsoleActionMap::iterator it = context->m_actions.begin(); it != context->m_actions.end(); ++it)
	{
		const SexyString& command = it->first;
		uint j;
		for (j = 0; j < text.length(); j++)
		{
			if (command.length() <= j || text[j] != command[j])
				break;
		}
		if (j == text.length())
			i_completionStrings.push_back(command);
	}
}


/////////////// Input ///////////////

void CommandConsole::EditProcessKey(Sexy::KeyCode key)
{
	if (key == Sexy::KEYCODE_RETURN)
	{
		m_edit->SetText(_S(""), true);
		ResetCompletion();
		return;
	}
	UpdateCompletionHelp();
	int index;
	if (key == Sexy::KEYCODE_UP && mWidgetManager->mKeyDown[Sexy::KEYCODE_CONTROL])
	{
		index = m_startIndex - 1;
		if (index < 0)
			index = 0;
		m_startIndex = index;
	}
	else if (!mWidgetManager->mKeyDown[Sexy::KEYCODE_CONTROL] || key != Sexy::KEYCODE_DOWN)
	{
		if (key == Sexy::KEYCODE_UP)
		{
			if (m_historyIndex < 1)
				return;
			index = m_historyIndex - 1;
			m_historyIndex = index;
		}
		else
		{
			if (key != Sexy::KEYCODE_DOWN)
				return;
			index = m_historyIndex + 1;
			if ((int)m_history.size() <= index)
				return;
			m_historyIndex = index;
		}
		m_edit->mString = m_history[index];
		m_edit->mCursorPos = (int)m_edit->mString.length();
	}
	else
	{
		index = m_startIndex;
		m_startIndex = index + 1;
		if ((int)m_displayLines.size() <= index + 1)
			m_startIndex = (int)m_displayLines.size() - 1;
	}
}

bool CommandConsole::EditKeyCodeDown(Sexy::KeyCode key)
{
	if (m_displayingCompletion && key != Sexy::KEYCODE_TAB && key != Sexy::KEYCODE_RETURN && key != Sexy::KEYCODE_SHIFT && key != Sexy::KEYCODE_SPACE)
	{
		m_edit->SetText(m_edit->mString.substr(0, m_edit->mHilitePos), true);
	}
	else
	{
		if (key == Sexy::KEYCODE_TAB)
		{
			DoNextCompletion(mWidgetManager->mKeyDown[Sexy::KEYCODE_SHIFT]);
			return true;
		}
		if (key != Sexy::KEYCODE_RETURN && key != Sexy::KEYCODE_SPACE)
			return false;
	}
	m_edit->mHilitePos = m_edit->mCursorPos;
	ResetCompletion();
	return false;
}

void CommandConsole::ButtonDepress(int i_id)
{
	int index = i_id - BTN_WIDGET_START_ID;
	if (index >= 0 && index < (int)m_btnWidgets.size())
	{
		Sexy::ButtonWidget* btn = m_btnWidgets[index];
		ConsoleContext* context = FindCurrentContext();
		for (ConsoleActionMap::iterator it = context->m_actions.begin(); it != context->m_actions.end(); ++it)
		{
			if (it->first == btn->mLabel)
			{
				it->second.m_callback(it->first, CCStringVector());
				break;
			}
		}
	}
}

/////////////// Completion ///////////////

void CommandConsole::DoNextCompletion(bool i_doReverseCompletion)
{
	CCStringVector completions;
	GetAllCompletionStrings(completions);
	int hilitePos = m_edit->mCursorPos;
	size_t index;
	if (m_displayingCompletion)
	{
		hilitePos = m_edit->mHilitePos;
		size_t count = completions.size();
		if (count == 0)
			goto none;
		if (!i_doReverseCompletion)
		{
			m_curCompletionIdx++;
			index = m_curCompletionIdx % count;
		}
		else
		{
			int prev = m_curCompletionIdx - 1;
			if (prev < 0)
			{
				prev = (int)count - 1;
				m_curCompletionIdx = prev;
				index = prev % count;
			}
			else
			{
				m_curCompletionIdx = prev;
				index = prev % count;
			}
		}
	}
	else
	{
		if (completions.size() == 0)
			goto none;
		m_curCompletionIdx = 0;
		index = 0;
	}
	m_edit->SetText(completions[index], true);
	m_edit->mHilitePos = hilitePos;
	m_displayingCompletion = true;
	goto update;
none:
	m_displayingCompletion = false;
update:
	UpdateCompletionHelp();
}


/////////////// Fonts ///////////////

void CommandConsole::SetFont(Sexy::PrimeTypeface* i_font)
{
	if (m_needDeleteFont)
	{
		if (m_font != NULL)
			delete m_font;
		m_needDeleteFont = false;
	}
	if (i_font == NULL)
		m_primeFont = Sexy::PrimeText::Instance()->TypefaceDefault();
	else
		m_primeFont = i_font;
	int editHeight = (int)(m_primeFont->GetHeight() + 10.0f);
	m_edit->SetFont(m_primeFont, NULL);
	m_edit->Resize(10, m_windowHeight - editHeight - 5, mWidth - 20, editHeight);
	RefreshButtons();
}

void CommandConsole::SetFont(Sexy::Font* i_font)
{
	if (m_needDeleteFont)
	{
		if (m_font != NULL)
			delete m_font;
		m_needDeleteFont = false;
	}
	if (i_font == NULL)
		m_font = new Sexy::SysFont("Courier");
	else
		m_font = i_font->Duplicate();
	m_needDeleteFont = true;
	int editHeight = m_font->GetHeight() + 10;
	m_edit->SetFont(m_font, NULL);
	m_edit->Resize(10, m_windowHeight - editHeight - 5, mWidth - 20, editHeight);
	RefreshButtons();
}

/////////////// Commands ///////////////

void CommandConsole::AddCommand(int context, const SexyString& command, const SexyString& desc, bool i_addButton, ConsoleCallback callback_func)
{
	ConsoleContext* consoleContext;
	int count = (int)m_context.size();
	int i = 0;
	do
	{
		if (count <= i)
		{
			m_context.push_back(ConsoleContext());
			consoleContext = &m_context[m_context.size() - 1];
			break;
		}
		consoleContext = &m_context[i++];
	} while (consoleContext->m_contextNum != context);
	ConsoleAction action;
	action.m_callback = callback_func;
	action.m_description = desc;
	action.m_hasBtn = i_addButton;
	consoleContext->m_actions[command] = action;
	consoleContext->m_contextNum = context;
}


/////////////// Visibility ///////////////

void CommandConsole::Hide(bool should_hide)
{
	if (m_hidden == should_hide)
		return;
	m_hidden = should_hide;
	if (!should_hide)
	{
		SetVisible(true);
		RefreshSize(false);
		SetDisabled(false);
		m_edit->SetVisible(true);
		m_edit->SetDisabled(false);
		Sexy::WidgetManager* manager = Sexy::gSexyAppBase->mWidgetManager;
		if (this != manager->mFocusWidget && m_edit != manager->mFocusWidget)
			m_lastFocusWidget = manager->mFocusWidget;
		mWidgetFlagsMod.mRemoveFlags &= ~(Sexy::WIDGETFLAGS_ALLOW_MOUSE | Sexy::WIDGETFLAGS_ALLOW_FOCUS);
		Sexy::gSexyAppBase->mWidgetManager->SetFocus(m_edit);
		m_edit->mString.clear();
		m_hideYPct.Intercept("b;0,1,0.01,0.25,~###         ~####");
	}
	else
	{
		SetDisabled(true);
		m_edit->SetDisabled(true);
		if (m_lastFocusWidget != NULL)
			Sexy::gSexyAppBase->mWidgetManager->SetFocus(m_lastFocusWidget);
		for (uint i = 0; i < m_btnWidgets.size(); i++)
		{
			if (mWidgetManager->mFocusWidget == m_btnWidgets[i])
				Sexy::gSexyAppBase->mWidgetManager->SetFocus(NULL);
		}
		mWidgetFlagsMod.mRemoveFlags |= Sexy::WIDGETFLAGS_ALLOW_MOUSE | Sexy::WIDGETFLAGS_ALLOW_FOCUS;
		m_lastFocusWidget = NULL;
		m_hideYPct.Intercept("b;0,1,0.01,0.25,####         ~~###");
	}
	mY = m_baseY - (int)((double)m_hideYPct * m_windowHeight);
}

