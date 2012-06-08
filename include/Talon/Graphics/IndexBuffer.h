
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/BufferMapType.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi IndexBuffer
	{
	public:
		IndexBuffer(RenderDevice* renderDevice, u32 indexCount, BufferFormat format, BufferUsage bufferUsage, void* initialData = nullptr);
		virtual ~IndexBuffer();

		BufferFormat GetFormat() const;
		int GetIndexCount() const;
		BufferUsage GetBufferUsage() const;

		void Update(u32 indexCount, void* indexData);
		void Map(BufferMapType mapType, void** ppData);
		void Unmap();

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		ID3D11Buffer* GetBuffer() const;
#endif

	private:
		RenderDevice* m_renderDevice;
		BufferFormat m_format;
		u32 m_indexCount;
		BufferUsage m_bufferUsage;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}