
#include "TalonPrefix.h"
#include <Talon/Graphics/IndexBuffer.h>

namespace Talon
{
	BufferFormat IndexBuffer::GetFormat() const
	{
		return m_format;
	}

	int IndexBuffer::GetIndexCount() const
	{
		return m_indexCount;
	}

	BufferUsage IndexBuffer::GetBufferUsage() const
	{
		return m_bufferUsage;
	}
}