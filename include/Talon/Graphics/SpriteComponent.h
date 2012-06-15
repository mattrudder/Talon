
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Component.h>

namespace Talon
{
	class Texture;

	class TalonApi SpriteComponent : public Component
	{
		TALON_COMPONENT(SpriteComponent, Component)

	public:
		virtual ~SpriteComponent();

		virtual void Create();
		virtual void Update();
		virtual void Destroy();

		inline void SetTexture(Texture* texture) { m_texture = texture; }
		inline Texture* GetTexture() { return m_texture; }
		inline void SetSourceBounds(float4 sourceBounds) { m_sourceBounds = sourceBounds; }
		inline float4 GetSourceBounds() { return m_sourceBounds; }
		inline void SetOrigin(float2 origin) { m_origin = origin; }
		inline float2 GetOrigin() { return m_origin; }

	private:		
		Texture* m_texture;
		float4 m_sourceBounds;
		float2 m_origin;
	};
}