
#pragma once

namespace Talon
{
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