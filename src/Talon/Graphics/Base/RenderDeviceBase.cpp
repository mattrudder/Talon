
#include <Talon/Graphics/Base/RenderDeviceBase.h>

namespace Talon
{
	RenderDeviceBase::RenderDeviceBase(Window* window)
		: m_window(window)
		, m_initialized(false)
	{
	}

	RenderDeviceBase::~RenderDeviceBase()
	{

	}
}