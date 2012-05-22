
#include "TalonPrefix.h"
#include <GL/glew.h>
#include <Talon/Graphics/VertexBuffer.h>

namespace Talon
{
	class VertexBuffer::Impl
	{
	public:
		GLuint elementBuffer;
	};

	VertexBuffer::VertexBuffer(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* /*initialData*/, BufferUsage bufferUsage)
		: m_renderDevice(renderDevice)
		, m_vertexSize(vertexSize)
		, m_vertexCount(vertexCount)
		, m_bufferUsage(bufferUsage)
		, m_pImpl(make_unique<Impl>())
	{
	}

	VertexBuffer::~VertexBuffer()
	{
	}

}