
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Math/Vector.h>
#include <Talon/Math/Conversions.h>

#if TALON_MATH==TALON_MATH_SSE2
#	include <xmmintrin.h>
#endif

namespace Talon
{
	struct Matrix;

	// TODO: Support passing by value for systems that support it (e.g, Xbox 360)
	typedef const Matrix& MatrixArgL1;

	TALON_ALIGN(16, struct TalonApi Matrix
	{
		Vector r[4];

		Matrix() {}
		Matrix(VectorArgL1 r0, VectorArgL1 r1, VectorArgL1 r2, VectorArgL2 r3) { r[0] = r0; r[1] = r1; r[2] = r2; r[3] = r3; }
		Matrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		explicit Matrix(const float *pArray);

		Matrix& operator= (const Matrix& m) { r[0] = m.r[0]; r[1] = m.r[1]; r[2] = m.r[2]; r[3] = m.r[3]; return *this; }
			    
		Matrix operator+ () const { return *this; }
		Matrix operator- () const;
			    
		Matrix& operator+= (MatrixArgL1 m);
		Matrix& operator-= (MatrixArgL1 m);
		Matrix& operator*= (MatrixArgL1 m);
		Matrix& operator*= (float s);
		Matrix& operator/= (float s);
			    
		Matrix operator+ (MatrixArgL1 m) const;
		Matrix operator- (MatrixArgL1 m) const;
		Matrix operator* (MatrixArgL1 m) const;
		Matrix operator* (float s) const;
		Matrix operator/ (float s) const;

		friend Matrix operator* (float s, MatrixArgL1 m);
	});

	// TODO: Matrix free functions
	Matrix MatrixMultiply(MatrixArgL1 lhs, MatrixArgL1 rhs);
}

#if BUILDING_TALON
#include "Matrix.inl"

#if TALON_MATH == TALON_MATH_FPU
#include <Talon/Math/x87/Matrix.inl>
#elif TALON_MATH == TALON_MATH_SSE2
#include <Talon/Math/SSE/Matrix.inl>
#else
#error "Matrix not defined for this platform!"
#endif
#endif