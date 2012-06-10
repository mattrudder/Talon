
#include "TalonPrefix.h"

#include <Talon/Platform/Platform.h>

namespace Talon 
{
	bool Platform::SetWorkingPath(const std::string& path)
	{
		return SetCurrentDirectory(convert(path).c_str()) == TRUE;
	}

	std::string Platform::GetEnginePath()
	{
		std::string exePath(_pgmptr);
		return exePath.substr(0, exePath.find_last_of('\\') + 1);
	}
}