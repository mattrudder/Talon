
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

	VertexBuffer::VertexBuffer(RenderDevice* renderDevice, u32 vertexSize, u32 vertexCount, BufferUsage bufferUsage, void* initialData)
		: m_renderDevice(renderDevice)
		, m_vertexSize(vertexSize)
		, m_vertexCount(vertexCount)
		, m_bufferUsage(bufferUsage)
        , m_pImpl(std::make_unique<Impl>())
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
    
    void VertexBuffer::Update(int vertexCount, void* vertexData)
    {
        u32 bufferSize = vertexCount * m_vertexSize;
		TALON_ASSERT(bufferSize <= m_vertexCount * m_vertexSize && "Data supplied is larger than the buffer!");

        glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->arrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexData, m_bufferUsage == BufferUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void VertexBuffer::Map(BufferMapType mapType, void** ppData)
    {
        GLenum access = GL_MAP_WRITE_BIT;
        
        if (mapType == BufferMapType::Discard)
            access |= GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
        
        glBindBuffer(GL_ARRAY_BUFFER, m_pImpl->arrayBuffer);
        glMapBufferRange(GL_ARRAY_BUFFER, 0, m_vertexCount * m_vertexSize, access);
    }
    
    void VertexBuffer::Unmap()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}