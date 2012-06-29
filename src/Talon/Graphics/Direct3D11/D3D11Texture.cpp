

#include "TalonPrefix.h"
#include "D3D11Utility.h"
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	class Texture::Impl
	{
	public:
		bool Load(ID3D11Device* device, u32 width, u32 height, BufferFormat format, BufferUsage usage, const void* data, const std::string debugName);
		void Update(ID3D11DeviceContext* ctx, const void* data);

		u32 width;
		u32 height;

		BufferFormat format;
		BufferUsage usage;

		CComPtr<ID3D11Texture2D> texture;
		CComPtr<ID3D11ShaderResourceView> shaderResourceView;
	};

	Texture::Texture(const RenderDevice* device)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>())
	{
	}

	Texture::~Texture()
	{
	}

	ID3D11ShaderResourceView* Texture::GetShaderResourceView() const
	{
		return m_pImpl->shaderResourceView;
	}

	bool Texture::Load(u32 width, u32 height, BufferFormat format, BufferUsage usage, const void* data, const std::string debugName)
	{
		bool success = m_pImpl->Load(GetParent()->GetDevice(), width, height, format, usage, data, debugName);
		
		if (usage == BufferUsage::Dynamic)
			Update(data);

		return success;
	}

	bool Texture::Impl::Load(ID3D11Device* device, u32 width, u32 height, BufferFormat format, BufferUsage usage, const void* data, const std::string debugName)
	{
		D3D11_TEXTURE2D_DESC desc = { 0 };
		 
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = D3D11::ToDxgiFormat(format);
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11::ToUsage(usage);
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = usage == BufferUsage::Dynamic ? D3D11_CPU_ACCESS_WRITE : 0;

		D3D11_SUBRESOURCE_DATA initialData = { 0 };
		if (usage == BufferUsage::Default)
		{
			initialData.pSysMem = data;
			initialData.SysMemPitch = width * Graphics::ToBytesPerPixel(format);
		}

		if (FAILED(device->CreateTexture2D(&desc, usage == BufferUsage::Default ? &initialData : nullptr, &texture)))
			return false;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(srvDesc));
		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;

		if (FAILED(device->CreateShaderResourceView(texture, &srvDesc, &shaderResourceView)))
		{
			texture.Release();
			return false;
		}
		
		D3D11::SetDebugName(texture, debugName);

		this->width = width;
		this->height = height;
		this->format = format;
		this->usage = usage;

		return true;
	}

	void Texture::Impl::Update(ID3D11DeviceContext* ctx, const void* data)
	{
		if (usage == BufferUsage::Dynamic)
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			ThrowIfFailed(ctx->Map(texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource));

			u32 bufferSize = subresource.RowPitch * height;
			for(u32 bufferOffset = 0; bufferOffset < bufferSize; bufferOffset += subresource.RowPitch)
				memcpy(((u8*) subresource.pData) + bufferOffset, ((u8*) data) + bufferOffset, subresource.RowPitch);

			ctx->Unmap(texture, 0);
		}
		else
		{
			auto debugName = D3D11::GetDebugName(texture);

			shaderResourceView.Release();
			texture.Release();

			ID3D11Device* device;
			ctx->GetDevice(&device);
			Load(device, width, height, format, usage, data, debugName);
		}
	}

	void Texture::Update(const void* data)
	{
		m_pImpl->Update(GetParent()->GetDeviceContext(), data);
	}

	u32 Texture::GetWidth() const
	{
		return m_pImpl->width;
	}

	u32 Texture::GetHeight() const
	{
		return m_pImpl->height;
	}
}