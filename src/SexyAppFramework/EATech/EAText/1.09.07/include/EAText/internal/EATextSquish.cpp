//
//  EATextSquish.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include <EAText/internal/EATextSquish.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <EASTL/algorithm.h>
#include "SexyVector.h"

namespace EATextSquish
{

class Vec3 : public Sexy::SexyVector3
{
public:
	Vec3() {}
	explicit Vec3(float v);
	Vec3(float X, float Y, float Z) : Sexy::SexyVector3(X, Y, Z) {}
	Vec3& operator+=(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3& operator*=(const Vec3& v);
	Vec3& operator*=(float t);
	Vec3& operator/=(float t);
};

class Sym3x3
{
public:
	float m_x[6];
	explicit Sym3x3(float s);
	float& operator[](int index);
};

class ColorSet
{
public:
	int m_count;
	char m_pad[0x144];
	ColorSet(const uint8_t* rgba, uint32_t w, uint32_t h);
};

int GetColorCount(int count);

class ClusterFit
{
public:
	char m_pad[0x2c0];
	ClusterFit(const ColorSet* colours);
	void Compress4(void* block);
};

struct SourceBlock
{
	uint8_t start;
	uint8_t end;
	uint8_t error;
};

struct SingleColourLookup
{
	SourceBlock sources[4];
};

class SingleColourFit
{
public:
	void* m_vptr;
	const ColorSet* m_colours;
	char m_pad0[4];
	uint8_t m_colour[3];
	Vec3 m_start;
	Vec3 m_end;
	uint8_t m_index;
	int m_besterror;
	int m_error;
	char m_pad[0x2c0 - 0x3c];
	SingleColourFit(const ColorSet* colours);
	void Compress4(void* block);
	void ComputeEndPoints(int count, const SingleColourLookup* const* lookups);
};

Vec3 operator*(float left, const Vec3& right);
Vec3 operator-(const Vec3& left, const Vec3& right);
Sym3x3 ComputeWeightedCovariance(int n, const Vec3* points, const float* weights);
float Dot(const Vec3& left, const Vec3& right);
Vec3 Min(const Vec3& left, const Vec3& right);
Vec3 Max(const Vec3& left, const Vec3& right);
Vec3 Floor(const Vec3& v);

Vec3& Vec3::operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
Vec3& Vec3::operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Vec3& Vec3::operator*=(const Vec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
Vec3& Vec3::operator*=(float t) { x *= t; y *= t; z *= t; return *this; }
Vec3& Vec3::operator/=(float t) { float s = 1.0f / t; x *= s; y *= s; z *= s; return *this; }
float Dot(const Vec3& left, const Vec3& right) { return right.x * left.x + right.y * left.y + right.z * left.z; }
float& Sym3x3::operator[](int index) { return m_x[index]; }
Vec3 Min(const Vec3& left, const Vec3& right) { return Vec3(std::min(left.x, right.x), std::min(left.y, right.y), std::min(left.z, right.z)); }
Vec3 Max(const Vec3& left, const Vec3& right) { return Vec3(std::max(left.x, right.x), std::max(left.y, right.y), std::max(left.z, right.z)); }
Vec3 Floor(const Vec3& v) { return Vec3(floorf(v.x), floorf(v.y), floorf(v.z)); }

void SingleColourFit::ComputeEndPoints(int count, const SingleColourLookup* const* lookups)
{
	m_besterror = 0x7fffffff;
	for (int index = 0; index < count; ++index)
	{
		const SourceBlock& s0 = lookups[0][m_colour[0]].sources[index];
		const SourceBlock& s1 = lookups[1][m_colour[1]].sources[index];
		const SourceBlock& s2 = lookups[2][m_colour[2]].sources[index];
		int error = s0.error * s0.error + s1.error * s1.error + s2.error * s2.error;
		if (error < m_besterror)
		{
			m_start = Vec3(s0.start * (1.0f / 31.0f), s1.start * (1.0f / 63.0f), s2.start * (1.0f / 31.0f));
			m_end = Vec3(s0.end * (1.0f / 31.0f), s1.end * (1.0f / 63.0f), s2.end * (1.0f / 31.0f));
			m_index = (uint8_t)index;
			m_besterror = error;
		}
	}
}

static float X(float x) { return x; }
static float Y(float y) { return y; }
static float Z(float z) { return z; }

Sym3x3 ComputeWeightedCovariance(int n, const Vec3* points, const float* weights)
{
	float total = 0.0f;
	Vec3 centroid(0.0f);
	for (int i = 0; i < n; ++i)
	{
		total += weights[i];
		centroid += weights[i] * points[i];
	}
	centroid /= total;

	Sym3x3 covariance(0.0f);
	for (int i = 0; i < n; ++i)
	{
		Vec3 a = points[i] - centroid;
		Vec3 b = weights[i] * a;
		covariance[0] += X(a.x) * X(b.x);
		covariance[1] += X(a.x) * Y(b.y);
		covariance[2] += X(a.x) * Z(b.z);
		covariance[3] += Y(a.y) * Y(b.y);
		covariance[4] += Y(a.y) * Z(b.z);
		covariance[5] += Z(a.z) * Z(b.z);
	}
	return covariance;
}


static int FloatToInt(float a, int limit)
{
	int i = (int)(a + 0.5f);
	if (i < 0) i = 0;
	else if (i > limit) i = limit;
	return i;
}

static int FloatTo565(const Vec3& colour)
{
	int r = FloatToInt(31.0f * colour.x, 31);
	int g = FloatToInt(63.0f * colour.y, 63);
	int b = FloatToInt(31.0f * colour.z, 31);
	return (r << 11) | (g << 5) | b;
}

static void WriteColourBlock(int a, int b, const uint8_t* indices, void* block)
{
	uint8_t* bytes = (uint8_t*)block;
	bytes[0] = (uint8_t)(a & 0xff);
	bytes[1] = (uint8_t)(a >> 8);
	bytes[2] = (uint8_t)(b & 0xff);
	bytes[3] = (uint8_t)(b >> 8);
	for (int i = 0; i < 4; ++i)
	{
		const uint8_t* ind = indices + 4 * i;
		bytes[4 + i] = ind[0] | (ind[1] << 2) | (ind[2] << 4) | (ind[3] << 6);
	}
}

void WriteColourBlock4(const Vec3& start, const Vec3& end, const uint8_t* indices, void* block)
{
	int a = FloatTo565(start);
	int b = FloatTo565(end);
	uint8_t remapped[16];
	if (a < b)
	{
		eastl::swap(a, b);
		for (int i = 0; i < 16; ++i)
			remapped[i] = (indices[i] ^ 0x1) & 0x3;
	}
	else if (a == b)
	{
		for (int i = 0; i < 16; ++i)
			remapped[i] = 0;
	}
	else
	{
		for (int i = 0; i < 16; ++i)
			remapped[i] = indices[i];
	}
	WriteColourBlock(a, b, remapped, block);
}

}

namespace EATextSquish
{
	void Compress(const uint8_t* pSourceARGB, void* pDestination, uint32_t nSourceStride, uint32_t nImageSize)
	{
		void* block = (uint8_t*)pDestination + 8;
		ColorSet colours(pSourceARGB, nSourceStride, nImageSize);
		if (GetColorCount(colours.m_count) == 1)
		{
			SingleColourFit fit(&colours);
			fit.Compress4(block);
		}
		else
		{
			ClusterFit fit(&colours);
			fit.Compress4(block);
		}
	}

}
