
#pragma once

#include <Talon/TalonMath.h>
#include <Talon/Math/Vector.h>

namespace Talon
{
	inline float ToRadians(float degrees) { return degrees * (Pi / 180.0f); }
	inline float ToDegrees(float radians) { return radians * (180.0f / Pi); }

	inline Vector Vector4Load(const float4* v);
	inline Vector Vector4Load(float x, float y, float z, float w);

	inline Vector Vector2Load(const float2* v);
	inline Vector Vector2Load(float x, float y);

	inline void StoreFloat4(float4* pDest, VectorArgL1 V);
	inline void StoreFloat3(float3* pDest, VectorArgL1 V);
	inline void StoreFloat2(float2* pDest, VectorArgL1 V);
}

#if TALON_MATH == TALON_MATH_FPU
#include <Talon/Math/x87/Conversions.inl>
#elif TALON_MATH == TALON_MATH_SSE2
#include <Talon/Math/SSE/Conversions.inl>
#else
#error "Math Conversions not defined for this platform!"
#endif