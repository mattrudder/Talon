
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Component.h>
#include <Talon/Graphics/Texture.h>

namespace Talon
{
	class TalonApi SpriteComponent : public Component
	{
		TALON_COMPONENT(SpriteComponent, Component)

	public:
		SpriteComponent();
		virtual ~SpriteComponent();

		virtual void Create();
		virtual void Update();
		virtual void Destroy();

		inline void SetTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }
		inline std::shared_ptr<Texture> GetTexture() { return m_texture; }
		inline void SetSourceBounds(float4 sourceBounds) { m_sourceBounds = sourceBounds; }
		inline float4 GetSourceBounds() { return m_sourceBounds; }
		inline void SetOrigin(float2 origin) { m_origin = origin; }
		inline float2 GetOrigin() { return m_origin; }

	private:		
		std::shared_ptr<Texture> m_texture;
		float4 m_sourceBounds;
		float2 m_origin;
	};
}