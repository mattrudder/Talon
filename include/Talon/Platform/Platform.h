
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon { namespace Platform
{
	bool SetWorkingPath(const std::string& path);
	std::string GetEnginePath();
	std::string GetResourcePath(const std::string& fileName);
	
	std::string GetTextFromFile(const std::string& fileName);
}}