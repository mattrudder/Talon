
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/RenderDeviceBase.h>

namespace Talon
{
	class TalonApi D3D11RenderDevice : public RenderDeviceBase
	{
	public:
		typedef RenderDeviceBase Base;

	private:
#include <Talon/Graphics/Direct3D11/Generated/D3D11RenderDevice.h>
	};
}