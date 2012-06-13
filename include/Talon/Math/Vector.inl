
#pragma once

namespace Talon
{
	inline Vector VectorNegate(VectorArgL1 v)
	{
#if TALON_MATH == TALON_MATH_SSE2
		Vector zero = _mm_setzero_ps();
		return _mm_sub_ps(zero, v);
#endif
	}

	inline Vector VectorAdd(VectorArgL1 v1, VectorArgL1 v2)
	{
#if TALON_MATH == TALON_MATH_SSE2
		return _mm_add_ps(v1, v2);
#endif
	}

	inline Vector VectorSubtract(VectorArgL1 v1, VectorArgL1 v2)
	{
#if TALON_MATH == TALON_MATH_SSE2
		return _mm_sub_ps(v1, v2);
#endif
	}

	inline Vector VectorMultiply(VectorArgL1 v1, VectorArgL1 v2)
	{
#if TALON_MATH == TALON_MATH_SSE2
		return _mm_mul_ps(v1, v2);
#endif
	}

	inline Vector VectorDivide(VectorArgL1 v1, VectorArgL1 v2)
	{
#if TALON_MATH == TALON_MATH_SSE2
		return _mm_div_ps(v1, v2);
#endif
	}

	inline Vector VectorScale(VectorArgL1 v, float scale)
	{
#if TALON_MATH == TALON_MATH_SSE2
		Vector s = _mm_set_ps1(scale);
		return _mm_mul_ps(s, v);
#endif
	}

	inline Vector operator+ (VectorArgL1 v)
	{
		return v;
	}

	inline Vector operator- (VectorArgL1 v)
	{
		return VectorNegate(v);
	}

	inline Vector& operator+= (Vector& v1, VectorArgL1 v2)
	{
		v1 = VectorAdd(v1, v2);
		return v1;
	}

	inline Vector& operator-= (Vector& v1, VectorArgL1 v2)
	{
		v1 = VectorSubtract(v1, v2);
		return v1;
	}

	inline Vector& operator*= (Vector& v1, VectorArgL1 v2)
	{
		v1 = VectorMultiply(v1, v2);
		return v1;
	}

	inline Vector& operator/= (Vector& v1, VectorArgL1 v2)
	{
		v1 = VectorDivide(v1, v2);
		return v1;
	}

	inline Vector& operator*= (Vector& v, float s)
	{
		v = VectorScale(v, s);
		return v;
	}

	inline Vector& operator/= (Vector& v, float s)
	{
		TALON_ASSERT(s != 0.0f);
		v = VectorScale(v, 1 / s);
		return v;
	}

	inline Vector operator+ (VectorArgL1 v1, VectorArgL1 v2)
	{
		return VectorAdd(v1, v2);
	}

	inline Vector operator- (VectorArgL1 v1, VectorArgL1 v2)
	{
		return VectorSubtract(v1, v2);
	}

	inline Vector operator* (VectorArgL1 v1, VectorArgL1 v2)
	{
		return VectorMultiply(v1, v2);
	}

	inline Vector operator/ (VectorArgL1 v1, VectorArgL1 v2)
	{
		return VectorDivide(v1, v2);
	}

	inline Vector operator* (VectorArgL1 v, float s)
	{
		return VectorScale(v, s);
	}

	inline Vector operator* (float s, VectorArgL1 v)
	{
		return VectorScale(v, s);
	}

	inline Vector operator/ (VectorArgL1 v, float s)
	{
		TALON_ASSERT(s != 0);
		return VectorScale(v, s);
	}
}