
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferUsage.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi IndexBuffer
	{
	public:
		IndexBuffer(RenderDevice* renderDevice, u32 indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage);
		virtual ~IndexBuffer();

		BufferFormat GetFormat() const;
		int GetIndexCount() const;
		BufferUsage GetBufferUsage() const;

		void Update(u32 indexCount, void* indexData);

	private:
		RenderDevice* m_renderDevice;
		BufferFormat m_format;
		u32 m_indexCount;
		BufferUsage m_bufferUsage;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}