

#include "TalonPrefix.h"
#include "D3D11Utility.h"
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	class Texture::Impl
	{
	public:
		bool LoadFromMemory(ID3D11Device* device, u32 width, u32 height, BufferFormat format, const void* data);

		CComPtr<ID3D11Texture2D> texture;
	};

	Texture::Texture(const RenderDevice* device)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>())
	{
	}

	Texture::~Texture()
	{
	}

	bool Texture::LoadFromMemory(u32 width, u32 height, BufferFormat format, const void* data)
	{
		return m_pImpl->LoadFromMemory(GetParent()->GetDevice(), width, height, format, data);
	}

	bool Texture::Impl::LoadFromMemory(ID3D11Device* device, u32 width, u32 height, BufferFormat format, const void* data)
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

		return SUCCEEDED(device->CreateTexture2D(&desc, &initialData, &texture));
	}
}