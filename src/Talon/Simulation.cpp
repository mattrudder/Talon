
#include <Talon/Simulation.h>

namespace Talon
{
	const std::string Simulation::GetTitle() const
	{
		return "Talon Engine";
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