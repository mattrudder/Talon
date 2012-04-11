
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/RenderDeviceBase.h>

namespace Talon
{
	class TalonApi D3D11RenderDevice : public RenderDeviceBase
	{
	public:
		typedef RenderDeviceBase Base;

		D3D11RenderDevice(Window* window);
		virtual ~D3D11RenderDevice();

	private:
	};
}