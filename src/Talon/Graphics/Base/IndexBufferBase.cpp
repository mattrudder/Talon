
#include "TalonPrefix.h"
#include <Talon/Graphics/Base/IndexBufferBase.h>

namespace Talon
{
// TODO: Code generation should mark unused parameters as such.
#pragma warning(push)
#pragma warning(disable : 4100)
	IndexBufferBase::IndexBufferBase(RenderDevice* renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage)
		: m_renderDevice(renderDevice)
		, m_format(format)
		, m_indexCount(indexCount)
		, m_bufferUsage(bufferUsage)
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

	int IndexBufferBase::GetIndexCount() const
	{
		return m_indexCount;
	}


	void IndexBufferBase::SetIndexCount(int value)
	{
		m_indexCount = value;
	}

	BufferUsage IndexBufferBase::GetBufferUsage() const
	{
		return m_bufferUsage;
	}


	void IndexBufferBase::SetBufferUsage(BufferUsage value)
	{
		m_bufferUsage = value;
	}

}