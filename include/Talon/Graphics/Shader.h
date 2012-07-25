
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/ShaderType.h>
#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	class ConstantBufferBase;
	class Texture;

	class TalonApi Shader : RenderDeviceChild
	{
	public:
		static std::shared_ptr<Shader> CreateFromFile(RenderDevice* device, ShaderType type, const char* filePath);
		static std::shared_ptr<Shader> CreateFromMemory(RenderDevice* device, ShaderType type, const char* shaderText, const char* sourceFileName);

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		static std::shared_ptr<Shader> CreateFromBlob(RenderDevice* device, ShaderType type, ID3DBlob* shaderBytecode, const std::string debugName);

		ID3DBlob* GetShaderBytecode() const;
#	define SHADER_ACCESSOR(type) ID3D11##type##Shader* Get##type##Shader() const;
		SHADER_ACCESSOR(Compute)
		SHADER_ACCESSOR(Domain)
		SHADER_ACCESSOR(Geometry)
		SHADER_ACCESSOR(Hull)
		SHADER_ACCESSOR(Pixel)
		SHADER_ACCESSOR(Vertex)
#	undef SHADER_ACCESSOR
#endif
		
		inline ShaderType GetType() const;

		/** Sets a texture on the current shader instance. */
		void SetTexture(u32 index, std::shared_ptr<Texture> texture);

		/** Sets a buffer of values on the current shader instance. */
		void SetConstantBuffer(u32 index, std::shared_ptr<ConstantBufferBase> buffer);

		~Shader();

	protected:
		explicit Shader(RenderDevice* device, ShaderType type);
		

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;

		ShaderType m_type;
	};

	inline ShaderType Shader::GetType() const
	{
		return m_type;
	}
}