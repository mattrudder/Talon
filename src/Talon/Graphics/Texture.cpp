
#include "TalonPrefix.h"
#include <Talon/Graphics/Texture.h>
#include <FreeImage.h>

namespace Talon
{
	std::shared_ptr<Texture> Texture::FromFile(const RenderDevice* device, const std::string fileName)
	{
		TalonLog("WARN: Files loaded with Texture::FromFile convert the file to 32-bit\n");

		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(fileName.c_str());
		FIBITMAP* bmp = FreeImage_Load(fif, fileName.c_str());
		FIBITMAP* conversion = FreeImage_ConvertTo32Bits(bmp);
		FreeImage_Unload(bmp);
		bmp = conversion;

		u32 bpp = FreeImage_GetBPP(bmp) / 8;
		FREE_IMAGE_TYPE type = FreeImage_GetImageType(bmp);
		if (type != FIT_BITMAP)
			return nullptr;
		
		TALON_ASSERT(FreeImage_GetWidth(bmp) == FreeImage_GetPitch(bmp) / bpp);

		std::shared_ptr<Texture> texture = std::make_shared<Texture>(device);
		if (!texture->LoadFromMemory(FreeImage_GetWidth(bmp), FreeImage_GetHeight(bmp), BufferFormat::R8G8B8A8U, FreeImage_GetBits(bmp)))
			texture = nullptr;

		FreeImage_Unload(bmp);
		return texture;
	}
}