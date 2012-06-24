

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
    
	bool Texture::Load(u32 width, u32 height, BufferFormat format, const void* data, const std::string debugName)
	{
		glBindTexture(GL_TEXTURE_2D, m_pImpl->texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL::ToInternalFormat(format), width, height, 0, GL::ToFormat(format), GL::ToDataType(format), data);
        glBindTexture(GL_TEXTURE_2D, 0);
        
		m_pImpl->width = width;
		m_pImpl->height = height;
		return true;
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