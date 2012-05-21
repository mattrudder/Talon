
#include "TalonPrefix.h"
#include <Talon/Graphics/VertexBuffer.h>

namespace Talon
{
	VertexBuffer::VertexBuffer(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* initialData, BufferUsage bufferUsage)
		: Base(renderDevice, vertexSize, vertexCount, initialData, bufferUsage)
	{
	}


	VertexBuffer::~VertexBuffer()
	{

	}

}