
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	class RenderDevice;
	class Texture;

	class TalonApi SpriteBatch
	{
	public:
		SpriteBatch(RenderDevice* renderDevice);
		~SpriteBatch();

		void Begin();
		void End();

		void Draw(Texture* texture, f32 x, f32 y);

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}