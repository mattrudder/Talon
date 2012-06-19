
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Math/Vector.h>

#if TALON_MATH==TALON_MATH_SSE2
#	if TALON_WINDOWS
#		include <xmmintrin.h>
#	endif
#endif

namespace Talon
{
	struct Matrix;

	// TODO: Support passing by value for systems that support it (e.g, Xbox 360)
	typedef const Matrix& MatrixArgL1;

	TALON_ALIGN(16, struct Matrix
	{
		Vector Rows[4];

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
}

#include "Matrix.inl"

#if TALON_MATH == TALON_MATH_FPU
#include <Talon/Math/x87/Matrix.inl>
#elif TALON_MATH == TALON_MATH_SSE2
#include <Talon/Math/SSE/Matrix.inl>
#else
#error "Matrix not defined for this platform!"
#endif