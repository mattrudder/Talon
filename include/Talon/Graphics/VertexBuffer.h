
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/BufferMapType.h>
#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi VertexBuffer : public RenderDeviceChild
	{
	public:
		static std::shared_ptr<VertexBuffer> Create(RenderDevice* renderDevice, u32 vertexSize, u32 vertexCount, BufferUsage bufferUsage, void* initialData = nullptr);
		~VertexBuffer();

		int GetVertexSize() const;
		int GetVertexCount() const;
		BufferUsage GetBufferUsage() const;

		void Update(int vertexCount, void* vertexData);
		void Map(BufferMapType mapType, void** ppData);
		void Unmap();

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		ID3D11Buffer* GetBuffer() const;
#else
		u32 GetBuffer() const;
#endif
	private:
		VertexBuffer(RenderDevice* renderDevice, u32 vertexSize, u32 vertexCount, BufferUsage bufferUsage, void* initialData = nullptr);

	private:
		u32 m_vertexSize;
		u32 m_vertexCount;
		BufferUsage m_bufferUsage;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}