
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
		IndexBuffer(std::shared_ptr<RenderDevice> renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage);
		virtual ~IndexBuffer();

		BufferFormat GetFormat() const;
		int GetIndexCount() const;
		BufferUsage GetBufferUsage() const;

	private:
		std::weak_ptr<RenderDevice> m_renderDevice;
		BufferFormat m_format;
		int m_indexCount;
		BufferUsage m_bufferUsage;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}