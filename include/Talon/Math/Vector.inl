
#pragma once

namespace Talon
{
// GCC/Clang already implement these
#if TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_VS
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
#endif
}