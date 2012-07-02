
#include "TalonPrefix.h"

#include <Talon/Graphics/Shader.h>

namespace Talon
{
	struct Shader::Impl
	{
		CComPtr<ID3D11Shader> shaderInstance;
		CComPtr<ID3D11ShaderReflection> shaderReflection;
		CComPtr<ID3D11ClassLinkage> classLinkage;
		CComPtr<ID3D11SamplerState> samplerState;
		CComPtr<ID3DBlob> shaderBytecode;
	};

	std::unique_ptr<Shader> Shader::CreateFromFile(RenderDevice* device, ShaderType type, const char* filePath)
	{
		std::unique_ptr<Shader> shader;
		CComPtr<ID3DBlob> errorBlob;
		CComPtr<ID3DBlob> shaderBlob;
		
		if (SUCCEEDED(D3DX11CompileFromFileW(convert(filePath).c_str(), nullptr, nullptr, "FunctionName", "vs_4_0", 0, 0, nullptr, &shaderBlob, &errorBlob, nullptr)))
		{
			shader = CreateFromBlob(device, type, shaderBlob);
			D3D11::SetDebugName(shader->m_pImpl->shaderInstance, filePath);
		}
		//else
		//{
		//	const char* errorText = (const char*)errorBlob->GetBufferPointer();
		//}

		return shader;
	}

	std::unique_ptr<Shader> Shader::CreateFromMemory(RenderDevice* device, ShaderType type, const char* shaderText, const char* sourceFileName)
	{
		std::unique_ptr<Shader> shader;
		CComPtr<ID3DBlob> errorBlob;
		CComPtr<ID3DBlob> shaderBlob;
		
		if (SUCCEEDED(D3DX11CompileFromMemory(shaderText, strlen(shaderText), sourceFileName != nullptr ? sourceFileName : "Talon Internal",
			nullptr, nullptr, "FunctionName", "vs_4_0", 0, 0, nullptr, &shaderBlob, &errorBlob, nullptr)))
		{
			shader = CreateFromBlob(device, type, shaderBlob);
			D3D11::SetDebugName(shader->m_pImpl->shaderInstance, sourceFileName != nullptr ? sourceFileName : "Talon Internal");
		}
		//else
		//{
		//	const char* errorText = (const char*)errorBlob->GetBufferPointer();
		//}

		return shader;
	}

	std::unique_ptr<Shader> Shader::CreateFromBlob(RenderDevice* device, ShaderType type, ID3DBlob* shaderBytecode)
	{
		std::unique_ptr<Shader> shader;
		CComPtr<ID3D11DeviceChild> shaderInstance;
		CComPtr<ID3D11ShaderReflection> shaderReflection;
		CComPtr<ID3D11ClassLinkage> classLinkage;

		ID3D11Device* d3d = device->GetDevice();

#define CHECK_SHADER_TYPE(type) \
        case ShaderType::##type##: \
                { \
                        ID3D11##type##Shader* shader = NULL; \
                        if (SUCCEEDED(device->Create##type##Shader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), linkage, &shader))) \
                                shaderInstance = shader; \
                } \
                break;

		switch (type)
		{
		CHECK_SHADER_TYPE(Compute)
		CHECK_SHADER_TYPE(Domain)
		CHECK_SHADER_TYPE(Geometry)
		CHECK_SHADER_TYPE(Hull)
		CHECK_SHADER_TYPE(Pixel)
		CHECK_SHADER_TYPE(Vertex)
		}
#undef CHECK_SHADER_TYPE

		if (shaderInstance)
		{
			if (!SUCCEEDED(D3DReflect(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection)))
				TalonLog("D3D11Shader::CreateFromBlob: Unable to retrieve shader reflection metadata.");

			D3D11_SAMPLER_DESC descSampler;
			descSampler.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			descSampler.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
			descSampler.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
			descSampler.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
			descSampler.MinLOD = -FLT_MAX;
			descSampler.MaxLOD = FLT_MAX;
			descSampler.MipLODBias = 0.0f;
			descSampler.MaxAnisotropy = 16;
			descSampler.ComparisonFunc = D3D11_COMPARISON_NEVER;
			descSampler.BorderColor[0] = 0.0f;
			descSampler.BorderColor[1] = 0.0f;
			descSampler.BorderColor[2] = 0.0f;
			descSampler.BorderColor[3] = 0.0f;

			ID3D11SamplerState* samplerState;
			if (!SUCCEEDED(device->CreateSamplerState(&descSampler, &samplerState)))
				TalonLog("D3D11Shader::CreateFromBlob: Unable to create sampler state.");

			shader = std::make_unique<Shader>(context, type);
			shader->m_pImpl->shaderInstance = shaderInstance;
			shader->m_pImpl->reflection = reflection;
			shader->m_pImpl->shaderBytecode = shaderBytecode;
			shader->m_pImpl->samplerState = samplerState;
		}
		return shader;
	}

	/** Sets a texture on the current shader instance. */
	void Shader::SetTexture(u32 index, Texture* texture)
	{
		ID3D11ShaderResourceView* resourceView = texture != nullptr ? texture->GetResourceView() : nullptr;
		ID3D11DeviceContext* context = GetRenderDevice()->GetContext();
		switch(GetType())
		{
		case ShaderTypes::Compute:
			context->CSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderTypes::Domain:
			context->DSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderTypes::Geometry:
			context->GSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderTypes::Hull:
			context->HSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderTypes::Pixel:
			context->PSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderTypes::Vertex:
			context->VSSetShaderResources(index, 1, &resourceView);
			break;
		}
	}

	/** Sets a buffer of values on the current shader instance. */
	void Shader::SetConstantBuffer(u32 index, ConstantBuffer* buffer)
	{
		ID3D11Buffer* bufferD3D = buffer != nullptr ? buffer->GetConstantBuffer() : nullptr;
		ID3D11DeviceContext* context = GetRenderDevice()->GetContext();
		switch(GetType())
		{
		case ShaderTypes::Compute:
			context->CSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderTypes::Domain:
			context->DSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderTypes::Geometry:
			context->GSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderTypes::Hull:
			context->HSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderTypes::Pixel:
			context->PSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderTypes::Vertex:
			context->VSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		}
	}

	explicit Shader::Shader(RenderDevice* device, ShaderType type)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>())
		, m_type(type)
	{
	}
}