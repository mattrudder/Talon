
#include "TalonPrefix.h"
#include <Talon/Graphics/VertexBuffer.h>

using namespace std;

namespace Talon
{
    class VertexBuffer::Impl
    {
    public:
    };

    VertexBuffer::VertexBuffer(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* /*initialData*/, BufferUsage bufferUsage)
        : m_renderDevice(renderDevice)
        , m_vertexSize(vertexSize)
        , m_vertexCount(vertexCount)
        , m_bufferUsage(bufferUsage)
        , m_pImpl(make_unique<Impl>())
    {
    }

    VertexBuffer::~VertexBuffer()
    {
    }
}