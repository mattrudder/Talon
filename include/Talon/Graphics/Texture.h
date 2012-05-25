
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/RenderDeviceChild.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi Texture : RenderDeviceChild
	{
	public:
		static std::shared_ptr<Texture> FromFile(const RenderDevice* device, const std::string fileName);

		Texture(const RenderDevice* device);
		~Texture();

	private:
		bool LoadFromMemory(u32 width, u32 height, BufferFormat format, const void* data);

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}