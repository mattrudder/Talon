
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/Base/RenderDeviceBase.h>
#include <Talon/Platform/Window.h>

namespace Talon
{
// TODO: Code generation should mark unused parameters as such.
#pragma warning(push)
#pragma warning(disable : 4100)
	RenderDeviceBase::RenderDeviceBase(Window* window)
		: m_window(window)
		, m_initialized(false)
	{
	}
#pragma warning(pop)
	RenderDeviceBase::~RenderDeviceBase()
	{
	}

	Window* RenderDeviceBase::GetWindow() const
	{
		return m_window;
	}


	void RenderDeviceBase::SetWindow(Window* value)
	{
		m_window = value;
	}

	bool RenderDeviceBase::IsInitialized() const
	{
		return m_initialized;
	}


	void RenderDeviceBase::SetInitialized(bool value)
	{
		m_initialized = value;
	}

	void RenderDeviceBase::BeginFrame()
	{
	}

	void RenderDeviceBase::EndFrame()
	{
	}

}