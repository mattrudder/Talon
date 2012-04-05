
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/GraphicsSupportImpl.h>

#if TALON_WINDOWS
#	include <Talon/Graphics/Direct3D11GraphicsSupport.h>
#endif

namespace Talon
{
#if TALON_WINDOWS
	typedef GraphicsSupportImpl<Direct3D11GraphicsSupport> GraphicsSupport;
#else
#	error GraphicsSupport is undefined for this platform.
#endif
}