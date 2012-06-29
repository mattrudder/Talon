
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi Texture : RenderDeviceChild
	{
	public:
		static std::shared_ptr<Texture> FromFile(const RenderDevice* device, const std::string fileName);
		static std::shared_ptr<Texture> FromMemory(const RenderDevice* device, u32 width, u32 height, BufferFormat format, BufferUsage usage, const void* data, const std::string debugName);

		void Update(const void* data);

		u32 GetWidth() const;
		u32 GetHeight() const;

		Texture(const RenderDevice* device);
		~Texture();

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		ID3D11ShaderResourceView* GetShaderResourceView() const;
#endif

	private:
		bool Load(u32 width, u32 height, BufferFormat format, BufferUsage usage, const void* data, const std::string debugName);

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}