
#pragma once

namespace Talon
{
	template <int v>
	struct Int2Type
	{
		enum { value = v; };
	};
}