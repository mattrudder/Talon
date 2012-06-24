
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferMapType.h>

namespace Talon { namespace GL
{
    inline GLenum ToInternalFormat(BufferFormat format)
    {
        switch (format)
        {
            case BufferFormat::R8G8B8A8U:
            case BufferFormat::B8G8R8A8U:		return GL_RGBA8UI;
            case BufferFormat::B8G8R8U:			return GL_RGB8UI;
            case BufferFormat::R32G32B32A32F:	return GL_RGBA32F;
            case BufferFormat::R32G32B32F:		return GL_RGB32F;
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
}}