
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/InputClassification.h>

namespace Talon
{
	struct InputElement
	{
		const char* SemanticName;
		u32 SemanticIndex;
		BufferFormat Format;
		u32 InputSlot;
		u32 AlignedByteOffset;
		InputClassification InputSlotClass;
		u32 InstanceDataStepRate;
	};
}