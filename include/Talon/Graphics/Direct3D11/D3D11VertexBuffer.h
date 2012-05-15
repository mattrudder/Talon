
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/VertexBufferBase.h>

namespace Talon
{
	class TalonApi D3D11VertexBuffer : public VertexBufferBase
	{
	public:
		typedef VertexBufferBase Base;

	private:
#include <Talon/Graphics/Direct3D11/Generated/D3D11VertexBuffer.h>
	};
}