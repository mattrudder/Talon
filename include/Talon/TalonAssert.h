
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	typedef enum
	{
		afHalt,
		afContinue,
	} AssertFailBehavior;

	typedef AssertFailBehavior (*AssertHandler)(const char*, const char*, const char*, int);

	TalonApi AssertHandler talonGetAssertHandler();
	TalonApi void talonSetAssertHandler(AssertHandler newHandler);

	TalonApi AssertFailBehavior talonReportFailure(const char* condition, const char* file, int line, const char* msg, ...);
	
#if TALON_MAC
	/** Returns true if the current process is being debugged
	 (either running under the debugger or has a debugger attached post facto).
	 */
	TalonApi bool talonAmIBeingDebugged(void);
#endif
}

#if TALON_WINDOWS
#define TALON_HALT() __debugbreak();
#else
//#define TALON_HALT() __asm__ { int 3 };
#define TALON_HALT() abort();
#endif

#define TALON_UNUSED(x) do { (void) sizeof(x); } while(0)

#ifdef TALON_ASSERTS_ENABLED
#pragma warning(push)
#pragma warning(disable : 4127)

	#define TALON_ASSERT(cond) do \
			{ \
				if (!(cond)) \
				{ \
					if (talonReportFailure(#cond, __FILE__, __LINE__, 0) == afHalt) \
						TALON_HALT(); \
				} \
			} while(0)

	#define TALON_ASSERT_MSG(cond, msg, ...) do \
			{ \
				if (!(cond)) \
				{ \
					if (talonReportFailure(#cond, __FILE__, __LINE__, msg, ##__VA_ARGS__) == afHalt) \
						TALON_HALT(); \
				} \
			} while(0)

	#define TALON_ASSERT_FAIL(msg, ...) do \
			{ \
				if (talonReportFailure(0, __FILE__, __LINE__, msg, ##__VA_ARGS__) == afHalt) \
					TALON_HALT(); \
			} while(0)

#if TALON_WINDOWS
	#define TALON_BREAK() __debugbreak();
#elif TALON_MAC
	#define TALON_BREAK() if(talonAmIBeingDebugged()) {__asm__("int $3\n" : : );}

#endif

	#define TALON_VERIFY(cond) TALON_ASSERT(cond)
	#define TALON_VERIFY_MSG(cond, msg, ...) TALON_ASSERT_MSG(cond, msg, ##__VA_ARGS__)
#pragma warning(pop)
#else
	#define TALON_ASSERT(condition) \
		do { TALON_UNUSED(condition); } while(0)
	#define TALON_ASSERT_MSG(condition, msg, ...) \
		do { TALON_UNUSED(condition); TALON_UNUSED(msg); } while(0)
	#define TALON_ASSERT_FAIL(msg, ...) \
		do { TALON_UNUSED(msg); } while(0)
	#define TALON_BREAK()
	#define TALON_VERIFY(cond)  (void)(cond)
	#define TALON_VERIFY_MSG(cond, msg, ...) \
		do { (void)(cond); TALON_UNUSED(msg); } while(0)
#endif

#define TALON_STATIC_ASSERT(x) typedef char TalonStaticAssert[(x) ? 1 : -1];
#define TALON_STATIC_ASSERT_ISTYPEOF(derived, base) static_cast<base*>((derived*) NULL);
