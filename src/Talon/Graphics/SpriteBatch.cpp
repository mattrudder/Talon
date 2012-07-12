
#include "TalonPrefix.h"

#include <Talon/Graphics/SpriteBatch.h>

#include <Talon/TalonMath.h>
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/ConstantBuffer.h>
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/InputLayout.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Graphics/Shader.h>
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/VertexBuffer.h>
#include <Talon/Graphics/VertexFormats.h>

#include <Talon/Platform/Window.h>

#include <algorithm>

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
#include "Direct3D11/D3D11Utility.h"
#include <DirectXMath.h>
using namespace DirectX;
#endif

namespace Talon
{
	// TODO: Replace with Material definition (https://app.asana.com/0/1144010891804/1171962804809)
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
	const char* c_vsSpriteEffect = "Resources/SpriteBatch.VS.hlsl";

	const char* c_psSpriteEffect = "Resources/SpriteBatch.PS.hlsl";
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
	const char* c_vsSpriteEffect = "Resources/SpriteBatch.VS.glsl";
	
	const char* c_psSpriteEffect = "Resources/SpriteBatch.PS.glsl";
#endif

	class SpriteBatch::Impl
	{
	public:
		Impl(RenderDevice* renderDevice);

		void Begin();
		void End();

		void Draw(std::shared_ptr<Texture> texture, float4 destination, Rect const* source, float4 color, u32 flags);

		struct SpriteInfo
		{
			float4 source;
			float4 destination;
			float4 color;
			float2 origin;
			float rotation;
			float depth;

			std::shared_ptr<Texture> texture;
			u32 flags;

			// Combine values from the public SpriteEffects enum with these internal-only flags.
			static const int SourceInTexels = 4;
			static const int DestSizeInPixels = 8;

			static_assert(((int)SpriteEffects::FlipBoth & (SourceInTexels | DestSizeInPixels)) == 0, "Flag bits must not overlap");
			
		};

	private:
		std::vector<u16> CreateIndexValues();

		void GrowSpriteQueue();
		void PrepareForRendering();
		void CleanupRendering();
		void FlushBatch();
		void SortSprites();
		void GrowSortedSprites();

		void RenderBatch(std::shared_ptr<Texture> texture, SpriteInfo const* const* sprites, size_t count);
		
		static void RenderSprite(SpriteInfo const* sprite, VertexPositionColorTexture* vertices, float2 textureSize, float2 inverseTextureSize);

		// Constants
		static const size_t MaxBatchSize;
		static const size_t MinBatchSize;
		static const size_t InitialQueueSize;
		static const size_t VerticesPerSprite;
		static const size_t IndicesPerSprite;

		std::unique_ptr<SpriteInfo[]> m_spriteQueue;

		bool m_insideBeginEnd;
		size_t m_queueCount;
		size_t m_queueSize;
		size_t m_vertexBufferOffset;

		std::vector<SpriteInfo const*> m_sortedSprites;

		RenderDevice* device;

		std::shared_ptr<ConstantBuffer<Matrix>> constantBuffer;

		std::shared_ptr<IndexBuffer> indexBuffer;
		std::shared_ptr<VertexBuffer> vertexBuffer;

		std::shared_ptr<Shader> vertexShader;
		std::shared_ptr<Shader> pixelShader;

		std::shared_ptr<InputLayout> spriteVertexLayout;

		// TODO: Make Talon compliant
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		CComPtr<ID3D11BlendState> blendState;
		CComPtr<ID3D11DepthStencilState> depthStencilState;
		CComPtr<ID3D11RasterizerState> rasterizerState;
		CComPtr<ID3D11SamplerState> samplerState;
#endif
	};

	const size_t SpriteBatch::Impl::MaxBatchSize = 2048;
	const size_t SpriteBatch::Impl::MinBatchSize = 128;
	const size_t SpriteBatch::Impl::InitialQueueSize = 64;
	const size_t SpriteBatch::Impl::VerticesPerSprite = 4;
	const size_t SpriteBatch::Impl::IndicesPerSprite = 6;

