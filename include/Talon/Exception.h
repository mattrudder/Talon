
#pragma once

#include <string>
#include <exception>

namespace Talon
{
	class Exception : public std::exception
	{
	public:
		Exception(const char* message)
			: m_message(message)
		{
		}

        virtual const char* what() const throw()
        {
            return m_message.c_str();
        }

    private:
        std::string m_message;
	};
}