
#pragma once

#include <Talon/TalonPublic.h>


namespace Talon
{
	class RenderDevice;

	class TalonApi VertexBufferBase
	{
	public:
		VertexBufferBase(RenderDevice* renderDevice, int vertexSize);
		virtual ~VertexBufferBase();

		int GetVertexSize() const;

	protected:
		void SetVertexSize(int value);

	private:
		RenderDevice* m_renderDevice;
		int m_vertexSize;
	};
}