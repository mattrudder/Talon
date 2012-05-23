
#pragma once

#include <Talon/TalonPublic.h>
#include <exception>

namespace Talon
{
	class Exception : public std::exception
	{
	public:
		Exception(const char* message)
			: exception(message)
		{
		}
	};
}