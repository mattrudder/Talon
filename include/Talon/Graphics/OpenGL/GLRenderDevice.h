
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/RenderDeviceBase.h>
#include <functional>

namespace Talon
{
	class TalonApi GLRenderDevice : public RenderDeviceBase
	{
	public:
		typedef RenderDeviceBase Base;

		struct Impl;
		
	private:
		void WithContext(std::function<void()> fn);

	private:
		std::unique_ptr<Impl> m_impl;

#include <Talon/Graphics/OpenGL/Generated/GLRenderDevice.h>
	};
}