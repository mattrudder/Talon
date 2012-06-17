
#pragma once
#include <Talon/TalonPublic.h>

#if TALON_MATH==TALON_MATH_SSE2
#	if TALON_WINDOWS
#		include <xmmintrin.h>
#	endif
namespace Talon
{
#	if TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_VS
	typedef __m128 Vector;

	typedef const Vector VectorArgL1;
	typedef const Vector VectorArgL2;
	typedef const Vector& VectorArgLX;
#	endif
}
#endif

namespace Talon
{
	Vector VectorNegate(VectorArgL1 v);
	Vector VectorAdd(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorSubtract(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorMultiply(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorDivide(VectorArgL1 v1, VectorArgL1 v2);
	Vector VectorScale(VectorArgL1 v, float scale);

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
}

#include "Vector.inl"

#if TALON_MATH == TALON_MATH_SSE2
#include <Talon/Math/SSE/Vector.inl>
#endif