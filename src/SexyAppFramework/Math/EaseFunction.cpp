//
//  EaseFunction.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "EaseFunction.h"

#pragma GCC optimize("fast-math")

namespace Sexy
{

/////////////// Lifecycle ///////////////

EaseFunction::EaseFunction()
{
	setup(1.0f, 1.0f, 0.5f, 0.5f);
}

EaseFunction::EaseFunction(float v0, float v1, float a, float b)
{
	setup(v0, v1, a, b);
}

/////////////// Evaluation ///////////////

void EaseFunction::setup(float v0, float v1, float a, float b)
{
	m_v0 = v0;
	m_v1 = v1;
	m_a = a;
	m_b = b;
	m_vc = ((b - 1) * v1 + 2 - a * v0) / (1 + b - a);

	float aFactor;
	float aArea;
	if (a == 0)
	{
		aArea = 0;
		aFactor = 0;
	}
	else
	{
		aFactor = (m_vc - v0) / (2 * a);
		aArea = aFactor * a;
	}
	m_afactor = aFactor;

	if (b == 1)
		m_bfactor = 0;
	else
		m_bfactor = (v1 - m_vc) / ((1 - b) + (1 - b));

	m_atotal = (aArea + v0) * a;
	m_btotal = m_atotal + (b - a) * m_vc;
}

float EaseFunction::operator()(float t) const
{
	if (t < m_a)
		return (m_v0 + m_afactor * t) * t;
	if (t < m_b)
		return m_atotal + (t - m_a) * m_vc;
	float dt = t - m_b;
	return m_btotal + dt * (m_vc + m_bfactor * dt);
}

float EaseFunction::operator()(float t, float tmax) const
{
	return (*this)(t / tmax);
}

float EaseFunction::operator()(float t, float tmin, float tmax) const
{
	return (*this)(t / (tmax - tmin));
}

}
