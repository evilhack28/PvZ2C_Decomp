//
//  WorldMapCamera.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "WorldMapCamera.h"
#include "ScaledApp.h"
#include "SexyAppFramework/SexyApp.h"
#include "SexyAppFramework/Graphics.h"
#include "PopAnimRig.h"
#include "SexyAppFramework/PopAnim.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"

/////////////// Lifecycle ///////////////

WorldMapCamera::WorldMapCamera(Sexy::Graphics* i_g)
{
	SetCameraScale(1.0f, 1.0f);
	SetGraphics(i_g);
	m_useClipViewport = false;
	m_viewport = Sexy::Rect(0, 0, 1, 1);
}

/////////////// Accessors ///////////////

const Sexy::FPoint& WorldMapCamera::GetCameraScale() const
{
	return m_cameraScale;
}

void WorldMapCamera::SetUseClipViewport(const bool i_useClipping)
{
	m_useClipViewport = i_useClipping;
}

void WorldMapCamera::SetCameraScale(float i_scaleX, float i_scaleY)
{
	m_cameraScale.mX = i_scaleX;
	m_cameraScale.mY = i_scaleY;
	rebuildViewMatrices();
}

void WorldMapCamera::SetCameraCenter(float i_centerX, float i_centerY)
{
	m_cameraCenter.mX = i_centerX;
	m_cameraCenter.mY = i_centerY;
	rebuildViewMatrices();
}

void WorldMapCamera::SetGraphics(Sexy::Graphics* i_g)
{
	m_graphics = i_g;
	if (i_g)
	{
		m_viewport = Sexy::Rect(0, 0, i_g->mDestImage->mWidth, i_g->mDestImage->mHeight);
		m_clipViewportRect = m_viewport;
		SetCameraCenter(m_viewport.mWidth * 0.5f, m_viewport.mHeight * 0.5f);
	}
}

void WorldMapCamera::rebuildViewMatrices()
{
	m_clipViewportRect.mX = -S(200);
	m_clipViewportRect.mY = -S(200);
	m_clipViewportRect.mWidth = m_viewport.mWidth + S(400);
	m_clipViewportRect.mHeight = m_viewport.mHeight + S(400);
}

/////////////// Transforms ///////////////

Sexy::FPoint WorldMapCamera::TransformPointToCamera(float i_X, float i_Y)
{
	return Sexy::FPoint((i_X - m_cameraCenter.mX) * m_cameraScale.mX + m_cameraCenter.mX, (i_Y - m_cameraCenter.mY) * m_cameraScale.mY + m_cameraCenter.mY);
}

/////////////// Drawing ///////////////

void WorldMapCamera::DrawLine(float i_startX, float i_startY, float i_endX, float i_endY)
{
	Sexy::FPoint start = TransformPointToCamera(i_startX, i_startY);
	Sexy::FPoint end = TransformPointToCamera(i_endX, i_endY);
	m_graphics->DrawLine(start.mX, start.mY, end.mX, end.mY);
}

void WorldMapCamera::DrawRect(const Sexy::Rect& i_rect)
{
	Sexy::FPoint pos = TransformPointToCamera(i_rect.mX, i_rect.mY);
	Sexy::Rect rect(pos.mX, pos.mY, i_rect.mWidth * m_cameraScale.mX, i_rect.mHeight * m_cameraScale.mY);
	m_graphics->DrawRect(rect);
}

void WorldMapCamera::FillRect(const Sexy::Rect& i_rect)
{
	Sexy::FPoint pos = TransformPointToCamera(i_rect.mX, i_rect.mY);
	Sexy::Rect rect(pos.mX, pos.mY, i_rect.mWidth * m_cameraScale.mX, i_rect.mHeight * m_cameraScale.mY);
	m_graphics->FillRect(rect);
}

void WorldMapCamera::FillPoly(Sexy::Point* i_vertexList, int i_numVertices, bool i_isConvex)
{
	for (int i = 0; i < i_numVertices; i++)
	{
		Sexy::FPoint point = TransformPointToCamera(i_vertexList[i].mX, i_vertexList[i].mY);
		i_vertexList[i].mX = point.mX;
		i_vertexList[i].mY = point.mY;
	}
	m_graphics->PolyFill(i_vertexList, i_numVertices, i_isConvex);
}

