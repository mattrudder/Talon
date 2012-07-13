
#include "TalonPrefix.h"
#include <Talon/Graphics/ConstantBuffer.h>

namespace Talon
{
	class ConstantBufferBase::Impl
	{
	public:
		GLuint constantBuffer;
	};
	
	ConstantBufferBase::~ConstantBufferBase()
	{
		glDeleteBuffers(1, &m_pImpl->constantBuffer);
	}

	ConstantBufferBase::ConstantBufferBase(RenderDevice* renderDevice, u32 bufferSize, BufferUsage bufferUsage, void* initialData)
		: RenderDeviceChild(renderDevice)
		, m_bufferSize(bufferSize)
		, m_bufferUsage(bufferUsage)
		, m_pImpl(std::make_unique<Impl>())
	{
		TALON_ASSERT(bufferUsage == BufferUsage::Dynamic || bufferUsage == BufferUsage::Default);
		
		glGenBuffers(1, &m_pImpl->constantBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER_EXT, m_pImpl->constantBuffer);
		glBufferData(GL_UNIFORM_BUFFER_EXT, bufferSize, initialData, bufferUsage == BufferUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER_EXT, 0);
	}
	
	void ConstantBufferBase::Update(u32 bufferSize, void* bufferData)
    {
		TALON_ASSERT(bufferSize <= m_bufferSize && "Data supplied is larger than the buffer!");
		
        glBindBuffer(GL_UNIFORM_BUFFER_EXT, m_pImpl->constantBuffer);
        glBufferData(GL_UNIFORM_BUFFER_EXT, bufferSize, bufferData, m_bufferUsage == BufferUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER_EXT, 0);
    }
    
    void ConstantBufferBase::Map(BufferMapType mapType, void** ppData)
    {
		TALON_ASSERT(ppData);

		GLenum access = GL_MAP_WRITE_BIT;

		if (mapType == BufferMapType::Discard)
			access |= GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT;

		glBindBuffer(GL_UNIFORM_BUFFER_EXT, m_pImpl->constantBuffer);
		*ppData = glMapBufferRange(GL_UNIFORM_BUFFER_EXT, 0, m_bufferSize, access);
    }
    
    void ConstantBufferBase::Unmap()
    {
        glUnmapBuffer(GL_UNIFORM_BUFFER_EXT);
        glBindBuffer(GL_UNIFORM_BUFFER_EXT, 0);
    }
}