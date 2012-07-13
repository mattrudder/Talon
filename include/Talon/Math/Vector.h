
#pragma once
#include <Talon/TalonPublic.h>
#include "Constants.h"

#if TALON_MATH == TALON_MATH_FPU
namespace Talon
{
	TALON_ALIGN(16, struct Vector
	{
		union
		{
			float data_f32[4];
			u32 data_u32[4];
		};
	});
}
#elif TALON_MATH==TALON_MATH_SSE2
#	include <xmmintrin.h>
namespace Talon
{
	typedef __m128 Vector;
}
#endif

namespace Talon
{
	// TODO: support differences between
	typedef const Vector VectorArgL1;
	typedef const Vector& VectorArgL2;
	typedef const Vector& VectorArgLX;
	
	Vector VectorAnd(VectorArgL1 v1, VectorArgL1 v2);

	Vector VectorSplatX(VectorArgL1 v);
	Vector VectorSplatY(VectorArgL1 v);
	Vector VectorSplatZ(VectorArgL1 v);
	Vector VectorSplatW(VectorArgL1 v);

	Vector VectorNegate(VectorArgL1 v);
	Vector VectorAdd(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorSubtract(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorMultiply(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorDivide(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorScale(VectorArgL1 v, float scale);

	Vector VectorLerp(VectorArgL1 v1, VectorArgL1 v2, float scale);

	float Vector2Dot(VectorArgL1 v1, VectorArgL1 v2);

	Vector Vector3Cross(VectorArgL1 v1, VectorArgL1 v2);
	float Vector3Dot(VectorArgL1 v1, VectorArgL1 v2);

	float Vector4Dot(VectorArgL1 v1, VectorArgL1 v2);

    // GCC/Clang already implement these.
#if TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_VS
	Vector operator+ (VectorArgL1 V);
	Vector operator- (VectorArgL1 V);
	Vector& operator+= (Vector& V1, VectorArgL1 V2);
	Vector& operator-= (Vector& V1, VectorArgL1 V2);
	Vector& operator*= (Vector& V1, VectorArgL1 V2);
	Vector& operator/= (Vector& V1, VectorArgL1 V2);
	Vector& operator*= (Vector& V, float S);
	Vector& operator/= (Vector& V, float S);
	Vector operator+ (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator- (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator* (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator/ (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator* (VectorArgL1 V, float S);
	Vector operator* (float S, VectorArgL1 V);
	Vector operator/ (VectorArgL1 V, float S);
#endif
}

#include "Vector.inl"

#if TALON_MATH == TALON_MATH_FPU
#include <Talon/Math/x87/Vector.inl>
#elif TALON_MATH == TALON_MATH_SSE2
#include <Talon/Math/SSE/Vector.inl>
#else
#error "Vector not defined on this platform!"
#endif