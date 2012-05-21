
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferUsage.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi IndexBufferBase
	{
	public:
		IndexBufferBase(RenderDevice* renderDevice, int indexCount, BufferFormat format, void* initialData, BufferUsage bufferUsage);
		virtual ~IndexBufferBase();

		BufferFormat GetFormat() const;
		int GetIndexCount() const;
		BufferUsage GetBufferUsage() const;

	protected:
		void SetFormat(BufferFormat value);
		void SetIndexCount(int value);
		void SetBufferUsage(BufferUsage value);

	private:
		RenderDevice* m_renderDevice;
		BufferFormat m_format;
		int m_indexCount;
		BufferUsage m_bufferUsage;
	};
}