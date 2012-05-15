
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/Base/VertexBufferBase.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
// TODO: Code generation should mark unused parameters as such.
#pragma warning(push)
#pragma warning(disable : 4100)
	VertexBufferBase::VertexBufferBase(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* initialData, BufferUsage bufferUsage)
		: m_renderDevice(renderDevice)
		, m_vertexSize(vertexSize)
		, m_vertexCount(vertexCount)
		, m_bufferUsage(bufferUsage)
	{
	}
#pragma warning(pop)
	VertexBufferBase::~VertexBufferBase()
	{
	}

	int VertexBufferBase::GetVertexSize() const
	{
		return m_vertexSize;
	}


	void VertexBufferBase::SetVertexSize(int value)
	{
		m_vertexSize = value;
	}

}