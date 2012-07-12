
#include "TalonPrefix.h"
#include <Talon/Graphics/IndexBuffer.h>

namespace Talon
{
	class IndexBuffer::Impl
	{
	public:
		GLuint elementArrayBuffer;
	};

	
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(RenderDevice* renderDevice, u32 indexCount, BufferFormat format, BufferUsage bufferUsage, void* initialData)
	{
		return std::shared_ptr<IndexBuffer>(new IndexBuffer(renderDevice, indexCount, format, bufferUsage, initialData));
	}
	
	IndexBuffer::IndexBuffer(RenderDevice* renderDevice, u32 indexCount, BufferFormat format, BufferUsage bufferUsage, void* initialData)
		: RenderDeviceChild(renderDevice)
		, m_format(format)
		, m_indexCount(indexCount)
		, m_bufferUsage(bufferUsage)
        , m_pImpl(std::make_unique<Impl>())
	{
		TALON_ASSERT(bufferUsage == BufferUsage::Dynamic || bufferUsage == BufferUsage::Default);

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
	
	u32 IndexBuffer::GetBuffer() const
	{
		return m_pImpl->elementArrayBuffer;
	}
}