	SpriteBatch::Impl::Impl(RenderDevice* renderDevice)
		: m_insideBeginEnd(false)
		, m_queueCount(0)
		, m_queueSize(0)
		, m_vertexBufferOffset(0)
		, device(renderDevice)
	{
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		auto device = renderDevice->GetDevice();
#endif
		vertexShader = Shader::CreateFromFile(renderDevice, ShaderType::Vertex, c_vsSpriteEffect);
		pixelShader = Shader::CreateFromFile(renderDevice, ShaderType::Pixel, c_psSpriteEffect);
		spriteVertexLayout = InputLayout::Create(renderDevice, VertexPositionColorTexture::InputElements, VertexPositionColorTexture::InputElementCount, vertexShader);

		// TODO: Support render states (https://app.asana.com/0/1144010891804/1171962804804)
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		ThrowIfFailed(D3D11::CreateBlendState(device, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_ONE, D3D11_BLEND_ONE, &blendState));
		ThrowIfFailed(D3D11::CreateDepthStencilState(device, true, true, &depthStencilState));
		ThrowIfFailed(D3D11::CreateRasterizerState(device, D3D11_CULL_BACK, D3D11_FILL_SOLID, &rasterizerState));
		ThrowIfFailed(D3D11::CreateSamplerState(device, D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_CLAMP, &samplerState));
#endif

		constantBuffer = ConstantBuffer<Matrix>::Create(renderDevice, BufferUsage::Dynamic);

		auto indexValues = CreateIndexValues();
		indexBuffer = IndexBuffer::Create(renderDevice, MaxBatchSize * IndicesPerSprite, BufferFormat::I16, BufferUsage::Default, &indexValues.front());
		vertexBuffer = VertexBuffer::Create(renderDevice, sizeof(VertexPositionColorTexture), MaxBatchSize * VerticesPerSprite, BufferUsage::Dynamic);
	}

	void SpriteBatch::Impl::Begin()
	{
		if (m_insideBeginEnd)
			throw Exception("Cannot nest Begin calls on a single SpriteBatch");

		m_insideBeginEnd = true;
	}

	void SpriteBatch::Impl::End()
	{
		if (!m_insideBeginEnd)
			throw Exception("Begin must be called before End");

		PrepareForRendering();
		FlushBatch();
		CleanupRendering();

		m_insideBeginEnd = false;
	}

	Matrix GetViewportTransform(RenderDevice* device)
	{
		int width = device->GetWindow()->GetWidth();
		int height = device->GetWindow()->GetHeight();

		// Compute the matrix.
		float xScale = (width  > 0) ? 2.0f / width  : 0.0f;
		float yScale = (height > 0) ? 2.0f / height : 0.0f;

		return Matrix
		(
			xScale, 0,       0,  0,
			0,      -yScale, 0,  0,
			0,      0,       1,  0,
			-1,     1,       0,  1
		);
	}

	void SpriteBatch::Impl::Draw(std::shared_ptr<Texture> texture, float4 destination, Rect const* sourceRect, float4 color, u32 flags)
	{
		static const size_t vectorSize = sizeof(float4);
#define LoadVector(dest, src) memcpy(dest, src, vectorSize)

		if (!texture)
			throw Exception("Texture cannot be null");

		if (!m_insideBeginEnd)
			throw Exception("Being must be called before Draw");

		if (m_queueCount >= m_queueSize)
			GrowSpriteQueue();

		float4 dest = destination;
		SpriteInfo* sprite = &m_spriteQueue[m_queueCount];

		if (sourceRect)
		{
			LoadVector(&sprite->source, &sourceRect);
		}
		else
		{
			static const float4 wholeTexture(0, 0, 1, 1);
			LoadVector(&sprite->source, &wholeTexture);
		}

		sprite->rotation = 0;
		LoadVector(&sprite->destination, &dest);
		LoadVector(&sprite->color, &color);

		sprite->texture = texture;
		sprite->flags = flags;

		m_queueCount++;

#undef LoadVector
	}

	void SpriteBatch::Impl::GrowSpriteQueue()
	{
		size_t newSize = std::max(InitialQueueSize, m_queueSize * 2);

		std::unique_ptr<SpriteInfo[]> newArray(new SpriteInfo[newSize]);

		for (size_t i = 0; i < m_queueCount; ++i)
			newArray[i] = m_spriteQueue[i];

		m_spriteQueue = std::move(newArray);
		m_queueSize = newSize;

		m_sortedSprites.clear();
	}

