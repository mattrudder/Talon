
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>

namespace Talon
{
	class TalonApi InputDevice
	{
	public:
		virtual ~InputDevice();

		delegate<InputDevice, void()> Connected;
		delegate<InputDevice, void()> Disconnected;

		virtual void PollForUpdates() = 0;

		inline bool IsConnected() const { return m_isConnected; }

		struct Kind
		{
		public:
			const char* Name;
			std::vector<std::shared_ptr<InputDevice>> (*Enumerator)(void);
		};

	protected:
		void SetIsConnected(bool value);

	private:
		bool m_isConnected;
	};
}