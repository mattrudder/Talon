
#pragma once
#include <Talon/Input/InputDevice.h>

namespace Talon
{
	class RawInputDevice : public InputDevice
	{
	public:
		static Kind Kind;

		static std::vector<std::shared_ptr<InputDevice>> Enumerate();

		~RawInputDevice();

	private:
		RawInputDevice();
	};
}