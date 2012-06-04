
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon
{
	struct RawInputEventArgs
	{
		HRAWINPUT InputHandle;
		PRAWINPUT RawInputData;
		bool IsForeground;
	};
}