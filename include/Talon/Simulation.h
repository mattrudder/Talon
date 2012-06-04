
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi Simulation
	{
	public:
		friend class Engine;

		void Initialize();
		void BeginFrame();
		void EndFrame();

		delegate<Simulation, void()> Initialized;
		delegate<Simulation, void()> FrameStarted;
		delegate<Simulation, void()> FrameEnded;

		// HACKS!
		RenderDevice* Device;

	protected:
		virtual const std::string GetTitle() const;

		virtual void OnInitialized();
		virtual void OnBeginFrame();
		virtual void OnEndFrame();

	private:
	};
}