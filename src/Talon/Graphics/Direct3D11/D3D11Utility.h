
#include "TalonPrefix.h"
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferMapType.h>

namespace Talon { namespace D3D11
{
	inline void SetDebugName(ID3D11DeviceChild* child, const std::string name)
	{
		child->SetPrivateData(WKPDID_D3DDebugObjectName, name.size() * sizeof(char), name.c_str());
	}

	inline HRESULT CreateBlendState(ID3D11Device* device, D3D11_BLEND srcBlend, D3D11_BLEND destBlend, ID3D11BlendState** pResult)
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE) ||
			(destBlend != D3D11_BLEND_ZERO);

		desc.RenderTarget[0].SrcBlend  = desc.RenderTarget[0].SrcBlendAlpha  = srcBlend;
		desc.RenderTarget[0].DestBlend = desc.RenderTarget[0].DestBlendAlpha = destBlend;
		desc.RenderTarget[0].BlendOp   = desc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return device->CreateBlendState(&desc, pResult);
	}

	inline HRESULT CreateDepthStencilState(ID3D11Device* device, bool enable, bool writeEnable, ID3D11DepthStencilState** pResult)
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.DepthEnable = enable;
		desc.DepthWriteMask = writeEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		desc.StencilEnable = false;
		desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

		desc.BackFace = desc.FrontFace;

		return device->CreateDepthStencilState(&desc, pResult);
	}

	inline HRESULT CreateRasterizerState(ID3D11Device* device, D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, _Out_ ID3D11RasterizerState** pResult)
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.CullMode = cullMode;
		desc.FillMode = fillMode;
		desc.DepthClipEnable = true;
		desc.MultisampleEnable = true;

		return device->CreateRasterizerState(&desc, pResult);
	}

	inline HRESULT CreateSamplerState(ID3D11Device* device, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressMode, _Out_ ID3D11SamplerState** pResult)
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.Filter = filter;

		desc.AddressU = addressMode;
		desc.AddressV = addressMode;
		desc.AddressW = addressMode;

		desc.MaxLOD = FLT_MAX;
		desc.MaxAnisotropy = 16;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		return device->CreateSamplerState(&desc, pResult);
	}

	inline DXGI_FORMAT ToDxgiFormat(BufferFormat format)
	{
		switch (format)
		{
		case BufferFormat::B8G8R8A8U:		return DXGI_FORMAT_B8G8R8A8_UNORM;
		case BufferFormat::B8G8R8U:			return DXGI_FORMAT_B8G8R8X8_UNORM;
		case BufferFormat::R32G32B32A32F:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case BufferFormat::R32G32B32F:		return DXGI_FORMAT_R32G32B32_FLOAT;
		case BufferFormat::R32G32F:			return DXGI_FORMAT_R32G32_FLOAT;
		case BufferFormat::R8G8B8A8U:		return DXGI_FORMAT_R8G8B8A8_UNORM;
		default:							return DXGI_FORMAT_UNKNOWN;
		}
	}

	inline D3D11_MAP ToMap(BufferMapType mapType)
	{
		switch (mapType)
		{
		case BufferMapType::Discard:		return D3D11_MAP_WRITE_DISCARD;
		case BufferMapType::NoOverwrite:	return D3D11_MAP_WRITE_NO_OVERWRITE;
		default:							return D3D11_MAP_WRITE;
		}
	}
}}