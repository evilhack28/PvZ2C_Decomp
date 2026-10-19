//
//  PrimeText_SimpleFormatter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-19.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/PrimeText/PrimeText_SimpleFormatter.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"
#include "SexyAppFramework/PrimeText/PrimeGlyphMesh.h"
#include "SexyAppFramework/Graphics.h"

using namespace Sexy;

/////////////// Drawing ///////////////

void PrimeText_SimpleFormatter::DrawFormattedText(Graphics* g, PrimeTypeface* font, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal, EA::Text::VAlignment alignmentVertical, const Color& color)
{
	PrimeGlyphMesh* aMesh = PrepareFormattedText(font, x, y, width, height, text, alignmentHorizontal, alignmentVertical, color);
	aMesh->Draw(g);
	delete aMesh;
}

/////////////// Formatting ///////////////

EA::Text::TextStyle* PrimeText_SimpleFormatter::ProcessFormatter(SexyString text, int formatterOffset, EA::Text::TextStyle* lastTextStyle, const Color& originalColor, int& formatterLength)
{
	EA::Text::TextStyle* aStyle = new EA::Text::TextStyle(*lastTextStyle);
	if (text[formatterOffset + 1] == 'o')
	{
		if (wcsncmp(text.c_str() + ((long)formatterOffset + 1), L"oldclr", 6) == 0)
			aStyle->mColor = originalColor.ToInt();
	}
	else
	{
		uint32_t aColor = 0;
		long aIndex = (long)formatterOffset + 1;
		uint32_t aShift = 20;
		do
		{
			unsigned int aChar = text[aIndex];
			unsigned int aDigit = aChar - '0';
			int aValue;
			if (aDigit <= 9)
				aValue = aDigit << aShift;
			else
			{
				aValue = 0;
				if (aChar - 'A' < 6)
					aValue = (aChar - 55) << aShift;
				else if (aChar - 'a' < 6)
					aValue = (aChar - 87) << aShift;
			}
			aShift -= 4;
			aIndex++;
			aColor += aValue;
		} while (aShift != 0xfffffffc);
		aStyle->mColor = aColor | 0xff000000;
	}
	formatterLength = 8;
	return aStyle;
}

PrimeGlyphMesh* PrimeText_SimpleFormatter::PrepareFormattedText(PrimeTypeface* font, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal, EA::Text::VAlignment alignmentVertical, Color color)
{
	int aResultHeight;
	PrimeTypeface* aFont = font->FitString_Paragraph(text, (int)width, (int)height, aResultHeight);

	TextStyleArray aStyles;
	if (color.IsInvalid())
		color = Color(aFont->GetDefaultStyle().mColor);

	EA::Text::TextStyle aStyle(aFont->GetDefaultStyle());
	aStyle.mColor = color.ToInt();
	EA::Text::Typesetter aTypesetter = aFont->PrepareTypesetter(aStyle, x, y, width, height, alignmentHorizontal, alignmentVertical, color);

	const char16_t* aChars = PrimeText::Instance()->String32to16(text);
	SexyString aUnused;

	int aCount = 0;
	int aPos = 0;
	int aStart = 0;
	int aFormatterLength;
	while ((size_t)aPos < text.size())
	{
		if (text[aPos] != '^')
		{
			aPos++;
			continue;
		}
		if (aPos > aStart)
			aTypesetter.AddTextRun(aChars + aStart, aPos - aStart);
		aCount++;
		EA::Text::TextStyle* aNewStyle = ProcessFormatter(text, aPos, &aStyle, color, aFormatterLength);
		aTypesetter.AddStyleChange(aNewStyle);
		aStyles.push_back(aNewStyle);
		aPos += aFormatterLength;
		aStart = aPos;
	}
	if (aStart < aPos)
		aTypesetter.AddTextRun(aChars + aStart, aPos - aStart);

	PrimeGlyphMesh* aMesh = aFont->PrepareString_Typesetter(aTypesetter, height, true);
	for (int i = 0; i < aCount; i++)
		delete aStyles[i];
	return aMesh;
}
