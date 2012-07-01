
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	// Vertex struct holding position, color, and texture mapping information.
	struct VertexPositionColorTexture
	{
		VertexPositionColorTexture()
		{
		}
		
		VertexPositionColorTexture(float3 const& position, float4 const& color, float2 const& textureCoordinate)
			: position(position)
			, color(color)
			, textureCoordinate(textureCoordinate)
		{
		}
		
		float3 position;
		float4 color;
		float2 textureCoordinate;
		
		static const int InputElementCount = 3;
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
#endif
	};
}