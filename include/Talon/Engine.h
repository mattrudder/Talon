
#include <Talon/TalonPublic.h>

namespace Talon
{
	class InputManager;
	class Simulation;
	class Window;

	class TalonApi Engine
	{
	public:
		static Engine& Instance();

		bool Initialize(std::shared_ptr<Simulation> sim);
		void Shutdown();
		void RunFrame();

		inline std::shared_ptr<InputManager> GetInputManager() const { return m_inputManager; }

		inline bool IsRunning() const { return m_running; }

	private:
		// Disable creation/copy
		Engine();
		~Engine();
		Engine(const Engine&);
		const Engine& operator=(const Engine&);

		void CreateManagers();

		bool m_running;

		std::shared_ptr<InputManager> m_inputManager;

		std::shared_ptr<Simulation> m_simulation;
		std::shared_ptr<Window> m_window;
	};
}