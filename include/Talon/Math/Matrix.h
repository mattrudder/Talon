
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

#if TALON_MATH == TALON_MATH_SSE2
#include <Talon/Math/SSE/Matrix.inl>
#endif