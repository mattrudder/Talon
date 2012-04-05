
#include <Talon/TalonPublic.h>

namespace Talon
{
	template <class GraphicsApi>
	class GraphicsSupportBase
	{
	public:
		GraphicsApi::ConstantBufferType* CreateConstantBuffer(size_t bufferSize)
		{
			return static_cast<GraphicsApi>(this)->CreateConstantBufferCore(bufferSize);
		}

		GraphicsApi::IndexBufferType* CreateIndexBuffer(void* data, size_t indexCount)
		{
			return static_cast<GraphicsApi>(this)->CreateIndexBufferCore(data, indexCount);
		}

		GraphicsApi::VertexBufferType* CreateVertexBuffer(void* data, size_t vertexSize, size_t vertexCount)
		{
			return static_cast<GraphicsApi>(this)->CreateVertexBufferCore(data, vertexSize, vertexCount);
		}
	};
}