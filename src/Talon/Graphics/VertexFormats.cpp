
#include "TalonPrefix.h"

#include <Talon/Graphics/VertexFormats.h>

namespace Talon
{
	
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		// Vertex struct holding position, color, and texture mapping information.
	//const D3D11_INPUT_ELEMENT_DESC VertexPositionColorTexture::InputElements[] =
	//{
	//	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};
	const InputElement VertexPositionColorTexture::InputElements[] =
	{
		{ "SV_Position", 0, BufferFormat::R32G32B32F,    0, InputClassification::PerVertex, 0 },
		{ "COLOR",       0, BufferFormat::R32G32B32A32F, 0, InputClassification::PerVertex, 0 },
		{ "TEXCOORD",    0, BufferFormat::R32G32F,       0, InputClassification::PerVertex, 0 },
	};
#endif
}