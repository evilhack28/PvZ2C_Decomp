//
//  AndroidGL20Vertex.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-26.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/drivers/graphics/android/AndroidGL20Vertex.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

AndroidGL20Vertex::AndroidGL20Vertex()
{
}

AndroidGL20Vertex::AndroidGL20Vertex(float theX, float theY, float theZ, float theU, float theV, uint32 theColor)
{
	x = theX;
	y = theY;
	z = theZ;
	u = theU;
	v = theV;
	color = theColor;
}

/////////////// Accessors ///////////////

float AndroidGL20Vertex::GetCoord(const AndroidGL20Vertex& theVertex, int theCoord)
{
	switch (theCoord)
	{
		case 0: return theVertex.x;
		case 1: return theVertex.y;
		case 2: return theVertex.z;
		case 3: return theVertex.u;
		case 4: return theVertex.v;
		default: return 0;
	}
}

void AndroidGL20Vertex::SetPosition(float theX, float theY, float theZ)
{
	x = theX;
	y = theY;
	z = theZ;
}

uint32 AndroidGL20Vertex::TexCoordOffset()
{
	return 24;
}

/////////////// Color ///////////////

uint32 AndroidGL20Vertex::PackColor(int theRed, int theGreen, int theBlue, int theAlpha)
{
	return (theAlpha << 24) | ((theBlue & 0xFF) << 16) | ((theGreen & 0xFF) << 8) | (theRed & 0xFF);
}

AndroidGL20Vertex AndroidGL20Vertex::Interpolate(const AndroidGL20Vertex& v1, const AndroidGL20Vertex& v2, float t)
{
	AndroidGL20Vertex aVertex = v1;
	float dx = v2.x - v1.x;
	aVertex.x = v1.x + t * dx;
	aVertex.y = v1.y + t * (v2.y - v1.y);
	aVertex.u = v1.u + t * (v2.u - v1.u);
	aVertex.v = v1.v + t * (v2.v - v1.v);
	if (v1.color != v2.color)
	{
		int32 Pct = (uint32)(t * 255.0f);
		Pct = (Pct < 0) ? 0 : (Pct > 255) ? 255 : Pct;

		int32 InvPct = 255 - Pct;
		aVertex.color = (((((v1.color & 0xFF000000) >> 24) * InvPct) + (((v2.color & 0xFF000000) >> 24) * Pct) << 16) & 0xFF000000) |
						(((((v1.color & 0x00FF0000) >> 16) * InvPct) + (((v2.color & 0x00FF0000) >> 16) * Pct) <<  8) & 0x00FF0000) |
						(((((v1.color & 0x0000FF00) >>  8) * InvPct) + (((v2.color & 0x0000FF00) >>  8) * Pct)      ) & 0x0000FF00) |
						(((((v1.color & 0x000000FF) >>  0) * InvPct) + (((v2.color & 0x000000FF) >>  0) * Pct) >>  8) & 0x000000FF);
	}
	return aVertex;
}
