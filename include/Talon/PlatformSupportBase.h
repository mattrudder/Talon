
#include <Talon/TalonPublic.h>
#include <Talon/Platforms/Window.h>

namespace Talon
{
	template <class PlatformApi, class WindowType>
	class PlatformSupportBase
	{
		typedef WindowType WindowType;
	public:
		WindowType* CreateWindow(U32 width, U32 height)
		{
			return static_cast<PlatformApi>(this)->CreateWindowCore(width, height);
		}
	};
}