	void SpriteBatch::Impl::PrepareForRendering()
	{
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		auto deviceContext = device->GetDeviceContext();

		// TODO: Support render states (https://app.asana.com/0/1144010891804/1171962804804)
		ID3D11SamplerState* pSamplerState = samplerState;
		deviceContext->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
		deviceContext->OMSetDepthStencilState(depthStencilState, 0);
		deviceContext->RSSetState(rasterizerState);
		deviceContext->PSSetSamplers(0, 1, &pSamplerState);
#endif

		device->SetActiveInputLayout(spriteVertexLayout);

		device->SetActiveShader(ShaderType::Vertex, vertexShader);
		device->SetActiveShader(ShaderType::Pixel, pixelShader);

		device->SetActiveVertexBuffer(vertexBuffer);
		device->SetActiveIndexBuffer(indexBuffer);

		Matrix transformMatrix = GetViewportTransform(device);
		constantBuffer->Update(&transformMatrix);
		vertexShader->SetConstantBuffer(0, constantBuffer);
	}

	void SpriteBatch::Impl::CleanupRendering()
	{
		device->SetActiveIndexBuffer(nullptr);
		device->SetActiveVertexBuffer(nullptr);

		device->SetActiveShader(ShaderType::Pixel, nullptr);
		device->SetActiveShader(ShaderType::Vertex, nullptr);

		device->SetActiveInputLayout(nullptr);
	}

	std::vector<u16> SpriteBatch::Impl::CreateIndexValues()
	{
		std::vector<u16> indices;

		indices.reserve(MaxBatchSize * IndicesPerSprite);

		for (u16 i = 0; i < MaxBatchSize * VerticesPerSprite; i += VerticesPerSprite)
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);

