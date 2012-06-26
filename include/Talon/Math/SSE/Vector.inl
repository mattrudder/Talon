
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

	inline float Vector2Dot(VectorArgL1 v1, VectorArgL1 v2)
	{
		Vector vLengthSq = _mm_mul_ps(v1, v2);
		Vector vTemp = _mm_shuffle_ps(vLengthSq, vLengthSq, _MM_SHUFFLE(1,1,1,1));

		// x + y
		vLengthSq = _mm_add_ss(vLengthSq, vTemp);

		float r;
		_mm_store_ss(&r, vLengthSq);
		return r;
	}

	inline float Vector3Dot(VectorArgL1 v1, VectorArgL1 v2)
	{
		// Perform the dot product
		Vector vDot = _mm_mul_ps(v1, v2);

		// x=Dot.vector4_f32[1], y=Dot.vector4_f32[2]
		Vector vTemp = _mm_shuffle_ps(vDot, vDot, _MM_SHUFFLE(2,1,2,1));
		// Result.vector4_f32[0] = x+y
		vDot = _mm_add_ss(vDot, vTemp);
		// x=Dot.vector4_f32[2]
		vTemp = _mm_shuffle_ps(vTemp, vTemp, _MM_SHUFFLE(1,1,1,1));
		// Result.vector4_f32[0] = (x+y)+z
		vDot = _mm_add_ss(vDot, vTemp);

		float r;
		_mm_store_ss(&r, vDot);
		return r;
	}

	inline float Vector4Dot(VectorArgL1 v1, VectorArgL1 v2)
	{
		Vector vTemp2 = v2;
		Vector vTemp = _mm_mul_ps(v1,vTemp2);
		vTemp2 = _mm_shuffle_ps(vTemp2, vTemp, _MM_SHUFFLE(1,0,0,0)); // Copy X to the Z position and Y to the W position
		vTemp2 = _mm_add_ps(vTemp2, vTemp);          // Add Z = X+Z; W = Y+W;
		vTemp = _mm_shuffle_ps(vTemp, vTemp2, _MM_SHUFFLE(0,3,0,0));  // Copy W to the Z position
		vTemp = _mm_add_ps(vTemp, vTemp2);           // Add Z and W together
		vTemp = _mm_shuffle_ps(vTemp, vTemp, _MM_SHUFFLE(2,2,2,2));

		float r;
		_mm_store_ss(&r, vTemp);
		return r;
	}
}