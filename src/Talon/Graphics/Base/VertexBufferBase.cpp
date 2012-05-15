
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/Base/VertexBufferBase.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	VertexBufferBase::VertexBufferBase(RenderDevice* renderDevice, int vertexSize)
		: m_renderDevice(renderDevice)
		, m_vertexSize(vertexSize)
	{
	}

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