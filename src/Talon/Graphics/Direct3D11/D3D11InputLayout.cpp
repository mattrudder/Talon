
#include "TalonPrefix.h"

#include <Talon/Graphics/InputLayout.h>

#include "D3D11Utility.h"
#include <Talon/Graphics/InputElement.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Graphics/Shader.h>
#include <Talon/Graphics/ShaderType.h>

namespace Talon
{
	class InputLayout::Impl
	{
	public:
		Impl(ID3D11Device* device, const InputElement* inputElements, u32 elementCount, Shader* vertexShader);

		CComPtr<ID3D11InputLayout> inputLayout;
	};
	
	InputLayout::Impl::Impl(ID3D11Device* device, const InputElement* inputElements, u32 elementCount, Shader* vertexShader)
	{
		TALON_ASSERT(inputElements != nullptr);
 		TALON_ASSERT(elementCount > 0);
 		TALON_ASSERT(vertexShader != nullptr);
 		TALON_ASSERT(vertexShader->GetType() == ShaderType::Vertex);

		D3D11_INPUT_ELEMENT_DESC* pElements = new D3D11_INPUT_ELEMENT_DESC[elementCount];
		for (u32 i = 0; i < elementCount; ++i)
		{
			const InputElement& el = inputElements[i];
			D3D11_INPUT_ELEMENT_DESC& desc = pElements[i];
			desc.SemanticName = el.SemanticName;
			desc.SemanticIndex = el.SemanticIndex;
			desc.Format = D3D11::ToDxgiFormat(el.Format);
			desc.InputSlot = el.InputSlot;
			desc.AlignedByteOffset = el.AlignedByteOffset;
			desc.InputSlotClass = (D3D11_INPUT_CLASSIFICATION)el.InputSlotClass;
			desc.InstanceDataStepRate = el.InstanceDataStepRate;
		}

		ID3DBlob* bytecode = vertexShader->GetShaderBytecode();

		u32 bufferSize = bytecode->GetBufferSize();
		void* buffer = bytecode->GetBufferPointer();

		HRESULT hr = device->CreateInputLayout(pElements, elementCount, buffer, bufferSize, &inputLayout);
		delete [] pElements;

		ThrowIfFailed(hr);
	}

	InputLayout::InputLayout(RenderDevice* device, const InputElement* inputElements, u32 elementCount, Shader* vertexShader)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>(device->GetDevice(), inputElements, elementCount, vertexShader))
 	{
	}

	InputLayout::~InputLayout()
	{
	}
}