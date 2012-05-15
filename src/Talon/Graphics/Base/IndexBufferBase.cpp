
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/Base/IndexBufferBase.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
// TODO: Code generation should mark unused parameters as such.
#pragma warning(push)
#pragma warning(disable : 4100)
	IndexBufferBase::IndexBufferBase(RenderDevice* renderDevice, BufferFormat format)
		: m_renderDevice(renderDevice)
		, m_format(format)
	{
	}
#pragma warning(pop)
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