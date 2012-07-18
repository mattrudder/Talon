
#include "TalonPrefix.h"
#include <Talon/Simulation.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	const std::string Simulation::GetTitle() const
	{
		return "๏̯͡๏ Talon Sandbox ᵔᴥᵔ";
	}

	void Simulation::Initialize()
	{
		OnInitialized();
		Initialized();
	}

	void Simulation::BeginFrame()
	{
		FrameStarted();
		OnBeginFrame();
	}

	void Simulation::EndFrame()
	{
		OnEndFrame();
		FrameEnded();
	}

	void Simulation::Quit()
	{
		OnShutdown();
		Shutdown();
	}

	void Simulation::OnInitialized()
	{
	}

	void Simulation::OnBeginFrame()
	{
	}

	void Simulation::OnEndFrame()
	{
	}

	void Simulation::OnShutdown()
	{
	}
}