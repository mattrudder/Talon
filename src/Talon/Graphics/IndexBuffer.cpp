
#include "TalonPrefix.h"
#include <Talon/Graphics/IndexBuffer.h>

namespace Talon
{
	IndexBuffer::IndexBuffer(RenderDevice* renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage)
		: Base(renderDevice, indexCount, format, initialData, bufferUsage)
	{
	}


	IndexBuffer::~IndexBuffer()
	{

	}

}