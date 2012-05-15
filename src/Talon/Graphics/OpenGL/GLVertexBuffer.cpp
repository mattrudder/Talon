
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/OpenGL/GLVertexBuffer.h>

namespace Talon
{
	GLVertexBuffer::GLVertexBuffer(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* initialData, BufferUsage bufferUsage)
		: Base(renderDevice, vertexSize, vertexCount, initialData, bufferUsage)
	{
	}


	GLVertexBuffer::~GLVertexBuffer()
	{
	}

}