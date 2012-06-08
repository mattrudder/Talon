

#include "TalonPrefix.h"
#include "D3D11Utility.h"
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	class Texture::Impl
	{
	public:
		bool Load(ID3D11Device* device, u32 width, u32 height, BufferFormat format, const void* data, const std::string debugName);

		u32 width;
		u32 height;

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

	bool Texture::Load(u32 width, u32 height, BufferFormat format, const void* data, const std::string debugName)
	{
		return m_pImpl->Load(GetParent()->GetDevice(), width, height, format, data, debugName);
	}

	bool Texture::Impl::Load(ID3D11Device* device, u32 width, u32 height, BufferFormat format, const void* data, const std::string debugName)
	{
		D3D11_TEXTURE2D_DESC desc = { 0 };
		 
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = D3D11::ToDxgiFormat(format);
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA initialData = { 0 };
		initialData.pSysMem = data;
		initialData.SysMemPitch = width * Graphics::ToBytesPerPixel(format);

		if (FAILED(device->CreateTexture2D(&desc, &initialData, &texture)))
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
		
#if defined(DEBUG)
		D3D11::SetDebugName(texture, debugName);
#endif

		this->width = width;
		this->height = height;
		return true;
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