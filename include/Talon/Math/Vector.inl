
#pragma once

namespace Talon
{
	inline Vector VectorNegate(VectorArgL1 v)
	{

	}

	inline Vector VectorAdd(VectorArgL1 v1, VectorArgL1 v2)
	{

	}

	inline Vector VectorSubtract(VectorArgL1 v1, VectorArgL1 v2)
	{

	}

	inline Vector VectorMultiply(VectorArgL1 v1, VectorArgL1 v2)
	{

	}

	inline Vector VectorDivide(VectorArgL1 v1, VectorArgL1 v2)
	{

	}

	inline Vector VectorScale(VectorArgL1 v, float scale)
	{

	}

	inline Vector operator+ (VectorArgL1 v)
	{
		return V;
	}

	inline Vector operator- (VectorArgL1 v)
	{
		return VectorNegate(V);
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