
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Exception.h>

#define ThrowIfFailed(expr) Talon::ComException::CheckResult(expr, #expr, __FILE__, __LINE__)

namespace Talon
{
	class ComException : public Exception
	{
	public:
		explicit ComException(HRESULT status, LPCSTR expression, LPCSTR file, UINT line)
			: Exception("COM Exception")
			, m_status(status)
			, m_expression(expression)
			, m_file(file)
			, m_line(line)
		{
		}

		static inline HRESULT CheckResult(HRESULT status, LPCSTR expression, LPCSTR file, UINT line)
		{
			if (FAILED(status))
				throw ComException(status, expression, file, line);
			return status;
		}

	private:
		HRESULT m_status;
		LPCSTR m_expression;
		LPCSTR m_file;
		UINT m_line;
	};
}