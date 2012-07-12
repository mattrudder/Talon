
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferMapType.h>
#include <Talon/Graphics/ShaderType.h>

namespace Talon { namespace GL
{
    inline GLenum ToInternalFormat(BufferFormat format)
    {
        switch (format)
        {
            case BufferFormat::R8G8B8A8U:
            case BufferFormat::B8G8R8A8U:		return GL_RGBA8UI_EXT;
            case BufferFormat::B8G8R8U:			return GL_RGB8UI_EXT;
            case BufferFormat::R32G32B32A32F:	return GL_RGBA32F_ARB;
            case BufferFormat::R32G32B32F:		return GL_RGB32F_ARB;
            case BufferFormat::R32G32F:			return GL_RG32F;
            default:							return 0;
        }
    }
    
    inline GLenum ToDataType(BufferFormat format)
    {
        switch (format)
        {
            case BufferFormat::R32G32B32A32F:
            case BufferFormat::R32G32B32F:
            case BufferFormat::R32G32F:         return GL_FLOAT;
            case BufferFormat::B8G8R8A8U:
            case BufferFormat::B8G8R8U:
            case BufferFormat::R8G8B8A8U:       return GL_UNSIGNED_INT;
            default:							return 0;
        }
    }
    
    inline GLenum ToFormat(BufferFormat format)
    {
        switch (format)
        {
            case BufferFormat::B8G8R8A8U:		return GL_BGRA;
            case BufferFormat::B8G8R8U:			return GL_BGR;
            case BufferFormat::R32G32B32A32F:	return GL_RGBA;
            case BufferFormat::R32G32B32F:		return GL_RGB;
            case BufferFormat::R32G32F:			return GL_RG;
            case BufferFormat::R8G8B8A8U:		return GL_RGBA;
            default:							return 0;
        }
    }
	
	/** Returns the GL equivalent of the ShaderType specified, or 0 if not supported. */
	inline GLenum ToShaderType(ShaderType type)
	{
		switch (type)
		{
			case ShaderType::Compute:	return 0;
			case ShaderType::Domain:	return 0;
			case ShaderType::Geometry:	return GL_GEOMETRY_SHADER_EXT;
			case ShaderType::Hull:		return 0;
			case ShaderType::Pixel:		return GL_FRAGMENT_SHADER;
			case ShaderType::Vertex:	return GL_VERTEX_SHADER;
			default:					return 0;
		}
	}
}}