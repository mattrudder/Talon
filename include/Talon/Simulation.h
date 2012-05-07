
#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>

namespace Talon
{
	class TalonApi Simulation
	{
	public:
		friend class Engine;

		delegate<Simulation, void()> FrameStarted;
		delegate<Simulation, void()> FrameEnded;

	protected:
		virtual const std::string GetTitle() const;

		virtual void OnBeginFrame();
		virtual void OnEndFrame();

	private:
	};
}