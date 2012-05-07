
#include <Talon/Graphics/Base/RenderDeviceBase.h>

namespace Talon
{
	RenderDeviceBase::RenderDeviceBase(std::shared_ptr<Window> window)
		: m_window(window)
	{
	}

	RenderDeviceBase::~RenderDeviceBase()
	{
	}

	std::shared_ptr<Window> RenderDeviceBase::GetWindow() const
	{
		return m_window;
	}

	bool RenderDeviceBase::GetInitialized() const
	{
		return m_initialized;
	}

	void RenderDeviceBase::BeginFrame()
	{
	}

	void RenderDeviceBase::EndFrame()
	{
	}

}