//
//  PageControl.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-18.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/misc/iphoneos/PageControl.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Image.h"

namespace Sexy
{

/////////////// Lifecycle ///////////////

PageControl::PageControl(Image *partsImage)
{
	mPartsImage = partsImage;
	mNumberOfPages = 0;
	mCurrentPage = 0;
}

PageControl::~PageControl()
{
}

/////////////// Accessors ///////////////

void PageControl::SetNumberOfPages(int count)
{
	if (mNumberOfPages != count)
	{
		mNumberOfPages = count;
		int w = mPartsImage->GetCelWidth() * count;
		int h = mPartsImage->GetCelHeight();
		Resize(mX, mY, w, h);
	}
}

void PageControl::SetCurrentPage(int page)
{
	mCurrentPage = page;
	MarkDirtyFull();
}

int PageControl::GetCurrentPage()
{
	return mCurrentPage;
}

/////////////// Drawing ///////////////

void PageControl::Draw(Graphics *g)
{
	int w = mPartsImage->GetCelWidth();
	int h = mPartsImage->GetCelHeight();
	int x = (mWidth - mNumberOfPages * w) / 2;
	int y = (mHeight - h) / 2;
	for (int i = 0; i < mNumberOfPages; i++)
	{
		g->DrawImageCel(mPartsImage, x, y, mCurrentPage != i);
		x += w;
	}
}

}
