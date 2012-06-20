
#pragma once

namespace Talon
{
	Matrix::Matrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		r[0] = Vector4Load(m00, m01, m02, m03);
		r[1] = Vector4Load(m10, m11, m12, m13);
		r[2] = Vector4Load(m20, m21, m22, m23);
		r[3] = Vector4Load(m30, m31, m32, m33);
	}

	Matrix::Matrix(const float *pArray)
	{
		r[0] = Vector4Load((const float4 *)pArray);
		r[0] = Vector4Load((const float4 *)pArray + 4);
		r[0] = Vector4Load((const float4 *)pArray + 8);
		r[0] = Vector4Load((const float4 *)pArray + 12);
	}

	Matrix Matrix::operator- () const
	{
		Matrix result;
		result.r[0] = VectorNegate(r[0]);
		result.r[1] = VectorNegate(r[1]);
		result.r[2] = VectorNegate(r[2]);
		result.r[3] = VectorNegate(r[3]);

		return result;
	}

	Matrix& Matrix::operator+= (MatrixArgL1 m)
	{
		r[0] = VectorAdd(r[0], m.r[0]);
		r[1] = VectorAdd(r[1], m.r[1]);
		r[2] = VectorAdd(r[2], m.r[2]);
		r[3] = VectorAdd(r[3], m.r[3]);

		return *this;
	}

	Matrix& Matrix::operator-= (MatrixArgL1 m)
	{
		r[0] = VectorSubtract(r[0], m.r[0]);
		r[1] = VectorSubtract(r[1], m.r[1]);
		r[2] = VectorSubtract(r[2], m.r[2]);
		r[3] = VectorSubtract(r[3], m.r[3]);

		return *this;
	}

	Matrix& Matrix::operator*= (MatrixArgL1 m)
	{
		*this = MatrixMultiply(*this, m);
		return *this;
	}

	Matrix& Matrix::operator*= (float s)
	{
		r[0] = VectorScale(r[0], s);
		r[1] = VectorScale(r[1], s);
		r[2] = VectorScale(r[2], s);
		r[3] = VectorScale(r[3], s);

		return *this;
	}

	Matrix& Matrix::operator/= (float s)
	{
		TALON_ASSERT(s != 0);
		float t = 1.0f / s;
		r[0] = VectorScale(r[0], t);
		r[1] = VectorScale(r[1], t);
		r[2] = VectorScale(r[2], t);
		r[3] = VectorScale(r[3], t);

		return *this;
	}

	Matrix Matrix::operator+ (MatrixArgL1 m) const
	{
		Matrix result;
		result.r[0] = VectorAdd(r[0], m.r[0]);
		result.r[1] = VectorAdd(r[1], m.r[1]);
		result.r[2] = VectorAdd(r[2], m.r[2]);
		result.r[3] = VectorAdd(r[3], m.r[3]);

		return result;
	}

	Matrix Matrix::operator- (MatrixArgL1 m) const
	{
		Matrix result;
		result.r[0] = VectorSubtract(r[0], m.r[0]);
		result.r[1] = VectorSubtract(r[1], m.r[1]);
		result.r[2] = VectorSubtract(r[2], m.r[2]);
		result.r[3] = VectorSubtract(r[3], m.r[3]);

		return result;
	}

	Matrix Matrix::operator* (MatrixArgL1 m) const
	{
		return MatrixMultiply(*this, m);
	}

	Matrix Matrix::operator* (float s) const
	{
		Matrix result;
		result.r[0] = VectorScale(r[0], s);
		result.r[1] = VectorScale(r[1], s);
		result.r[2] = VectorScale(r[2], s);
		result.r[3] = VectorScale(r[3], s);

		return result;
	}

	Matrix Matrix::operator/ (float s) const
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

	Matrix operator* (float s, MatrixArgL1 m)
	{
		Matrix result;
		result.r[0] = VectorScale(m.r[0], s);
		result.r[1] = VectorScale(m.r[1], s);
		result.r[2] = VectorScale(m.r[2], s);
		result.r[3] = VectorScale(m.r[3], s);

		return result;
	}
}