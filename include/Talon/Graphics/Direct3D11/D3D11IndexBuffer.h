
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/IndexBufferBase.h>

namespace Talon
{
	class TalonApi D3D11IndexBuffer : public IndexBufferBase
	{
	public:
		typedef IndexBufferBase Base;

	private:
#include <Talon/Graphics/Direct3D11/Generated/D3D11IndexBuffer.h>
	};
}