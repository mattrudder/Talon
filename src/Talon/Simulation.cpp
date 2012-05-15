
#include <Talon/TalonPrefix.h>
#include <Talon/Simulation.h>

namespace Talon
{
	const std::string Simulation::GetTitle() const
	{
		return "๏̯͡๏ Talon Sandbox ᵔᴥᵔ";
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