
#include "TalonPrefix.h"

#include <Talon/Graphics/InputLayout.h>
#include <Talon/Graphics/ShaderType.h>

namespace Talon
{
	struct InputLayout::Impl
	{
	};
	
	InputLayout::InputLayout(RenderDevice* device, const InputElement* inputElements, u32 elementCount, Shader* vertexShader)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>())
 	{
 		TALON_ASSERT(inputElements != nullptr);
 		TALON_ASSERT(elementCount > 0);
 		TALON_ASSERT(vertexShader != nullptr);
 		TALON_ASSERT(vertexShader->GetType() != ShaderType::Vertex);
	}
}