
#include <Talon/TalonPrefix.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
    class RenderDevice::Impl
    {
    public:

    };

    RenderDevice::RenderDevice(Window* window)
        : m_window(window)
        , m_pImpl(make_unique<Impl>())
    {
	}

	RenderDevice::~RenderDevice()
	{
	}

    void RenderDevice::BeginFrame()
    {
    }

    void RenderDevice::EndFrame()
    {
    }
}