//
//  UIWidgetImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "UIWidgetImage.h"

UIWidgetImage::~UIWidgetImage()
{
}

void UIWidgetImage::SetImage(Sexy::Image* pImage)
{
	m_image.m_singleImage = pImage;
	if (m_image.m_imageType == PVZ2UIIMAGE_INITIALIZED)
		m_image.m_imageType = PVZ2UIIMAGE_SINGLE;
}