			indices.push_back(i + 1);
			indices.push_back(i + 3);
			indices.push_back(i + 2);
		}

		return indices;
	}

	void SpriteBatch::Impl::FlushBatch()
	{
		SortSprites();

		// Walk through sprite list, looking for entries that share a texture.
		size_t batchStart = 0;
		std::shared_ptr<Texture> batchTexture = nullptr;

		for (size_t index = 0; index < m_queueCount; ++index)
		{
			std::shared_ptr<Texture> texture = m_sortedSprites[index]->texture;

			if (texture != batchTexture)
			{
				if (index > batchStart)
					RenderBatch(batchTexture, &m_sortedSprites[batchStart], index - batchStart);

				batchTexture = texture;
				batchStart = index;
			}
		}

		// Render final batch
		RenderBatch(batchTexture, &m_sortedSprites[batchStart], m_queueCount - batchStart);

		// Reset queue
		m_queueCount = 0;

		m_sortedSprites.clear();
	}

	void SpriteBatch::Impl::SortSprites()
	{
		if (m_sortedSprites.size() < m_queueCount)
			GrowSortedSprites();

		// TODO: Additional sort modes. Currently only sorted by texture.
		std::sort(m_sortedSprites.begin(), m_sortedSprites.begin() + m_queueCount, [](SpriteInfo const* lhs, SpriteInfo const* rhs)
		{
			return lhs->texture < rhs->texture;
		});
	}

	void SpriteBatch::Impl::GrowSortedSprites()
	{
		size_t previousSize = m_sortedSprites.size();
		m_sortedSprites.resize(m_queueCount);

		for (size_t i = previousSize; i < m_queueCount; ++i)
			m_sortedSprites[i] = &m_spriteQueue[i];
	}

	void SpriteBatch::Impl::RenderBatch(std::shared_ptr<Texture> texture, SpriteInfo const* const* sprites, size_t count)
	{
		// Activate batch texture
		pixelShader->SetTexture(0, texture);

		while (count > 0)
		{
			size_t batchSize = count;
			size_t remainingSpace = MaxBatchSize - m_vertexBufferOffset;

			if (batchSize > remainingSpace)
			{
				if (remainingSpace < MinBatchSize)
				{
					m_vertexBufferOffset = 0;
					batchSize = std::min(count, MaxBatchSize);
				}
				else
				{
					batchSize = remainingSpace;
				}
			}

			VertexPositionColorTexture* vertices = nullptr;
			vertexBuffer->Map(m_vertexBufferOffset == 0 ? BufferMapType::Discard : BufferMapType::NoOverwrite, (void**) &vertices);
			vertices += m_vertexBufferOffset * VerticesPerSprite;

			for (size_t i = 0; i < batchSize; ++i)
			{
				float2 textureSize((float)texture->GetWidth(), (float)texture->GetHeight());
				float2 inverseTextureSize(1.0f / textureSize.x, 1.0f / textureSize.y);
				RenderSprite(sprites[i], vertices, textureSize, inverseTextureSize);

				vertices += VerticesPerSprite;
			}
			
			vertexBuffer->Unmap();

			// Draw indexed sprites!
			u32 startIndex = m_vertexBufferOffset * IndicesPerSprite;
			u32 indexCount = batchSize * IndicesPerSprite;

			device->DrawIndexed(indexCount, startIndex, 0);

			// Advance buffer position
			m_vertexBufferOffset += batchSize;

			sprites += batchSize;
			count -= batchSize;
		}
	}

	void SpriteBatch::Impl::RenderSprite(SpriteInfo const* sprite, VertexPositionColorTexture* vertices, float2 /*textureSize*/, float2 inverseTextureSize)
	{
		// Load sprite parameters into SIMD registers.
		//Vector source = Vector4Load(&sprite->source);
		Vector destination = Vector4Load(&sprite->destination);
		Vector origin = Vector2Load(&sprite->origin);
		Vector invTexSize = Vector2Load(&inverseTextureSize);
		
		float rotation = sprite->rotation;
		//float depth = sprite->depth;
		u32 flags = sprite->flags;

		origin = origin * invTexSize;

		//Vector originRotationDepth = Vector4Load(sprite->origin.x, sprite->origin.y, rotation, depth);
		Vector sourceSize = Vector2Load(sprite->source.z, sprite->source.w);
		Vector destinationSize = Vector2Load(sprite->destination.z, sprite->destination.w);

		Vector rotationMatrix1;
		Vector rotationMatrix2;

		if (rotation != 0)
		{
			float sin = sinf(rotation);
			float cos = cosf(rotation);

			rotationMatrix1 = Vector4Load(cos, sin, 0, 0);
			rotationMatrix2 = Vector4Load(-sin, cos, 0, 0);
		}
		else
		{
			rotationMatrix1 = MatrixIdentityRow0;
			rotationMatrix2 = MatrixIdentityRow1;
		}

		static Vector cornerOffsets[VerticesPerSprite] =
		{
			Vector2Load(0, 0),
			Vector2Load(1, 0),
			Vector2Load(0, 1),
			Vector2Load(1, 1),
		};

		static_assert((int)SpriteEffects::FlipHorizontally == 1 &&
			(int)SpriteEffects::FlipVertically == 2, "If you change these enum values, the mirroring implementation must be updated to match");

		int mirrorBits = flags & 3;

		Matrix transformMatrix = MatrixRotationZ(rotation);
		for (int i = 0; i < VerticesPerSprite; ++i)
		{
			// Calculate position.
			Vector cornerOffset = (cornerOffsets[i] - origin) * destinationSize;

			Vector position1 = VectorAdd(VectorMultiply(VectorSplatX(cornerOffset), rotationMatrix1), destination);
			Vector position2 = VectorAdd(VectorMultiply(VectorSplatY(cornerOffset), rotationMatrix2), position1);
			Vector posX = VectorAdd(cornerOffset, destination);
			posX = posX;

			// TODO: Add real depth component, instead of just zeroing out the depth.
			//Vector position = VectorPermute<0, 1, 7, 6>(position2, originRotationDepth); Modeled after XMVectorPermute
			Vector position = VectorAnd(position2, VectorMask2);
			StoreFloat3(&vertices[i].position, position);

			vertices[i].color = sprite->color;

			Vector sourceOrigin = Vector2Load(sprite->source.x, sprite->source.y);
			Vector uv = (cornerOffsets[i ^ mirrorBits] * sourceSize) + sourceOrigin;
			StoreFloat2(&vertices[i].textureCoordinate, uv);
		}
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
		m_pImpl->Begin();
	}

	void SpriteBatch::End()
	{
		m_pImpl->End();
	}

	void SpriteBatch::Draw(std::shared_ptr<Texture> texture, float x, float y)
	{
		Draw(texture, x, y, (float)texture->GetWidth(), (float)texture->GetHeight());
	}

	void SpriteBatch::Draw(std::shared_ptr<Texture> texture, float x, float y, float w, float h)
	{
		Draw(texture, x, y, w, h, float4(1, 1, 1, 1));
	}

	void SpriteBatch::Draw(std::shared_ptr<Texture> texture, float x, float y, float w, float h, float4 color)
	{
		float4 dest(x, y, w, h);
		m_pImpl->Draw(texture, dest, nullptr, color, 0);
	}
}