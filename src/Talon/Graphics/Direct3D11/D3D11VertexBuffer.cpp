
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/Direct3D11/D3D11VertexBuffer.h>

namespace Talon
{
	D3D11VertexBuffer::D3D11VertexBuffer(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* initialData, BufferUsage bufferUsage)
		: Base(renderDevice, vertexSize, vertexCount, initialData, bufferUsage)
	{
	}


	D3D11VertexBuffer::~D3D11VertexBuffer()
	{
	}

}