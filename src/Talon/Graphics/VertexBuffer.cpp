
#include "TalonPrefix.h"
#include <Talon/Graphics/VertexBuffer.h>

namespace Talon
{
	int VertexBuffer::GetVertexSize() const
	{
		return m_vertexSize;
	}

	int VertexBuffer::GetVertexCount() const
	{
		return m_vertexCount;
	}

	BufferUsage VertexBuffer::GetBufferUsage() const
	{
		return m_bufferUsage;
	}
}