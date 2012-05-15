
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferFormat.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi IndexBufferBase
	{
	public:
		IndexBufferBase(RenderDevice* renderDevice, BufferFormat format);
		virtual ~IndexBufferBase();

		BufferFormat GetFormat() const;

	protected:
		void SetFormat(BufferFormat value);

	private:
		RenderDevice* m_renderDevice;
		BufferFormat m_format;
	};
}