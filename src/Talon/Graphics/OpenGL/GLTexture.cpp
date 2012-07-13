

#include "TalonPrefix.h"
#include "GLUtility.h"
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	class Texture::Impl
	{
	public:
        Impl();
        ~Impl();
        
		BufferFormat format;
        GLuint texture;
        u32 width;
        u32 height;
	};
    
	Texture::Texture(const RenderDevice* device)
    : RenderDeviceChild(device)
    , m_pImpl(std::make_unique<Impl>())
	{
	}
    
	Texture::~Texture()
	{
	}
    
    Texture::Impl::Impl()
    {
        glGenTextures(1, &texture);
    }
    
    Texture::Impl::~Impl()
    {
        glDeleteTextures(1, &texture);
    }
    
	bool Texture::Load(u32 width, u32 height, BufferFormat format, BufferUsage /*usage*/, const void* data, const std::string debugName)
	{
		glBindTexture(GL_TEXTURE_2D, m_pImpl->texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL::ToInternalFormat(format), width, height, 0, GL::ToFormat(format), GL::ToDataType(format), data);
        glBindTexture(GL_TEXTURE_2D, 0);
        
		m_pImpl->format = format;
		m_pImpl->width = width;
		m_pImpl->height = height;
		return true;
	}
	
	void Texture::Update(const void *data)
	{
		glBindTexture(GL_TEXTURE_2D, m_pImpl->texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_pImpl->width, m_pImpl->height, GL::ToFormat(m_pImpl->format), GL::ToDataType(m_pImpl->format), data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
    
	u32 Texture::GetWidth() const
	{
		return m_pImpl->width;
	}
    
	u32 Texture::GetHeight() const
	{
		return m_pImpl->height;
	}
}