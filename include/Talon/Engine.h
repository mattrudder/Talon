
#include <Talon/TalonPublic.h>

namespace Talon
{
	class ComponentService;
	class InputService;
	class Simulation;
	class Window;

	class TalonApi Engine
	{
	public:
		static Engine* Instance();

		bool Initialize(std::shared_ptr<Simulation> sim);
		void Shutdown();
		void RunFrame();

		inline std::shared_ptr<InputService> GetInputService() const { return m_inputService; }
		inline std::shared_ptr<ComponentService> GetComponentService() const { return m_componentService; }

		inline bool IsRunning() const { return m_running; }

	private:
		// Disable creation/copy
		Engine();
		~Engine();
		Engine(const Engine&);
		const Engine& operator=(const Engine&);

		void CreateServices();
		void UpdateServices();
		void DestroyServices();

		bool m_running;

		std::shared_ptr<InputService> m_inputService;
		std::shared_ptr<ComponentService> m_componentService;

		std::shared_ptr<Simulation> m_simulation;
		std::shared_ptr<Window> m_window;

		struct TimedUpdate
		{
			TimedUpdate(float frequency, std::function<void()> func)
				: UpdateFrequency(frequency)
				, SinceLastUpdate(0)
				, UpdateFunc(func)
			{
			}

			float UpdateFrequency;
			float SinceLastUpdate;
			std::function<void()> UpdateFunc;
		};

		std::vector<TimedUpdate> m_serviceUpdates;
	};
}