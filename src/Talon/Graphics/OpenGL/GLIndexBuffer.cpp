
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

	void IndexBuffer::Update(u32 indexCount, void* indexData)
	{
		size_t indexSize = m_format == BufferFormat::I16 ? sizeof(short) : sizeof(int);
		u32 bufferSize = indexCount * indexSize;
		TALON_ASSERT(bufferSize <= m_indexCount * indexSize && "Data supplied is larger than the buffer!");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->elementArrayBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, indexData, m_bufferUsage == BufferUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::Map(BufferMapType mapType, void** ppData)
	{
		TALON_ASSERT(ppData);

		GLenum access = GL_MAP_WRITE_BIT;

		if (mapType == BufferMapType::Discard)
			access |= GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT;

		size_t indexSize = m_format == BufferFormat::I16 ? sizeof(short) : sizeof(int);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pImpl->elementArrayBuffer);
		*ppData = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, m_indexCount * indexSize, access);
	}

	void IndexBuffer::Unmap()
	{
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	u32 IndexBuffer::GetBuffer() const
	{
		return m_pImpl->elementArrayBuffer;
	}
}