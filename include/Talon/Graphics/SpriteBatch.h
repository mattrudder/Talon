
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

	struct Vector2
	{
		f32 x;
		f32 y;

		Vector2(f32 x = 0, f32 y = 0)
			: x(x), y(y) { }

		Vector2 operator-(Vector2& rhs)
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2 operator+(Vector2& rhs)
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2 operator*(Vector2& rhs)
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}
	};

	struct Vector3
	{
		f32 x;
		f32 y;
		f32 z;

		Vector3(f32 x = 0, f32 y = 0, f32 z = 0)
			: x(x), y(y), z(z) { }

		Vector3 operator-(Vector3& rhs)
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3 operator+(Vector3& rhs)
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3 operator*(Vector3& rhs)
		{
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}
	};

	struct Vector4
	{
		f32 x;
		f32 y;
		f32 z;
		f32 w;

		Vector4(f32 x = 0, f32 y = 0, f32 z = 0, f32 w = 0)
			: x(x), y(y), z(z), w(w) { }

		Vector4 operator-(Vector4& rhs)
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, z - rhs.z);
		}

		Vector4 operator+(Vector4& rhs)
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, z + rhs.z);
		}

		Vector4 operator*(Vector4& rhs)
		{
			return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, z * rhs.z);
		}
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
		f32 left;
		f32 top;
		f32 width;
		f32 height;
	};

	class TalonApi SpriteBatch
	{
	public:
		SpriteBatch(RenderDevice* renderDevice);
		~SpriteBatch();

		void Begin();
		void End();

		void Draw(std::shared_ptr<Texture> texture, f32 x, f32 y);

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}