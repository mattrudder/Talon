
#include "TalonPrefix.h"
#include <Talon/Graphics/IndexBuffer.h>

namespace Talon
{
	BufferFormat IndexBuffer::GetFormat() const
	{
		return m_format;
	}

	void IndexBuffer::SetFormat(BufferFormat value)
	{
		m_format = value;
	}

	int IndexBuffer::GetIndexCount() const
	{
		return m_indexCount;
	}

	void IndexBuffer::SetIndexCount(int value)
	{
		m_indexCount = value;
	}

	BufferUsage IndexBuffer::GetBufferUsage() const
	{
		return m_bufferUsage;
	}

	void IndexBuffer::SetBufferUsage(BufferUsage value)
	{
		m_bufferUsage = value;
	}
}