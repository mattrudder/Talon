
#include "TalonPrefix.h"
#include "D3D11Utility.h"

#include <Talon/Graphics/InputLayout.h>
#include <Talon/Graphics/ShaderType.h>

namespace Talon
{
	struct InputLayout::Impl
	{
		Impl(ID3D11Device* device, const InputElement* inputElements, u32 elementCount, Shader* vertexShader);

		CComPtr<ID3D11InputLayout> inputLayout;
	};
	
	InputLayout::Impl::Impl(const InputElement* inputElements, u32 elementCount, Shader* vertexShader)
	{
		TALON_ASSERT(inputElements != nullptr);
 		TALON_ASSERT(elementCount > 0);
 		TALON_ASSERT(vertexShader != nullptr);
 		TALON_ASSERT(vertexShader->GetType() == ShaderType::Vertex);

		D3D11_INPUT_ELEMENT_DESC* pElements = new D3D11_INPUT_ELEMENT_DESC[elementCount];
		for (U32 i = 0; i < elementCount; ++i)
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

		D3D11InputLayout* pResult = nullptr;
		ID3D11InputLayout* pLayout = nullptr;
		ID3DBlob* pBytecode = vertexShader->GetShaderBytecode();

		u32 nBufferSize = pBytecode->GetBufferSize();
		void* pBuffer = pBytecode->GetBufferPointer();

		HRESULT hr = device->CreateInputLayout(pElements, elementCount, pBuffer, nBufferSize, &inputLayout);
		delete [] pElements;

		ThrowIfFailed(hr);
	}

	InputLayout::InputLayout(RenderDevice* device, const InputElement* inputElements, u32 elementCount, Shader* vertexShader)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>(device->GetDevice(), inputElements, elementCount, vertexShader))
 	{
	}
}