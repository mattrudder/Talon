
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>
#include <Talon/Input/InputDeviceType.h>
#include <Talon/Input/InputDeviceEvent.h>
#include <atomic>
#include <queue>

namespace Talon
{
	class TalonApi InputDevice
	{
	public:
		virtual ~InputDevice();

		delegate<InputDevice, void(InputDevice*)> Connected;
		delegate<InputDevice, void(InputDevice*)> Disconnected;

		inline u32 GetId() const { return m_id; }
		inline InputDeviceType GetType() const { return m_type; }
		inline bool IsConnected() const { return m_isConnected; }

		virtual void PollForUpdates();

		struct Kind
		{
		public:
			const char* Name;
			std::vector<std::shared_ptr<InputDevice>> (*Enumerator)(void);
		};

	protected:
		InputDevice(InputDeviceType type);
		void SetIsConnected(bool value);

		void LogEvent(InputDeviceEvent e);

	private:
		static std::atomic<u32> s_deviceIdGenerator;

		u32 m_id;
		bool m_isConnected;
		InputDeviceType m_type;

		std::queue<InputDeviceEvent> m_events;
	};
}