
#include "TalonPrefix.h"
#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	RenderDeviceChild::RenderDeviceChild(const RenderDevice* device)
		: m_device(device)
	{
	}

	RenderDeviceChild::~RenderDeviceChild()
	{
	}
}