
#include "TalonPrefix.h"
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/RenderDevice.h>

using namespace std;

namespace Talon
{
    class IndexBuffer::Impl
    {
    public:
		void Update(ID3D11DeviceContext* ctx, BufferUsage bufferUsage, u32 bufferSize, void* indexData)
		{
			TALON_ASSERT(bufferUsage != BufferUsage::Immutable && "Cannot update immutable buffers!");

			if (bufferUsage == BufferUsage::Dynamic)
			{
				D3D11_MAPPED_SUBRESOURCE subresource;
				ThrowIfFailed(ctx->Map(indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource));

				for(u32 bufferOffset = 0; bufferOffset < bufferSize; bufferOffset += subresource.RowPitch)
					memcpy(((u8*) subresource.pData) + bufferOffset, ((u8*) indexData) + bufferOffset, subresource.RowPitch);

				ctx->Unmap(indexBuffer, 0);
			}
			else
			{
				ctx->UpdateSubresource(indexBuffer, 0, nullptr, indexData, bufferSize, 0);
			}
		}

		CComPtr<ID3D11Buffer> indexBuffer;
    };

    IndexBuffer::IndexBuffer(RenderDevice* renderDevice, u32 indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage)
        : m_renderDevice(renderDevice)
        , m_format(format)
        , m_indexCount(indexCount)
        , m_bufferUsage(bufferUsage)
        , m_pImpl(make_unique<Impl>())
    {
		size_t indexSize = format == BufferFormat::I16 ? sizeof(i16) : sizeof(i32);

		D3D11_BUFFER_DESC bufferDesc = {0};
		bufferDesc.ByteWidth = indexSize * indexCount;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = bufferUsage == BufferUsage::Dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		switch(bufferUsage)
		{
		case BufferUsage::Default:
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			break;
		case BufferUsage::Dynamic:
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			break;
		case BufferUsage::Immutable:
			bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			break;
		}

		D3D11_SUBRESOURCE_DATA bufferData = {0};
		bufferData.pSysMem = initialData;
		bufferData.SysMemPitch = 0;
		bufferData.SysMemSlicePitch = 0;

		ThrowIfFailed(renderDevice->GetDevice()->CreateBuffer(&bufferDesc, &bufferData, &m_pImpl->indexBuffer));
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::Update(u32 indexCount, void* indexData)
	{
		u32 indexSize = m_format == BufferFormat::I16 ? sizeof(i16) : sizeof(i32);
		u32 bufferSize = indexCount * indexSize;
		TALON_ASSERT(indexCount <= m_indexCount && "Data supplied is larger than the buffer!");
		m_pImpl->Update(m_renderDevice->GetDeviceContext(), m_bufferUsage, bufferSize, indexData);
	}
}