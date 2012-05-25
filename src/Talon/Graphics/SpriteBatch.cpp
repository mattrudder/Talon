
#include "TalonPrefix.h"
#include <Talon/Graphics/SpriteBatch.h>

#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	class SpriteBatch::Impl
	{
	public:
		Impl(RenderDevice* renderDevice);
	};

	SpriteBatch::Impl::Impl(RenderDevice* /*renderDevice*/)
	{
	}

	SpriteBatch::SpriteBatch(RenderDevice* renderDevice)
		: m_pImpl(std::make_unique<Impl>(renderDevice))
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::Begin()
	{
	}

	void SpriteBatch::End()
	{
	}

	void Draw(Texture* /*texture*/, f32 /*x*/, f32 /*y*/)
	{
	}
}