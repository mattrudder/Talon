
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
	TALON_ALIGN(16, struct Matrix
	{
		Vector Rows[4];
	});
}

#include "Matrix.inl"

#if TALON_MATH == TALON_MATH_FPU
#include <Talon/Math/x87/Matrix.inl>
#elif TALON_MATH == TALON_MATH_SSE2
#include <Talon/Math/SSE/Matrix.inl>
#else
#error "Matrix not defined for this platform!"
#endif