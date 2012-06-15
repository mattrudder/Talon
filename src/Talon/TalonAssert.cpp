#include "TalonPrefix.h"
#include <Talon/TalonAssert.h>

//#include <stdio.h>
#include <stdarg.h>
#if TALON_MAC
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sysctl.h>
#endif

namespace Talon
{
	AssertFailBehavior DefaultAssertHandler(const char* condition, const char* msg, const char* file, const int line)
	{
		printf("%s(%d): Assert Failure: ", file, line);

		if (condition != NULL)
			printf("'%s' ", condition);

		if (msg != NULL)
			printf("%s", msg);

		printf("\n");

		return afHalt;
	}

	AssertHandler* GetAssertHandlerInstance()
	{
		static AssertHandler s_handler = &DefaultAssertHandler;
		return &s_handler;
	}

	AssertHandler GetAssertHandler()
	{
		return *GetAssertHandlerInstance();
	}

	void SetAssertHandler(AssertHandler newHandler)
	{
		*GetAssertHandlerInstance() = newHandler;
	}

	AssertFailBehavior talonReportFailure(const char* condition, const char* file, int line, const char* msg, ...)
	{
		const char* message = NULL;
		if (msg != NULL)
		{
			char messageBuffer[1024];
			{
				va_list args;
				va_start(args, msg);
#if TALON_WINDOWS
				vsnprintf_s(messageBuffer, 1024, msg, args);
#else
				vsnprintf(messageBuffer, 1024, msg, args);
#endif
				va_end(args);
			}

			message = messageBuffer;
		}

		return (*GetAssertHandlerInstance())(condition, message, file, line);
	}

#if TALON_MAC
	bool talonAmIBeingDebugged(void)
	{
		int                 junk;
		int                 mib[4];
		struct kinfo_proc   info;
		size_t              size;

		// Initialize the flags so that, if sysctl fails for some bizarre
		// reason, we get a predictable result.

		info.kp_proc.p_flag = 0;

		// Initialize mib, which tells sysctl the info we want, in this case
		// we're looking for information about a specific process ID.

		mib[0] = CTL_KERN;
		mib[1] = KERN_PROC;
		mib[2] = KERN_PROC_PID;
		mib[3] = getpid();

		// Call sysctl.

		size = sizeof(info);
		junk = sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, NULL, 0);
		assert(junk == 0);

		// We're being debugged if the P_TRACED flag is set.
		return ( (info.kp_proc.p_flag & P_TRACED) != 0 );
	}
#endif
}