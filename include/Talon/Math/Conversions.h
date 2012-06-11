
#pragma once

#include <Talon/TalonMath.h>
#include <Talon/Math/Vector.h>

namespace Talon
{
	inline float ToRadians(float degrees) { return degrees * (Pi / 180.0f); }
	inline float ToDegrees(float radians) { return radians * (180.0f / Pi); }

#if TALON_MATH == TALON_MATH_SSE2
	inline Vector Vector4Load(const float4& v) { return Simd::Load(v.x, v.y, v.z, v.w); }
	inline Vector Vector4Load(float x, float y, float z, float w) { return Simd::Load(x, y, z, w); }

	inline Vector Vector2Load(const float2& v) { return Simd::Load(v.x, v.y); }
	inline Vector Vector2Load(float x, float y) { return Simd::Load(x, y); }

	inline void StoreFloat4(float4* pDest, VectorArgL1 V) { Simd::Store(pDest, V); }
	inline void StoreFloat3(float3* pDest, VectorArgL1 V) { Simd::Store(pDest, V); }
	inline void StoreFloat2(float2* pDest, VectorArgL1 V) { Simd::Store(pDest, V); }
#endif
}