
#include <Talon/Graphics/Direct3D11/D3D11VertexBuffer.h>

namespace Talon
{
	D3D11VertexBuffer::D3D11VertexBuffer(RenderDevice* renderDevice, int vertexSize)
		: Base(renderDevice, vertexSize)
	{
	}


	D3D11VertexBuffer::~D3D11VertexBuffer()
	{
	}

}