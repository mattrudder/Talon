
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi RenderDeviceChild
	{
	public:
		RenderDeviceChild(const RenderDevice* device);
		~RenderDeviceChild();

		inline const RenderDevice* GetParent() const { return m_device; }

	private:
		// disable copying
		RenderDeviceChild(const RenderDeviceChild&);
		RenderDeviceChild& operator=(const RenderDeviceChild&);

		const RenderDevice* m_device;
	};
}