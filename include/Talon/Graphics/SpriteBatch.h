
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	class RenderDevice;
	class Texture;

	enum class SpriteSortMode
	{
		Deferred,
		Immediate,
		Texture,
		BackToFront,
		FrontToBack,
	};

	enum class SpriteEffects
	{
		None = 0,
		FlipHorizontally = 1,
		FlipVertically = 2,
		FlipBoth = FlipHorizontally | FlipVertically,
	};

	struct Rect
	{
		i32 left;
		i32 top;
		i32 width;
		i32 height;
	};

	struct RectF
	{
		float left;
		float top;
		float width;
		float height;
	};

	class TalonApi SpriteBatch
	{
	public:
		SpriteBatch(RenderDevice* renderDevice);
		~SpriteBatch();

		void Begin();
		void End();

		void Draw(std::shared_ptr<Texture> texture, float x, float y);
		void Draw(std::shared_ptr<Texture> texture, float x, float y, float w, float h);
		void Draw(std::shared_ptr<Texture> texture, float x, float y, float w, float h, float4 color);

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}