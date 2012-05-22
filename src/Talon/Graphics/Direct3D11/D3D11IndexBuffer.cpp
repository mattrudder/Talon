
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/IndexBuffer.h>

namespace Talon
{
    class IndexBuffer::Impl
    {
    public:
    };

    IndexBuffer::IndexBuffer(RenderDevice* renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage)
        : m_renderDevice(renderDevice)
        , m_format(format)
        , m_indexCount(indexCount)
        , m_bufferUsage(bufferUsage)
        , m_pImpl(make_unique<Impl>())
    {
	}


	IndexBuffer::~IndexBuffer()
	{
	}

}