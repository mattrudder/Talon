
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/BufferUsage.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi VertexBufferBase
	{
	public:
		VertexBufferBase(RenderDevice* renderDevice, int vertexSize, int vertexCount, void* initialData, BufferUsage bufferUsage);
		virtual ~VertexBufferBase();

		int GetVertexSize() const;
		int GetVertexCount() const;
		BufferUsage GetBufferUsage() const;

	protected:
		void SetVertexSize(int value);
		void SetVertexCount(int value);
		void SetBufferUsage(BufferUsage value);

	private:
		RenderDevice* m_renderDevice;
		int m_vertexSize;
		int m_vertexCount;
		BufferUsage m_bufferUsage;
	};
}