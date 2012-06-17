
#pragma once

namespace Talon
{
	inline Vector VectorNegate(VectorArgL1 v)
	{
		Vector zero = _mm_setzero_ps();
		return _mm_sub_ps(zero, v);
	}

	inline Vector VectorAdd(VectorArgL1 v1, VectorArgL1 v2)
	{
		return _mm_add_ps(v1, v2);
	}

	inline Vector VectorSubtract(VectorArgL1 v1, VectorArgL1 v2)
	{
		return _mm_sub_ps(v1, v2);
	}

	inline Vector VectorMultiply(VectorArgL1 v1, VectorArgL1 v2)
	{
		return _mm_mul_ps(v1, v2);
	}

	inline Vector VectorDivide(VectorArgL1 v1, VectorArgL1 v2)
	{
		return _mm_div_ps(v1, v2);
	}

	inline Vector VectorScale(VectorArgL1 v, float scale)
	{
		Vector s = _mm_set_ps1(scale);
		return _mm_mul_ps(s, v);
	}
}