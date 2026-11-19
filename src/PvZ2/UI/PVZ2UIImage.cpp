//
//  PVZ2UIImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/Image.h"
#include "PVZ2UIButton.h"

/////////////// Accessors ///////////////

int PVZ2UIImage::GetHeight() const
{
	if (m_imageType == PVZ2UIIMAGE_3SLICE_MULTI_IMAGE)
		return m_middleImage->GetHeight();

	return m_singleImage->GetHeight();
}

int PVZ2UIImage::GetWidth() const
{
	if (m_imageType == PVZ2UIIMAGE_3SLICE_MULTI_IMAGE)
		return m_leftImage->GetWidth() + m_middleImage->GetWidth() + m_rightImage->GetWidth();

	return m_singleImage->GetWidth();
}
