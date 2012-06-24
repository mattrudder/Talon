
#include "TalonPrefix.h"

#include <Talon/Platform/Platform.h>

namespace Talon 
{
	bool Platform::SetWorkingPath(const std::string& path)
	{
        return true;
	}
    
	std::string Platform::GetEnginePath()
	{
		std::string exePath;
        return exePath;
	}
}