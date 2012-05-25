
#include "TalonPrefix.h"
#include <Talon/Graphics/VertexBuffer.h>
#include <Talon/Graphics/RenderDevice.h>

using namespace std;

namespace Talon
{
    class VertexBuffer::Impl
    {
    public:
		CComPtr<ID3D11Buffer> vertexBuffer;
    };

    VertexBuffer::VertexBuffer(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* initialData, BufferUsage bufferUsage)
        : m_renderDevice(renderDevice)
        , m_vertexSize(vertexSize)
        , m_vertexCount(vertexCount)
        , m_bufferUsage(bufferUsage)
        , m_pImpl(make_unique<Impl>())
    {
		D3D11_BUFFER_DESC bufferDesc = {0};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = vertexSize * vertexCount;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA bufferData = {0};
		bufferData.pSysMem = initialData;
		bufferData.SysMemPitch = 0;
		bufferData.SysMemSlicePitch = 0;

		ThrowIfFailed(renderDevice->GetDevice()->CreateBuffer(&bufferDesc, &bufferData, &m_pImpl->vertexBuffer));
    }

    VertexBuffer::~VertexBuffer()
    {
    }
}