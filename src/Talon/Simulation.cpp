
#include "TalonPrefix.h"
#include <Talon/Simulation.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	const std::string Simulation::GetTitle() const
	{
		return "๏̯͡๏ Talon Sandbox ᵔᴥᵔ";
	}

	void Simulation::BeginFrame()
	{
		OnBeginFrame();
	}

	void Simulation::EndFrame()
	{
		OnEndFrame();
	}

	void Simulation::OnBeginFrame()
	{
		FrameStarted();
	}

	void Simulation::OnEndFrame()
	{
		FrameEnded();
	}
}