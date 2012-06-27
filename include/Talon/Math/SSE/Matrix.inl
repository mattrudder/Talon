
#pragma once

namespace Talon
{
	inline Matrix MatrixTranslation(float x, float y, float z)
	{
		Matrix m;
		m.r[0] = MatrixIdentityRow0;
		m.r[1] = MatrixIdentityRow1;
		m.r[2] = MatrixIdentityRow2;
		m.r[3] = Vector4Load(x, y, z, 1.0f);

		return m;
	}

	inline Matrix MatrixRotationX(float radians)
	{
		Matrix m;
		m.r[0] = MatrixIdentityRow0;

		__m128 vCos = _mm_set_ss(cosf(radians));
		__m128 vSin = _mm_set_ss(sinf(radians));

		// x = 0, y = cos, z = sin, w = 0
		vCos = _mm_shuffle_ps(vCos, vSin, _MM_SHUFFLE(3, 0, 0, 3));
		m.r[1] = vCos;

		// x = 0, y = -sin, z = cos, w = 0
		vCos = _mm_shuffle_ps(vCos, vCos, _MM_SHUFFLE(3, 1, 2, 0));
		vCos = _mm_mul_ps(vCos, VectorNegateY);
		m.r[2] = vCos;
		m.r[3] = MatrixIdentityRow3;

		return m;
	}

	inline Matrix MatrixRotationY(float radians)
	{
		Matrix m;
		m.r[1] = MatrixIdentityRow1;

		__m128 vCos = _mm_set_ss(cosf(radians));
		__m128 vSin = _mm_set_ss(sinf(radians));

		// x = sin, y = 0, z = cos, w = 0
		vCos = _mm_shuffle_ps(vSin, vCos, _MM_SHUFFLE(3, 0, 3, 0));
		m.r[2] = vCos;

		// x = cos, y = 0, z = -sin, w = 0
		vCos = _mm_shuffle_ps(vCos, vCos, _MM_SHUFFLE(3, 0, 1, 2));
		vCos = _mm_mul_ps(vCos, VectorNegateZ);
		m.r[0] = vCos;
		m.r[3] = MatrixIdentityRow3;

		return m;
	}

	inline Matrix MatrixRotationZ(float radians)
	{
		Matrix m;
		m.r[3] = MatrixIdentityRow3;
		m.r[2] = MatrixIdentityRow2;

		// x = cos, y = sin, z = 0, w = 0
		__m128 vCosSin = _mm_set_ps(0, 0, sinf(radians), cosf(radians));
		m.r[0] = vCosSin;

		// x = -sin, y = cos, z = 0, w = 0
		vCosSin = _mm_shuffle_ps(vCosSin, vCosSin, _MM_SHUFFLE(3, 2, 0, 1));
		vCosSin = _mm_mul_ps(vCosSin, VectorNegateX);
		m.r[1] = vCosSin;

		return m;
	}

	inline Matrix MatrixScale(float s)
	{
		Matrix m;
		m.r[0] = _mm_set_ps(0, 0, 0, s);
		m.r[1] = _mm_set_ps(0, 0, s, 0);
		m.r[2] = _mm_set_ps(0, s, 0, 0);
		m.r[3] = MatrixIdentityRow3;

		return m;
	}

	inline Matrix MatrixScale(float x, float y, float z)
	{
		Matrix m;
		m.r[0] = _mm_set_ps(0, 0, 0, x);
		m.r[1] = _mm_set_ps(0, 0, y, 0);
		m.r[2] = _mm_set_ps(0, z, 0, 0);
		m.r[3] = MatrixIdentityRow3;

		return m;
	}

	inline Matrix MatrixMultiply(MatrixArgL1 lhs, MatrixArgL1 rhs)
    {
        Matrix result;
        Vector vW = lhs.r[0];
        Vector vX = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(0, 0, 0, 0));
        Vector vY = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(1, 1, 1, 1));
        Vector vZ = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(3, 3, 3, 3));
        
        // Multiply first row.
        vX = _mm_mul_ps(vX, rhs.r[0]);
        vY = _mm_mul_ps(vY, rhs.r[1]);
        vZ = _mm_mul_ps(vZ, rhs.r[2]);
        vW = _mm_mul_ps(vW, rhs.r[3]);
        
        // Add to reduce errors
        vX = _mm_add_ps(vX, vZ);
        vY = _mm_add_ps(vY, vW);
        vX = _mm_add_ps(vX, vY);
        
        result.r[0] = vX;
        
        // Repeat for remaining rows
        vW = lhs.r[1];
        vX = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(0, 0, 0, 0));
        vY = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(1, 1, 1, 1));
        vZ = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(3, 3, 3, 3));
        vX = _mm_mul_ps(vX, rhs.r[0]);
        vY = _mm_mul_ps(vY, rhs.r[1]);
        vZ = _mm_mul_ps(vZ, rhs.r[2]);
        vW = _mm_mul_ps(vW, rhs.r[3]);
        vX = _mm_add_ps(vX, vZ);
        vY = _mm_add_ps(vY, vW);
        vX = _mm_add_ps(vX, vY);
        result.r[1] = vX;
        
        vW = lhs.r[2];
        vX = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(0, 0, 0, 0));
        vY = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(1, 1, 1, 1));
        vZ = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(3, 3, 3, 3));
        vX = _mm_mul_ps(vX, rhs.r[0]);
        vY = _mm_mul_ps(vY, rhs.r[1]);
        vZ = _mm_mul_ps(vZ, rhs.r[2]);
        vW = _mm_mul_ps(vW, rhs.r[3]);
        vX = _mm_add_ps(vX, vZ);
        vY = _mm_add_ps(vY, vW);
        vX = _mm_add_ps(vX, vY);
        result.r[2] = vX;
        
        vW = lhs.r[3];
        vX = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(0, 0, 0, 0));
        vY = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(1, 1, 1, 1));
        vZ = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = _mm_shuffle_ps(vW, vW, _MM_SHUFFLE(3, 3, 3, 3));
        vX = _mm_mul_ps(vX, rhs.r[0]);
        vY = _mm_mul_ps(vY, rhs.r[1]);
        vZ = _mm_mul_ps(vZ, rhs.r[2]);
        vW = _mm_mul_ps(vW, rhs.r[3]);
        vX = _mm_add_ps(vX, vZ);
        vY = _mm_add_ps(vY, vW);
        vX = _mm_add_ps(vX, vY);
        result.r[3] = vX;
        
        return result;
    }
}