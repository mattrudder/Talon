
#include "TalonPrefix.h"
#include "D3D11Utility.h"

#include <Talon/Graphics/VertexBuffer.h>
#include <Talon/Graphics/RenderDevice.h>

using namespace std;

namespace Talon
{
    class VertexBuffer::Impl
    {
    public:
		void Update(ID3D11DeviceContext* ctx, BufferUsage bufferUsage, u32 bufferSize, void* vertexData)
		{
			TALON_ASSERT(bufferUsage != BufferUsage::Immutable && "Cannot update immutable buffers!");

			// TODO: Separate Map/Unmap and Update.
			if (bufferUsage == BufferUsage::Dynamic)
			{
				D3D11_MAPPED_SUBRESOURCE subresource;
				ThrowIfFailed(ctx->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource));

				for(u32 bufferOffset = 0; bufferOffset < bufferSize; bufferOffset += subresource.RowPitch)
					memcpy(((u8*) subresource.pData) + bufferOffset, ((u8*) vertexData) + bufferOffset, subresource.RowPitch);

				ctx->Unmap(vertexBuffer, 0);
			}
			else
			{
				ctx->UpdateSubresource(vertexBuffer, 0, nullptr, vertexData, bufferSize, 0);
			}
		}

		void Map(ID3D11DeviceContext* ctx, BufferMapType mapType, void** ppData)
		{
			TALON_ASSERT(ppData);

			D3D11_MAPPED_SUBRESOURCE subresource;
			ThrowIfFailed(ctx->Map(vertexBuffer, 0, D3D11::ToMap(mapType), 0, &subresource));

			*ppData = subresource.pData;
		}

		void Unmap(ID3D11DeviceContext* ctx)
		{
			ctx->Unmap(vertexBuffer, 0);
		}

		ID3D11Buffer* GetBuffer() const
		{
			return vertexBuffer;
		}

		CComPtr<ID3D11Buffer> vertexBuffer;
    };

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(RenderDevice* renderDevice, u32 vertexSize, u32 vertexCount, BufferUsage bufferUsage, void* initialData)
	{
		return std::shared_ptr<VertexBuffer>(new VertexBuffer(renderDevice, vertexSize, vertexCount, bufferUsage, initialData));
	}

    VertexBuffer::VertexBuffer(RenderDevice* renderDevice, u32 vertexSize, u32 vertexCount, BufferUsage bufferUsage, void* initialData)
        : RenderDeviceChild(renderDevice)
        , m_vertexSize(vertexSize)
        , m_vertexCount(vertexCount)
        , m_bufferUsage(bufferUsage)
        , m_pImpl(make_unique<Impl>())
    {
		TALON_ASSERT((initialData != nullptr || bufferUsage == BufferUsage::Dynamic) && "Initial data is required, unless the buffer is writable!");

		D3D11_BUFFER_DESC bufferDesc = {0};
		bufferDesc.ByteWidth = vertexSize * vertexCount;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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

		ThrowIfFailed(renderDevice->GetDevice()->CreateBuffer(&bufferDesc, initialData == nullptr ? nullptr : &bufferData, &m_pImpl->vertexBuffer));
    }

	void VertexBuffer::Update(int vertexCount, void* vertexData)
	{
		u32 bufferSize = vertexCount * m_vertexSize;
		TALON_ASSERT(bufferSize <= m_vertexCount * m_vertexSize && "Data supplied is larger than the buffer!");
		m_pImpl->Update(GetParent()->GetDeviceContext(), m_bufferUsage, bufferSize, vertexData);
	}

	void VertexBuffer::Map(BufferMapType mapType, void** ppData)
	{
		m_pImpl->Map(GetParent()->GetDeviceContext(), mapType, ppData);
	}

	void VertexBuffer::Unmap()
	{
		m_pImpl->Unmap(GetParent()->GetDeviceContext());
	}

	ID3D11Buffer* VertexBuffer::GetBuffer() const
	{
		return m_pImpl->GetBuffer();
	}

    VertexBuffer::~VertexBuffer()
    {
    }
}