void WorldMapCamera::DrawImage(Sexy::Image* i_image, float i_posX, float i_posY, bool i_isMirrored, float i_width, float i_height)
{
	if (i_width < 0.0f)
		i_width = i_image->GetWidth();
	if (i_height < 0.0f)
		i_height = i_image->GetHeight();
	Sexy::FRect destRect(i_posX, i_posY, i_width, i_height);
	Sexy::Rect srcRect(0, 0, i_image->GetWidth(), i_image->GetHeight());
	DrawImage(i_image, srcRect, destRect, i_isMirrored);
}

void WorldMapCamera::DrawImageRotated(Sexy::Image* i_image, float i_posX, float i_posY, float i_rotationAngle, bool i_isMirrored, float i_width, float i_height)
{
	if (i_width < 0.0f)
		i_width = i_image->GetWidth();
	if (i_height < 0.0f)
		i_height = i_image->GetHeight();
	Sexy::FRect destRect(i_posX, i_posY, i_width, i_height);
	Sexy::Rect srcRect(0, 0, i_image->GetWidth(), i_image->GetHeight());
	DrawImageRotated(i_image, srcRect, destRect, i_rotationAngle, i_isMirrored);
}

void WorldMapCamera::DrawTexturedQuad(Sexy::Image* i_texture, Sexy::Point* i_vertexList, int i_numVertices)
{
	for (int i = 0; i < i_numVertices; i++)
	{
		Sexy::FPoint point = TransformPointToCamera(i_vertexList[i].mX, i_vertexList[i].mY);
		i_vertexList[i].mX = point.mX;
		i_vertexList[i].mY = point.mY;
	}
	Sexy::SexyVertex2D vertices[2][3] = {
		{ Sexy::SexyVertex2D(i_vertexList[0].mX, i_vertexList[0].mY, 0, 0), Sexy::SexyVertex2D(i_vertexList[1].mX, i_vertexList[1].mY, 1, 0), Sexy::SexyVertex2D(i_vertexList[2].mX, i_vertexList[2].mY, 1, 1) },
		{ Sexy::SexyVertex2D(i_vertexList[0].mX, i_vertexList[0].mY, 0, 0), Sexy::SexyVertex2D(i_vertexList[2].mX, i_vertexList[2].mY, 1, 1), Sexy::SexyVertex2D(i_vertexList[3].mX, i_vertexList[3].mY, 0, 1) }
	};
	m_graphics->DrawTrianglesTex(i_texture, vertices, 2);
}

void WorldMapCamera::DrawPopAnimRig(PopAnimRig* i_animRig, float i_posX, float i_posY, float i_scaleX, float i_scaleY, float i_rotation)
{
	Sexy::FPoint pos = TransformPointToCamera(i_posX, i_posY);

	if (m_useClipViewport)
	{
		const Sexy::PopAnim* pam = i_animRig->GetPAM();
		int width = pam->mAnimRect.mWidth * m_cameraScale.mX;
		int height = pam->mAnimRect.mHeight * m_cameraScale.mY;
		Sexy::Rect drawRect;
		drawRect.mX = (m_graphics->mTransX + pos.mX) - (float)(width / 2);
		drawRect.mY = (m_graphics->mTransY + pos.mY) - (float)(height / 2);
		drawRect.mWidth = width;
		drawRect.mHeight = height;
		if (!m_clipViewportRect.Intersects(drawRect))
			return;
	}

	Sexy::SexyTransform2D prevTransform = i_animRig->GetPAM()->mTransform;
	Sexy::SexyTransform2D transform = prevTransform;
	transform.RotateRad(i_rotation);
	transform.Scale(i_scaleX, i_scaleY);
	transform.Scale(m_cameraScale.mX, m_cameraScale.mY);
	transform.Translate(pos.mX, pos.mY);
	i_animRig->SetRenderTransform(transform);
	i_animRig->Draw(m_graphics);
	i_animRig->SetRenderTransform(prevTransform);
}
