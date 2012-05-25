
#include "TalonPrefix.h"
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/RenderDevice.h>

using namespace std;

namespace Talon
{
    class IndexBuffer::Impl
    {
    public:
		CComPtr<ID3D11Buffer> indexBuffer;
    };

    IndexBuffer::IndexBuffer(RenderDevice* renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage)
        : m_renderDevice(renderDevice)
        , m_format(format)
        , m_indexCount(indexCount)
        , m_bufferUsage(bufferUsage)
        , m_pImpl(make_unique<Impl>())
    {
		size_t indexSize = format == BufferFormat::I16 ? sizeof(i16) : sizeof(i32);

		D3D11_BUFFER_DESC bufferDesc = {0};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = indexSize * indexCount;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA bufferData = {0};
		bufferData.pSysMem = initialData;
		bufferData.SysMemPitch = 0;
		bufferData.SysMemSlicePitch = 0;

		ThrowIfFailed(renderDevice->GetDevice()->CreateBuffer(&bufferDesc, &bufferData, &m_pImpl->indexBuffer));
	}


	IndexBuffer::~IndexBuffer()
	{
	}

}