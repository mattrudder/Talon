
#include "TalonPrefix.h"

#include <Talon/Graphics/Shader.h>

#include <Talon/Graphics/ConstantBuffer.h>
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/RenderDevice.h>

#include "D3D11Utility.h"

namespace Talon
{
	class Shader::Impl
	{
	public:
		CComPtr<ID3D11DeviceChild> shaderInstance;
		CComPtr<ID3D11ShaderReflection> shaderReflection;
		CComPtr<ID3D11ClassLinkage> classLinkage;
		CComPtr<ID3D11SamplerState> samplerState;
		CComPtr<ID3DBlob> shaderBytecode;
	};

	std::shared_ptr<Shader> Shader::CreateFromFile(RenderDevice* device, ShaderType type, const char* filePath)
	{
		std::shared_ptr<Shader> shader;
		CComPtr<ID3DBlob> errorBlob;
		CComPtr<ID3DBlob> shaderBlob;

		if (SUCCEEDED(D3DCompileFromFile(convert(filePath).c_str(),
			nullptr, nullptr, D3D11::ToShaderEntryPoint(type), D3D11::ToShaderLevel(type), 0, 0, &shaderBlob, &errorBlob)))
		{
			shader = Shader::CreateFromBlob(device, type, shaderBlob);
			D3D11::SetDebugName(shader->m_pImpl->shaderInstance, filePath);
		}
		else
		{
			const char* errorText = (const char*)errorBlob->GetBufferPointer();
			TalonLog(errorText);
		}

		return shader;
	}

	std::shared_ptr<Shader> Shader::CreateFromMemory(RenderDevice* device, ShaderType type, const char* shaderText, const char* sourceFileName)
	{
		std::shared_ptr<Shader> shader;
		CComPtr<ID3DBlob> errorBlob;
		CComPtr<ID3DBlob> shaderBlob;

		if (SUCCEEDED(D3DCompile(shaderText, strlen(shaderText), sourceFileName != nullptr ? sourceFileName : "Talon Internal",
			nullptr, nullptr, D3D11::ToShaderEntryPoint(type), D3D11::ToShaderLevel(type), 0, 0, &shaderBlob, &errorBlob)))
		{
			shader = CreateFromBlob(device, type, shaderBlob);
			D3D11::SetDebugName(shader->m_pImpl->shaderInstance, sourceFileName != nullptr ? sourceFileName : "Talon Internal");
		}
		else
		{
			const char* errorText = (const char*)errorBlob->GetBufferPointer();
			TalonLog(errorText);
		}

		return shader;
	}

	std::shared_ptr<Shader> Shader::CreateFromBlob(RenderDevice* device, ShaderType type, ID3DBlob* shaderBytecode)
	{
		std::shared_ptr<Shader> shader;
		CComPtr<ID3D11DeviceChild> shaderInstance;
		CComPtr<ID3D11ShaderReflection> shaderReflection;
		CComPtr<ID3D11ClassLinkage> classLinkage;

		ID3D11Device* d3d = device->GetDevice();

#define CHECK_SHADER_TYPE(type) \
        case ShaderType::##type##: \
		{ \
		ID3D11##type##Shader* s = NULL; \
		if (SUCCEEDED(d3d->Create##type##Shader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), classLinkage, &s))) \
		shaderInstance = s; \
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
			if (!SUCCEEDED(D3DReflect(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection)))
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
			if (!SUCCEEDED(d3d->CreateSamplerState(&descSampler, &samplerState)))
				TalonLog("D3D11Shader::CreateFromBlob: Unable to create sampler state.");

			shader = std::shared_ptr<Shader>(new Shader(device, type));
			shader->m_pImpl->shaderInstance = shaderInstance;
			shader->m_pImpl->shaderReflection = shaderReflection;
			shader->m_pImpl->shaderBytecode = shaderBytecode;
			shader->m_pImpl->samplerState = samplerState;
		}
		return shader;
	}

	/** Sets a texture on the current shader instance. */
	void Shader::SetTexture(u32 index, std::shared_ptr<Texture> texture)
	{
		ID3D11ShaderResourceView* resourceView = texture != nullptr ? texture->GetShaderResourceView() : nullptr;
		ID3D11DeviceContext* context = GetParent()->GetDeviceContext();
		switch(GetType())
		{
		case ShaderType::Compute:
			context->CSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderType::Domain:
			context->DSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderType::Geometry:
			context->GSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderType::Hull:
			context->HSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderType::Pixel:
			context->PSSetShaderResources(index, 1, &resourceView);
			break;
		case ShaderType::Vertex:
			context->VSSetShaderResources(index, 1, &resourceView);
			break;
		}
	}

	/** Sets a buffer of values on the current shader instance. */
	void Shader::SetConstantBuffer(u32 index, std::shared_ptr<ConstantBufferBase> buffer)
	{
		ID3D11Buffer* bufferD3D = buffer != nullptr ? buffer->GetBuffer() : nullptr;
		ID3D11DeviceContext* context = GetParent()->GetDeviceContext();
		switch(GetType())
		{
		case ShaderType::Compute:
			context->CSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderType::Domain:
			context->DSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderType::Geometry:
			context->GSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderType::Hull:
			context->HSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderType::Pixel:
			context->PSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		case ShaderType::Vertex:
			context->VSSetConstantBuffers(index, 1, &bufferD3D);
			break;
		}
	}

	Shader::Shader(RenderDevice* device, ShaderType type)
		: RenderDeviceChild(device)
		, m_pImpl(std::make_unique<Impl>())
		, m_type(type)
	{
	}

	Shader::~Shader()
	{
	}

	ID3DBlob* Shader::GetShaderBytecode() const
	{
		return m_pImpl->shaderBytecode;
	}

#define SHADER_ACCESSOR(type) \
	ID3D11##type##Shader* Shader::Get##type##Shader() const\
	{\
	ID3D11##type##Shader* p = nullptr;\
	\
	if (GetType() == ShaderType::##type##)\
	m_pImpl->shaderInstance.QueryInterface(&p);\
	\
	return p;\
	}

	SHADER_ACCESSOR(Compute)
		SHADER_ACCESSOR(Domain)
		SHADER_ACCESSOR(Geometry)
		SHADER_ACCESSOR(Hull)
		SHADER_ACCESSOR(Pixel)
		SHADER_ACCESSOR(Vertex)
#undef SHADER_ACCESSOR
}