
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon
{
	/** Base class providing throttled updates to the inherited service. */
	template <typename tService>
	class TalonApi ThrottledService
	{
	public:
		void Update()
		{
			// TODO: Rate limit the call to update
			static_cast<tService>(this)->UpdateCore();
		}

	private:

		
	};
}