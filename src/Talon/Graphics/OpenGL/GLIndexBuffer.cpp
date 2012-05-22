
#include "TalonPrefix.h"
#include <GL/glew.h>
#include <Talon/Graphics/IndexBuffer.h>

namespace Talon
{
	class IndexBuffer::Impl
	{
	public:
		GLuint elementArrayBuffer;
	};

	IndexBuffer::IndexBuffer(RenderDevice* renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage)
		: m_renderDevice(renderDevice)
		, m_format(format)
		, m_indexCount(indexCount)
		, m_bufferUsage(bufferUsage)
		, m_pImpl(make_unique<Impl>())
	{
		//TALON_ASSERT(bufferUsage == BufferUsage::Dynamic || bufferUsage == BufferUsage::Default);

		size_t indexSize = format == BufferFormat::I16 ? sizeof(short) : sizeof(int);
		glGenBuffers(1, &m_pImpl->elementArrayBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->elementArrayBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * indexCount, initialData, bufferUsage == BufferUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_pImpl->elementArrayBuffer);
	}
}