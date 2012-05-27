
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>
#include <Talon/Input/InputDeviceType.h>

namespace Talon
{
	class TalonApi InputDevice
	{
	public:
		virtual ~InputDevice();

		delegate<InputDevice, void()> Connected;
		delegate<InputDevice, void()> Disconnected;

		virtual void PollForUpdates() = 0;

		inline InputDeviceType GetType() const { return m_type; }
		inline bool IsConnected() const { return m_isConnected; }

		struct Kind
		{
		public:
			const char* Name;
			std::vector<std::shared_ptr<InputDevice>> (*Enumerator)(void);
		};

	protected:
		InputDevice(InputDeviceType type);
		void SetIsConnected(bool value);

	private:
		bool m_isConnected;
		InputDeviceType m_type;
	};
}