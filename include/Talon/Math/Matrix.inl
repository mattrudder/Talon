
#pragma once

namespace Talon
{
	inline Matrix::Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		r[0] = Vector4Load(m00, m01, m02, m03);
		r[1] = Vector4Load(m10, m11, m12, m13);
		r[2] = Vector4Load(m20, m21, m22, m23);
		r[3] = Vector4Load(m30, m31, m32, m33);
	}

	inline Matrix::Matrix(const float *pArray)
	{
		r[0] = Vector4Load((const float4 *)pArray);
		r[0] = Vector4Load((const float4 *)pArray + 4);
		r[0] = Vector4Load((const float4 *)pArray + 8);
		r[0] = Vector4Load((const float4 *)pArray + 12);
	}

	inline Matrix Matrix::operator- () const
	{
		Matrix result;
		result.r[0] = VectorNegate(r[0]);
		result.r[1] = VectorNegate(r[1]);
		result.r[2] = VectorNegate(r[2]);
		result.r[3] = VectorNegate(r[3]);

		return result;
	}

	inline Matrix& Matrix::operator+= (MatrixArgL1 m)
	{
		r[0] = VectorAdd(r[0], m.r[0]);
		r[1] = VectorAdd(r[1], m.r[1]);
		r[2] = VectorAdd(r[2], m.r[2]);
		r[3] = VectorAdd(r[3], m.r[3]);

		return *this;
	}

	inline Matrix& Matrix::operator-= (MatrixArgL1 m)
	{
		r[0] = VectorSubtract(r[0], m.r[0]);
		r[1] = VectorSubtract(r[1], m.r[1]);
		r[2] = VectorSubtract(r[2], m.r[2]);
		r[3] = VectorSubtract(r[3], m.r[3]);

		return *this;
	}

	inline Matrix& Matrix::operator*= (MatrixArgL1 m)
	{
		*this = MatrixMultiply(*this, m);
		return *this;
	}

	inline Matrix& Matrix::operator*= (float s)
	{
		r[0] = VectorScale(r[0], s);
		r[1] = VectorScale(r[1], s);
		r[2] = VectorScale(r[2], s);
		r[3] = VectorScale(r[3], s);

		return *this;
	}

	inline Matrix& Matrix::operator/= (float s)
	{
		TALON_ASSERT(s != 0);
		float t = 1.0f / s;
		r[0] = VectorScale(r[0], t);
		r[1] = VectorScale(r[1], t);
		r[2] = VectorScale(r[2], t);
		r[3] = VectorScale(r[3], t);

		return *this;
	}

	inline Matrix Matrix::operator+ (MatrixArgL1 m) const
	{
		Matrix result;
		result.r[0] = VectorAdd(r[0], m.r[0]);
		result.r[1] = VectorAdd(r[1], m.r[1]);
		result.r[2] = VectorAdd(r[2], m.r[2]);
		result.r[3] = VectorAdd(r[3], m.r[3]);

		return result;
	}

	inline Matrix Matrix::operator- (MatrixArgL1 m) const
	{
		Matrix result;
		result.r[0] = VectorSubtract(r[0], m.r[0]);
		result.r[1] = VectorSubtract(r[1], m.r[1]);
		result.r[2] = VectorSubtract(r[2], m.r[2]);
		result.r[3] = VectorSubtract(r[3], m.r[3]);

		return result;
	}

	inline Matrix Matrix::operator* (MatrixArgL1 m) const
	{
		return MatrixMultiply(*this, m);
	}

	inline Matrix Matrix::operator* (float s) const
	{
		Matrix result;
		result.r[0] = VectorScale(r[0], s);
		result.r[1] = VectorScale(r[1], s);
		result.r[2] = VectorScale(r[2], s);
		result.r[3] = VectorScale(r[3], s);

		return result;
	}

	inline Matrix Matrix::operator/ (float s) const
	{
		TALON_ASSERT(s != 0.0f);
		float t = 1.0f / s;
		Matrix result;
		result.r[0] = VectorScale(r[0], t);
		result.r[1] = VectorScale(r[1], t);
		result.r[2] = VectorScale(r[2], t);
		result.r[3] = VectorScale(r[3], t);

		return result;
	}

	inline Matrix operator* (float s, MatrixArgL1 m)
	{
		Matrix result;
		result.r[0] = VectorScale(m.r[0], s);
		result.r[1] = VectorScale(m.r[1], s);
		result.r[2] = VectorScale(m.r[2], s);
		result.r[3] = VectorScale(m.r[3], s);

		return result;
	}

	inline bool MatrixIsIdentity(MatrixArgL1 m)
	{
		__m128 vTemp1 = _mm_cmpeq_ps(m.r[0], MatrixIdentityRow0);
		__m128 vTemp2 = _mm_cmpeq_ps(m.r[1], MatrixIdentityRow1);
		__m128 vTemp3 = _mm_cmpeq_ps(m.r[2], MatrixIdentityRow2);
		__m128 vTemp4 = _mm_cmpeq_ps(m.r[3], MatrixIdentityRow3);
		vTemp1 = _mm_and_ps(vTemp1, vTemp2);
		vTemp3 = _mm_and_ps(vTemp3, vTemp4);
		vTemp1 = _mm_and_ps(vTemp1, vTemp3);

		return _mm_movemask_ps(vTemp1) == 0x0F;
	}

	inline Matrix MatrixIdentity()
	{
		Matrix m;
		m.r[0] = MatrixIdentityRow0.v;
		m.r[1] = MatrixIdentityRow1.v;
		m.r[2] = MatrixIdentityRow2.v;
		m.r[3] = MatrixIdentityRow3.v;

		return m;
	}
}