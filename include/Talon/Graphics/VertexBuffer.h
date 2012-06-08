
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/BufferMapType.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi VertexBuffer
	{
	public:
		VertexBuffer(RenderDevice* renderDevice, u32 vertexSize, u32 vertexCount, BufferUsage bufferUsage, void* initialData = nullptr);
		virtual ~VertexBuffer();

		int GetVertexSize() const;
		int GetVertexCount() const;
		BufferUsage GetBufferUsage() const;

		void Update(int vertexCount, void* vertexData);
		void Map(BufferMapType mapType, void** ppData);
		void Unmap();

	private:
		RenderDevice* m_renderDevice;
		u32 m_vertexSize;
		u32 m_vertexCount;
		BufferUsage m_bufferUsage;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}