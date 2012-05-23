
#include <Talon/TalonPublic.h>

namespace Talon
{
	class Simulation;
	class Window;

	class TalonApi Engine
	{
	public:
		bool Initialize(std::shared_ptr<Simulation> sim);
		void Shutdown();
		void RunFrame();

		inline bool IsRunning() const { return m_running; }

	private:
		bool m_running;

		std::shared_ptr<Simulation> m_simulation;
		std::shared_ptr<Window> m_window;
	};
}