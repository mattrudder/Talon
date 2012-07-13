
#include "TalonPrefix.h"
#include "GraphicsUtility.h"

namespace Talon { namespace Graphics
{
	u32 ToByteSize(BufferFormat format)
	{
		switch (format)
		{
		case BufferFormat::B8G8R8A8U:		return 4;
		case BufferFormat::B8G8R8U:			return 3;
		case BufferFormat::R32G32B32A32F:	return 16;
		case BufferFormat::R32G32B32F:		return 12;
		case BufferFormat::R32G32F:			return 8;
		case BufferFormat::R8G8B8A8U:		return 4;
		default:							return 0;
		}
	}
}}