
#include <Talon/Graphics/Base/RenderDeviceBase.h>

namespace Talon
{
	RenderDeviceBase::RenderDeviceBase(Window* window)
		: m_window(window)
		, m_initialized(0)
	{
	}

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