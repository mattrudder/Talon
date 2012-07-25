
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
			std::string debugName = filePath;
			shader = Shader::CreateFromBlob(device, type, shaderBlob, "Shader: " + debugName);
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
			std::string debugName = sourceFileName != nullptr ? sourceFileName : "Talon Internal";
			shader = CreateFromBlob(device, type, shaderBlob, "Shader: " + debugName);
		}
		else
		{
			const char* errorText = (const char*)errorBlob->GetBufferPointer();
			TalonLog(errorText);
		}

		return shader;
	}

	std::shared_ptr<Shader> Shader::CreateFromBlob(RenderDevice* device, ShaderType type, ID3DBlob* shaderBytecode, const std::string debugName)
	{
		std::shared_ptr<Shader> shader;
		CComPtr<ID3D11DeviceChild> shaderInstance;
		CComPtr<ID3D11ShaderReflection> shaderReflection;
		CComPtr<ID3D11ClassLinkage> classLinkage;

		ID3D11Device* d3d = device->GetDevice();

		switch(type)
		{
		case ShaderType::Compute:
			{
				CComPtr<ID3D11ComputeShader> s = nullptr;
				if (SUCCEEDED(d3d->CreateComputeShader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), classLinkage, &s)))
					shaderInstance = s;
			}
			break;
		case ShaderType::Domain:
			{
				CComPtr<ID3D11DomainShader> s = nullptr;
				if (SUCCEEDED(d3d->CreateDomainShader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), classLinkage, &s)))
					shaderInstance = s;
			}
			break;
		case ShaderType::Geometry:
			{
				CComPtr<ID3D11GeometryShader> s = nullptr;
				if (SUCCEEDED(d3d->CreateGeometryShader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), classLinkage, &s)))
					shaderInstance = s;
			}
			break;
		case ShaderType::Hull:
			{
				CComPtr<ID3D11HullShader> s = nullptr;
				if (SUCCEEDED(d3d->CreateHullShader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), classLinkage, &s)))
					shaderInstance = s;
			}
			break;
		case ShaderType::Pixel:
			{
				CComPtr<ID3D11PixelShader> s = nullptr;
				if (SUCCEEDED(d3d->CreatePixelShader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), classLinkage, &s)))
					shaderInstance = s;
			}
			break;
		case ShaderType::Vertex:
			{
				CComPtr<ID3D11VertexShader> s = nullptr;
				if (SUCCEEDED(d3d->CreateVertexShader(shaderBytecode->GetBufferPointer(), shaderBytecode->GetBufferSize(), classLinkage, &s)))
					shaderInstance = s;
			}
			break;
		}

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

			CComPtr<ID3D11SamplerState> samplerState;
			if (!SUCCEEDED(d3d->CreateSamplerState(&descSampler, &samplerState)))
				TalonLog("D3D11Shader::CreateFromBlob: Unable to create sampler state.");

			shader = std::shared_ptr<Shader>(new Shader(device, type));
			shader->m_pImpl->shaderInstance = shaderInstance;
			shader->m_pImpl->shaderReflection = shaderReflection;
			shader->m_pImpl->shaderBytecode = shaderBytecode;
			shader->m_pImpl->samplerState = samplerState;

			D3D11::SetDebugName(samplerState, debugName);
			D3D11::SetDebugName(shaderInstance, debugName);
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

	ID3D11ComputeShader* Shader::GetComputeShader() const
	{
		CComPtr<ID3D11ComputeShader> p = nullptr;

		if (GetType() == ShaderType::Compute)
			m_pImpl->shaderInstance.QueryInterface(&p);

		return p;
	}

	ID3D11DomainShader* Shader::GetDomainShader() const
	{
		CComPtr<ID3D11DomainShader> p = nullptr;

		if (GetType() == ShaderType::Domain)
			m_pImpl->shaderInstance.QueryInterface(&p);

		return p;
	}
	
	ID3D11GeometryShader* Shader::GetGeometryShader() const
	{
		CComPtr<ID3D11GeometryShader> p = nullptr;

		if (GetType() == ShaderType::Geometry)
			m_pImpl->shaderInstance.QueryInterface(&p);

		return p;
	}

	ID3D11HullShader* Shader::GetHullShader() const
	{
		CComPtr<ID3D11HullShader> p = nullptr;

		if (GetType() == ShaderType::Hull)
			m_pImpl->shaderInstance.QueryInterface(&p);

		return p;
	}

	ID3D11PixelShader* Shader::GetPixelShader() const
	{
		CComPtr<ID3D11PixelShader> p = nullptr;

		if (GetType() == ShaderType::Pixel)
			m_pImpl->shaderInstance.QueryInterface(&p);

		return p;
	}

	ID3D11VertexShader* Shader::GetVertexShader() const
	{
		CComPtr<ID3D11VertexShader> p = nullptr;

		if (GetType() == ShaderType::Vertex)
			m_pImpl->shaderInstance.QueryInterface(&p);

		return p;
	}
}