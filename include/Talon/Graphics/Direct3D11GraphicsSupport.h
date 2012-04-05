
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/GraphicsSupportBase.h>

namespace Talon
{
	class ConstantBuffer;
	class IndexBuffer;
	class VertexBuffer;

	/** Direct3D 11 support policy for GraphicsSupportImpl. */
	class Direct3D11GraphicsSupport : public GraphicsSupportBase<Direct3D11GraphicsSupport>
	{
		ConstantBuffer* CreateConstantBufferCore(size_t bufferSize);
		IndexBuffer* CreateIndexBufferCore(void* data, size_t indexCount);
		VertexBuffer* CreateVertexBufferCore(void* data, size_t vertexSize, size_t vertexCount);
	};
}