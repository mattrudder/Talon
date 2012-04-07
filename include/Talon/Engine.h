
#include <Talon/TalonPublic.h>
#include <Talon/Platforms/Window.h>

namespace Talon
{
	class TalonApi Engine
	{
	public:
		void Initialize(const char* arguments);
		void Shutdown();
		void RunFrame();

		inline bool IsRunning() const { return m_running; }
		
	private:
		bool m_running;

		std::unique_ptr<Window> m_window;
	};
}