//
//  Effect_StaticImage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "Effect_StaticImage.h"

Effect_StaticImage::Effect_StaticImage()
{
}

Effect_StaticImage::~Effect_StaticImage()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(Effect_StaticImage);

void Effect_StaticImage::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(Effect_StaticImage);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(StandaloneEffect);

	REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<Image>, m_image);
	REFLECTION_CLASSBUILDER_FIELD(Color, m_imageColor);
	REFLECTION_CLASSBUILDER_FIELD(bool, m_centered);
	REFLECTION_CLASSBUILDER_FIELD(float, m_scale);
	REFLECTION_CLASSBUILDER_FIELD(std::string, m_pieceName);

	REFLECTION_CLASSBUILDER_END(Effect_StaticImage);
}
