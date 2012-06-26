
#pragma once

#include <Talon/TalonPublic.h>
#if TALON_MATH_SSE2
#	include <emmintrin.h>
#	include <xmmintrin.h>
#endif

namespace Talon
{
	// Constant conversion types
	TALON_ALIGN_START(16, struct VectorInt32)
	{
		union
		{
			i32 i[4];
			Vector v;
		};

		inline operator Vector() const { return v; }
#if TALON_MATH == TALON_MATH_SSE2
		inline operator __m128i() const { return _mm_castps_si128(v); }
		inline operator __m128d() const { return _mm_castps_pd(v); }
#endif
	} TALON_ALIGN_END(16);
	
	const float Pi				= 3.141592654f;
	const float TwoPi			= 6.283185307f;
	const float OneOverPi		= 0.318309886f;
	const float OneOverTwoPi	= 0.159154943f;
	const float PiOverTwo       = 1.570796327f;
	const float PiOverFour		= 0.785398163f;

	const extern VectorInt32 VectorMask3 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000};
	const extern VectorInt32 VectorMaskX = {0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000};
	const extern VectorInt32 VectorMaskY = {0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000};
	const extern VectorInt32 VectorMaskZ = {0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000};
	const extern VectorInt32 VectorMaskW = {0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF};
}