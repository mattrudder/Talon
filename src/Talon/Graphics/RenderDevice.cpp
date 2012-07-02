
#include "TalonPrefix.h"
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Graphics/Shader.h>
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

	std::shared_ptr<IndexBuffer> RenderDevice::GetActiveIndexBuffer() const
	{
		return m_activeIndexBuffer;
	}

	std::shared_ptr<VertexBuffer> RenderDevice::GetActiveVertexBuffer() const
	{
		return m_activeVertexBuffer;
	}

	std::shared_ptr<Shader> RenderDevice::GetActiveShader(ShaderType type)
	{
		return m_activeShaders[type];
	}

	void RenderDevice::SetActiveIndexBufferCore(std::shared_ptr<IndexBuffer> value)
	{
		m_activeIndexBuffer = value;
	}

	void RenderDevice::SetActiveVertexBufferCore(std::shared_ptr<VertexBuffer> value)
	{
		m_activeVertexBuffer = value;
	}
	
	void RenderDevice::SetActiveShaderCore(ShaderType type, std::shared_ptr<Shader> value)
	{
		m_activeShaders[type] = value;
	}
}