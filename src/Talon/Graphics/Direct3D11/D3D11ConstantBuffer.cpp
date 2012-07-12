
#include "TalonPrefix.h"

#include <Talon/Graphics/ConstantBuffer.h>
#include <Talon/Graphics/RenderDevice.h>

#include "D3D11Utility.h"

namespace Talon
{
	class ConstantBufferBase::Impl
	{
	public:
		CComPtr<ID3D11Buffer> constantBuffer;
	};

	ConstantBufferBase::~ConstantBufferBase()
	{
	}

	ConstantBufferBase::ConstantBufferBase(RenderDevice* renderDevice, u32 bufferSize, BufferUsage bufferUsage, void* initialData)
		: RenderDeviceChild(renderDevice)
		, m_bufferSize(bufferSize)
		, m_bufferUsage(bufferUsage)
		, m_pImpl(std::make_unique<Impl>())
	{
		TALON_ASSERT((initialData != nullptr || bufferUsage == BufferUsage::Dynamic) && "Initial data is required, unless the buffer is writable!");

		D3D11_BUFFER_DESC desc = {0};
		desc.ByteWidth = bufferSize;
		desc.Usage = D3D11::ToUsage(bufferUsage);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = bufferUsage == BufferUsage::Dynamic ? D3D11_CPU_ACCESS_WRITE : 0;

		D3D11_SUBRESOURCE_DATA bufferData = {0};
		bufferData.pSysMem = initialData;
		bufferData.SysMemPitch = 0;
		bufferData.SysMemSlicePitch = 0;
		ThrowIfFailed(renderDevice->GetDevice()->CreateBuffer(&desc, initialData == nullptr ? nullptr : &bufferData, &m_pImpl->constantBuffer));
	}

	void ConstantBufferBase::Update(u32 bufferSize, void* bufferData)
	{
		TALON_ASSERT(bufferSize <= m_bufferSize && "Data supplied is larger than the buffer!");
		TALON_ASSERT(m_bufferUsage != BufferUsage::Immutable && "Cannot update immutable buffers!");

		ID3D11DeviceContext* ctx = GetParent()->GetDeviceContext();
		if (m_bufferUsage == BufferUsage::Dynamic)
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			ThrowIfFailed(ctx->Map(m_pImpl->constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource));

			for(u32 bufferOffset = 0; bufferOffset < bufferSize; bufferOffset += subresource.RowPitch)
				memcpy(((u8*) subresource.pData) + bufferOffset, ((u8*) bufferData) + bufferOffset, subresource.RowPitch);

			ctx->Unmap(m_pImpl->constantBuffer, 0);
		}
		else
		{
			ctx->UpdateSubresource(m_pImpl->constantBuffer, 0, nullptr, bufferData, bufferSize, 0);
		}
	}

	void ConstantBufferBase::Map(BufferMapType mapType, void** ppData)
	{
		TALON_ASSERT(ppData);

		D3D11_MAPPED_SUBRESOURCE subresource;
		ID3D11DeviceContext* ctx = GetParent()->GetDeviceContext();
		ThrowIfFailed(ctx->Map(m_pImpl->constantBuffer, 0, D3D11::ToMap(mapType), 0, &subresource));

		*ppData = subresource.pData;
	}

	void ConstantBufferBase::Unmap()
	{
		ID3D11DeviceContext* ctx = GetParent()->GetDeviceContext();
		ctx->Unmap(m_pImpl->constantBuffer, 0);
	}

	ID3D11Buffer* ConstantBufferBase::GetBuffer() const
	{
		return m_pImpl->constantBuffer;
	}
}