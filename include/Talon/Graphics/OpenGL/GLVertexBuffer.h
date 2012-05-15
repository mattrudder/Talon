
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/VertexBufferBase.h>

namespace Talon
{
	class TalonApi GLVertexBuffer : public VertexBufferBase
	{
	public:
		typedef VertexBufferBase Base;

	private:
#include <Talon/Graphics/OpenGL/Generated/GLVertexBuffer.h>
	};
}