
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/Base/IndexBufferBase.h>

namespace Talon
{
	IndexBufferBase::IndexBufferBase(RenderDevice* renderDevice, BufferFormat format)
		: m_renderDevice(renderDevice)
		, m_format(format)
	{
	}

	IndexBufferBase::~IndexBufferBase()
	{
	}

	BufferFormat IndexBufferBase::GetFormat() const
	{
		return m_format;
	}


	void IndexBufferBase::SetFormat(BufferFormat value)
	{
		m_format = value;
	}

}