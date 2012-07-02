
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/ShaderType.h>
#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	class ConstantBuffer;
	class Texture;

	class TalonApi Shader : RenderDeviceChild
	{
	public:
		static std::unique_ptr<Shader> CreateFromFile(RenderDevice* device, ShaderType type, const char* filePath);
		static std::unique_ptr<Shader> CreateFromMemory(RenderDevice* device, ShaderType type, const char* shaderText, const char* sourceFileName);

#if TALON_GRAPHICS == TALON_GRAPHICS_DIRECT3D11
		static std::unique_ptr<Shader> CreateFromBlob(RenderDevice* device, ShaderType type, ID3DBlob* shaderBytecode);
#endif
		
		inline ShaderType GetType() const;

		/** Sets a texture on the current shader instance. */
		void SetTexture(u32 index, Texture* texture);

		/** Sets a buffer of values on the current shader instance. */
		void SetConstantBuffer(u32 index, ConstantBuffer* buffer);

	protected:
		explicit Shader(RenderDevice* device, ShaderType type);

	private:
		struct Impl;
		std::unique_ptr<Impl> m_pImpl;

		ShaderType m_type;
	};

	inline ShaderType Shader::GetType() const
	{
		return m_type;
	}
}