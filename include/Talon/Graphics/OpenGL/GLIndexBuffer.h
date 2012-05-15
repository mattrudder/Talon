
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/IndexBufferBase.h>

namespace Talon
{
	class TalonApi GLIndexBuffer : public IndexBufferBase
	{
	public:
		typedef IndexBufferBase Base;

	private:
#include <Talon/Graphics/OpenGL/Generated/GLIndexBuffer.h>
	};
}