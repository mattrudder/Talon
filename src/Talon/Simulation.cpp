
#include <Talon/Simulation.h>

namespace Talon
{
	const std::wstring Simulation::GetTitle() const
	{
		return L"Talon Engine";
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