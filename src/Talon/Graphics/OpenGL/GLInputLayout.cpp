
#include "TalonPrefix.h"

#include <Talon/Graphics/InputLayout.h>
#include <Talon/Graphics/ShaderType.h>
#include <Talon/Graphics/Shader.h>

namespace Talon
{
	class InputLayout::Impl
	{
	};
	
	std::shared_ptr<InputLayout> InputLayout::Create(Talon::RenderDevice* device, const Talon::InputElement* inputElements, u32 elementCount, std::shared_ptr<Shader> vertexShader)
	{
		return std::shared_ptr<InputLayout>(new InputLayout(device, inputElements, elementCount, vertexShader));
	}
	
	InputLayout::InputLayout(RenderDevice* device, const InputElement* inputElements, u32 elementCount, std::shared_ptr<Shader> vertexShader)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>())
 	{
		return;
 		TALON_ASSERT(inputElements != nullptr);
 		TALON_ASSERT(elementCount > 0);
 		TALON_ASSERT(vertexShader != nullptr);
 		TALON_ASSERT(vertexShader->GetType() != ShaderType::Vertex);
	}
	
	InputLayout::~InputLayout()
	{
	}
}