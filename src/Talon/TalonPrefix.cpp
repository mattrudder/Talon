
#include "TalonPrefix.h"
using namespace Talon;

#ifdef TALON_ALLOCATORS_ONLY
namespace {
	void* operator new(size_t /*size*/)
	{
		TALON_ASSERT(__LINE__ == -1);
		return nullptr;
	}
}
#endif