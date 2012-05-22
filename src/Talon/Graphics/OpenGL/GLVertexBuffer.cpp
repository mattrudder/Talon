
#include "TalonPrefix.h"
#include <GL/glew.h>
#include <Talon/Graphics/VertexBuffer.h>

namespace Talon
{
	class VertexBuffer::Impl
	{
	public:
		GLuint arrayBuffer;
	};

	VertexBuffer::VertexBuffer(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* initialData, BufferUsage bufferUsage)
		: m_renderDevice(renderDevice)
		, m_vertexSize(vertexSize)
		, m_vertexCount(vertexCount)
		, m_bufferUsage(bufferUsage)
		, m_pImpl(make_unique<Impl>())
	{
		glGenBuffers(1, &m_pImpl->arrayBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->arrayBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexCount, initialData, bufferUsage == BufferUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_pImpl->arrayBuffer);
	}
}