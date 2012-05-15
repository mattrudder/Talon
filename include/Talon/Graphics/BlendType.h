
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	enum class BlendType
	{
		Zero,
		One,
		SourceColor,
		InverseSourceColor,
		SourceAlpha,
		InverseSourceAlpha,
		DestinationAlpha,
		InverseDestinationAlpha,
		DestinationColor,
		InverseDestinationColor,
		BlendFactor,
		InverseBlendFactor,
	};
}