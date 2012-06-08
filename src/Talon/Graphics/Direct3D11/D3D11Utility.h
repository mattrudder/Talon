
#include "TalonPrefix.h"
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferMapType.h>

namespace Talon { namespace D3D11
{
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