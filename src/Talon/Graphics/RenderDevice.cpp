
#include "TalonPrefix.h"
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/VertexBuffer.h>
#include <Talon/Platform/Window.h>

namespace Talon
{
	Window* RenderDevice::GetWindow() const
	{
		return m_window;
	}

	void RenderDevice::SetWindow(Window* value)
	{
		m_window = value;
	}

	bool RenderDevice::IsInitialized() const
	{
		return m_initialized;
	}

	void RenderDevice::SetInitialized(bool value)
	{
		m_initialized = value;
	}

	IndexBuffer* RenderDevice::GetActiveIndexBuffer() const
	{
		return m_activeIndexBuffer;
	}

	void RenderDevice::SetActiveIndexBuffer(IndexBuffer* value)
	{
		m_activeIndexBuffer = value;
	}

	VertexBuffer* RenderDevice::GetActiveVertexBuffer() const
	{
		return m_activeVertexBuffer;
	}

	void RenderDevice::SetActiveVertexBuffer(VertexBuffer* value)
	{
		m_activeVertexBuffer = value;
	}
}