
#include "TalonPrefix.h"
#include <Talon/Graphics/VertexBuffer.h>

namespace Talon
{
	int VertexBuffer::GetVertexSize() const
	{
		return m_vertexSize;
	}

	void VertexBuffer::SetVertexSize(int value)
	{
		m_vertexSize = value;
	}

	int VertexBuffer::GetVertexCount() const
	{
		return m_vertexCount;
	}

	void VertexBuffer::SetVertexCount(int value)
	{
		m_vertexCount = value;
	}

	BufferUsage VertexBuffer::GetBufferUsage() const
	{
		return m_bufferUsage;
	}

	void VertexBuffer::SetBufferUsage(BufferUsage value)
	{
		m_bufferUsage = value;
	}
}