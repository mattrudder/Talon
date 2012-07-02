
#include "TalonPrefix.h"

#include <Talon/Graphics/SpriteBatch.h>

#include <Talon/TalonMath.h>
#include <Talon/Graphics/BufferFormat.h>
#include <Talon/Graphics/BufferUsage.h>
#include <Talon/Graphics/IndexBuffer.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Graphics/Shader.h>
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/VertexBuffer.h>
#include <Talon/Graphics/VertexFormats.h>

#include <algorithm>

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
#include "Direct3D11/D3D11Utility.h"
#include <DirectXMath.h>
using namespace DirectX;
#endif

namespace Talon
{
	const u8 SpriteEffect_SpritePixelShader[] =
	{
		68,  88,  66,  67,  62, 231, 
		156,  88, 145, 159, 172,  51, 
		164, 207, 207, 254, 124, 230, 
		155, 106,   1,   0,   0,   0, 
		232,   1,   0,   0,   4,   0, 
		0,   0,  48,   0,   0,   0, 
		184,   0,   0,   0, 100,   1, 
		0,   0, 180,   1,   0,   0, 
		65, 111, 110,  57, 128,   0, 
		0,   0, 128,   0,   0,   0, 
		0,   2, 255, 255,  88,   0, 
		0,   0,  40,   0,   0,   0, 
		0,   0,  40,   0,   0,   0, 
		40,   0,   0,   0,  40,   0, 
		1,   0,  36,   0,   0,   0, 
		40,   0,   0,   0,   0,   0, 
		0,   2, 255, 255,  31,   0, 
		0,   2,   0,   0,   0, 128, 
		0,   0,  15, 176,  31,   0, 
		0,   2,   0,   0,   0, 128, 
		1,   0,   3, 176,  31,   0, 
		0,   2,   0,   0,   0, 144, 
		0,   8,  15, 160,  66,   0, 
		0,   3,   0,   0,  15, 128, 
		1,   0, 228, 176,   0,   8, 
		228, 160,   5,   0,   0,   3, 
		0,   0,  15, 128,   0,   0, 
		228, 128,   0,   0, 228, 176, 
		1,   0,   0,   2,   0,   8, 
		15, 128,   0,   0, 228, 128, 
		255, 255,   0,   0,  83,  72, 
		68,  82, 164,   0,   0,   0, 
		64,   0,   0,   0,  41,   0, 
		0,   0,  89,   0,   0,   4, 
		70, 142,  32,   0,   0,   0, 
		0,   0,   1,   0,   0,   0, 
		90,   0,   0,   3,   0,  96, 
		16,   0,   0,   0,   0,   0, 
		88,  24,   0,   4,   0, 112, 
		16,   0,   0,   0,   0,   0, 
		85,  85,   0,   0,  98,  16, 
		0,   3, 242,  16,  16,   0, 
		0,   0,   0,   0,  98,  16, 
		0,   3,  50,  16,  16,   0, 
		1,   0,   0,   0, 101,   0, 
		0,   3, 242,  32,  16,   0, 
		0,   0,   0,   0, 104,   0, 
		0,   2,   1,   0,   0,   0, 
		69,   0,   0,   9, 242,   0, 
		16,   0,   0,   0,   0,   0, 
		70,  16,  16,   0,   1,   0, 
		0,   0,  70, 126,  16,   0, 
		0,   0,   0,   0,   0,  96, 
		16,   0,   0,   0,   0,   0, 
		56,   0,   0,   7, 242,  32, 
		16,   0,   0,   0,   0,   0, 
		70,  14,  16,   0,   0,   0, 
		0,   0,  70,  30,  16,   0, 
		0,   0,   0,   0,  62,   0, 
		0,   1,  73,  83,  71,  78, 
		72,   0,   0,   0,   2,   0, 
		0,   0,   8,   0,   0,   0, 
		56,   0,   0,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		3,   0,   0,   0,   0,   0, 
		0,   0,  15,  15,   0,   0, 
		62,   0,   0,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		3,   0,   0,   0,   1,   0, 
		0,   0,   3,   3,   0,   0, 
		67,  79,  76,  79,  82,   0, 
		84,  69,  88,  67,  79,  79, 
		82,  68,   0, 171,  79,  83, 
		71,  78,  44,   0,   0,   0, 
		1,   0,   0,   0,   8,   0, 
		0,   0,  32,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		0,   0,   3,   0,   0,   0, 
		0,   0,   0,   0,  15,   0, 
		0,   0,  83,  86,  95,  84, 
		97, 114, 103, 101, 116,   0, 
		171, 171
	};

	const u8 SpriteEffect_SpriteVertexShader[] =
	{
		68,  88,  66,  67,  53,  15, 
		108,  68,  10,  30,  79, 231, 
		153,   9,  61,  10, 198, 154, 
		8, 125,   1,   0,   0,   0, 
		60,   3,   0,   0,   4,   0, 
		0,   0,  48,   0,   0,   0, 
		28,   1,   0,   0,  84,   2, 
		0,   0, 200,   2,   0,   0, 
		65, 111, 110,  57, 228,   0, 
		0,   0, 228,   0,   0,   0, 
		0,   2, 254, 255, 176,   0, 
		0,   0,  52,   0,   0,   0, 
		1,   0,  36,   0,   0,   0, 
		48,   0,   0,   0,  48,   0, 
		0,   0,  36,   0,   1,   0, 
		48,   0,   0,   0,   0,   0, 
		4,   0,   1,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		0,   2, 254, 255,  31,   0, 
		0,   2,   5,   0,   0, 128, 
		0,   0,  15, 144,  31,   0, 
		0,   2,   5,   0,   1, 128, 
		1,   0,  15, 144,  31,   0, 
		0,   2,   5,   0,   2, 128, 
		2,   0,  15, 144,   5,   0, 
		0,   3,   0,   0,  15, 128, 
		2,   0,  85, 144,   2,   0, 
		228, 160,   4,   0,   0,   4, 
		0,   0,  15, 128,   2,   0, 
		0, 144,   1,   0, 228, 160, 
		0,   0, 228, 128,   4,   0, 
		0,   4,   0,   0,  15, 128, 
		2,   0, 170, 144,   3,   0, 
		228, 160,   0,   0, 228, 128, 
		4,   0,   0,   4,   0,   0, 
		15, 128,   2,   0, 255, 144, 
		4,   0, 228, 160,   0,   0, 
		228, 128,   4,   0,   0,   4, 
		0,   0,   3, 192,   0,   0, 
		255, 128,   0,   0, 228, 160, 
		0,   0, 228, 128,   1,   0, 
		0,   2,   0,   0,  12, 192, 
		0,   0, 228, 128,   1,   0, 
		0,   2,   0,   0,  15, 224, 
		0,   0, 228, 144,   1,   0, 
		0,   2,   1,   0,   3, 224, 
		1,   0, 228, 144, 255, 255, 
		0,   0,  83,  72,  68,  82, 
		48,   1,   0,   0,  64,   0, 
		1,   0,  76,   0,   0,   0, 
		89,   0,   0,   4,  70, 142, 
		32,   0,   0,   0,   0,   0, 
		4,   0,   0,   0,  95,   0, 
		0,   3, 242,  16,  16,   0, 
		0,   0,   0,   0,  95,   0, 
		0,   3,  50,  16,  16,   0, 
		1,   0,   0,   0,  95,   0, 
		0,   3, 242,  16,  16,   0, 
		2,   0,   0,   0, 101,   0, 
		0,   3, 242,  32,  16,   0, 
		0,   0,   0,   0, 101,   0, 
		0,   3,  50,  32,  16,   0, 
		1,   0,   0,   0, 103,   0, 
		0,   4, 242,  32,  16,   0, 
		2,   0,   0,   0,   1,   0, 
		0,   0, 104,   0,   0,   2, 
		1,   0,   0,   0,  54,   0, 
		0,   5, 242,  32,  16,   0, 
		0,   0,   0,   0,  70,  30, 
		16,   0,   0,   0,   0,   0, 
		54,   0,   0,   5,  50,  32, 
		16,   0,   1,   0,   0,   0, 
		70,  16,  16,   0,   1,   0, 
		0,   0,  56,   0,   0,   8, 
		242,   0,  16,   0,   0,   0, 
		0,   0,  86,  21,  16,   0, 
		2,   0,   0,   0,  70, 142, 
		32,   0,   0,   0,   0,   0, 
		1,   0,   0,   0,  50,   0, 
		0,  10, 242,   0,  16,   0, 
		0,   0,   0,   0,   6,  16, 
		16,   0,   2,   0,   0,   0, 
		70, 142,  32,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		70,  14,  16,   0,   0,   0, 
		0,   0,  50,   0,   0,  10, 
		242,   0,  16,   0,   0,   0, 
		0,   0, 166,  26,  16,   0, 
		2,   0,   0,   0,  70, 142, 
		32,   0,   0,   0,   0,   0, 
		2,   0,   0,   0,  70,  14, 
		16,   0,   0,   0,   0,   0, 
		50,   0,   0,  10, 242,  32, 
		16,   0,   2,   0,   0,   0, 
		246,  31,  16,   0,   2,   0, 
		0,   0,  70, 142,  32,   0, 
		0,   0,   0,   0,   3,   0, 
		0,   0,  70,  14,  16,   0, 
		0,   0,   0,   0,  62,   0, 
		0,   1,  73,  83,  71,  78, 
		108,   0,   0,   0,   3,   0, 
		0,   0,   8,   0,   0,   0, 
		80,   0,   0,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		3,   0,   0,   0,   0,   0, 
		0,   0,  15,  15,   0,   0, 
		86,   0,   0,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		3,   0,   0,   0,   1,   0, 
		0,   0,   3,   3,   0,   0, 
		95,   0,   0,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		3,   0,   0,   0,   2,   0, 
		0,   0,  15,  15,   0,   0, 
		67,  79,  76,  79,  82,   0, 
		84,  69,  88,  67,  79,  79, 
		82,  68,   0,  83,  86,  95, 
		80, 111, 115, 105, 116, 105, 
		111, 110,   0, 171,  79,  83, 
		71,  78, 108,   0,   0,   0, 
		3,   0,   0,   0,   8,   0, 
		0,   0,  80,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		0,   0,   3,   0,   0,   0, 
		0,   0,   0,   0,  15,   0, 
		0,   0,  86,   0,   0,   0, 
		0,   0,   0,   0,   0,   0, 
		0,   0,   3,   0,   0,   0, 
		1,   0,   0,   0,   3,  12, 
		0,   0,  95,   0,   0,   0, 
		0,   0,   0,   0,   1,   0, 
		0,   0,   3,   0,   0,   0, 
		2,   0,   0,   0,  15,   0, 
		0,   0,  67,  79,  76,  79, 
		82,   0,  84,  69,  88,  67, 
		79,  79,  82,  68,   0,  83, 
		86,  95,  80, 111, 115, 105, 
		116, 105, 111, 110,   0, 171
	};

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
	const char* c_vsSpriteEffect = "\
		cbuffer Parameters : register(b0) \
		{\
			row_major float4x4 MatrixTransform;\
		};\
	\
	\
		void VSMain(inout float4 color    : COLOR0,\
			inout float2 texCoord : TEXCOORD0,\
			inout float4 position : SV_Position)\
		{\
			position = mul(position, MatrixTransform);\
		}";

	const char* c_psSpriteEffect = "\
		Texture2D<float4> Texture : register(t0);\
		sampler TextureSampler : register(s0);\
	\
	\
		float4 PSMain(float4 color    : COLOR0,\
			float2 texCoord : TEXCOORD0) : SV_Target0\
		{\
			return Texture.Sample(TextureSampler, texCoord) * color;\
		}";
#else
#	warning "SpriteBatch needs shader definitions for this platform!"
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

		std::vector<SpriteInfo const*> m_sortedSprites;

		RenderDevice* device;
		std::shared_ptr<IndexBuffer> indexBuffer;
		std::shared_ptr<VertexBuffer> vertexBuffer;

		size_t m_vertexBufferOffset;

		std::shared_ptr<Shader> vertexShader;
		std::shared_ptr<Shader> pixelShader;


		// TODO: Make Talon compliant
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		//CComPtr<ID3D11PixelShader> pixelShader;
		//CComPtr<ID3D11VertexShader> vertexShader;
		CComPtr<ID3D11InputLayout> inputLayout;
		CComPtr<ID3D11Buffer> constantBuffer;

		CComPtr<ID3D11BlendState> blendState;
		CComPtr<ID3D11DepthStencilState> depthStencilState;
		CComPtr<ID3D11RasterizerState> rasterizerState;
		CComPtr<ID3D11SamplerState> samplerState;
#else
//#warning "SpriteBatch contains platform-specific code and needs to be ported!"
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
        , device(renderDevice)
		, m_vertexBufferOffset(0)

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		auto device = renderDevice->GetDevice();
#endif
		vertexShader = Shader::CreateFromMemory(renderDevice, ShaderType::Vertex, c_vsSpriteEffect, "SpriteBatch.cpp+c_vsSpriteEffect");
		pixelShader = Shader::CreateFromMemory(renderDevice, ShaderType::Pixel, c_psSpriteEffect, "SpriteBatch.cpp+c_psSpriteEffect");
		
		// TODO: Support vertex layout class (https://app.asana.com/0/1144010891804/1155421552097)
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		ThrowIfFailed(device->CreateInputLayout(VertexPositionColorTexture::InputElements, VertexPositionColorTexture::InputElementCount, SpriteEffect_SpriteVertexShader, sizeof(SpriteEffect_SpriteVertexShader), &inputLayout));
#endif

		// TODO: Support render states (https://app.asana.com/0/1144010891804/1171962804804)
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		//ThrowIfFailed(D3D11::CreateBlendState(device, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, &blendState));
		//ThrowIfFailed(D3D11::CreateDepthStencilState(device, true, true, &depthStencilState));
		//ThrowIfFailed(D3D11::CreateRasterizerState(device, D3D11_CULL_BACK, D3D11_FILL_SOLID, &rasterizerState));
		//ThrowIfFailed(D3D11::CreateSamplerState(device, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, &samplerState));
#endif

		// TODO: Support constant buffers (https://app.asana.com/0/1144010891804/1171962804793)
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		D3D11_BUFFER_DESC desc = {0};
		desc.ByteWidth = sizeof(XMMATRIX);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ThrowIfFailed(device->CreateBuffer(&desc, nullptr, &constantBuffer));
#endif

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

		m_insideBeginEnd = false;
	}

	// TODO: Support constant buffers (https://app.asana.com/0/1144010891804/1171962804793)
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
	XMMATRIX GetViewportTransform(ID3D11DeviceContext* deviceContext)
	{
		// Look up the current viewport.
		D3D11_VIEWPORT viewport;
		UINT viewportCount = 1;

		deviceContext->RSGetViewports(&viewportCount, &viewport);

		if (viewportCount != 1)
			throw std::exception("No viewport is set");

		// Compute the matrix.
		float xScale = (viewport.Width  > 0) ? 2.0f / viewport.Width  : 0.0f;
		float yScale = (viewport.Height > 0) ? 2.0f / viewport.Height : 0.0f;

		return XMMATRIX
			(
			xScale,  0,       0,  0,
			0,      -yScale,  0,  0,
			0,       0,       1,  0,
			-1,       1,       0,  1
			);
	}
#endif

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
		//ID3D11SamplerState* pSamplerState = samplerState;
		//deviceContext->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
		//deviceContext->OMSetDepthStencilState(depthStencilState, 0);
		//deviceContext->RSSetState(rasterizerState);
		//deviceContext->PSSetSamplers(0, 1, &pSamplerState);

		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceContext->IASetInputLayout(inputLayout);
#endif

		device->SetActiveShader(ShaderType::Vertex, vertexShader);
		device->SetActiveShader(ShaderType::Pixel, pixelShader);

		device->SetActiveVertexBuffer(vertexBuffer);
		device->SetActiveIndexBuffer(indexBuffer);

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		// TODO: Support constant buffers (https://app.asana.com/0/1144010891804/1171962804793)
		XMMATRIX transformMatrix = GetViewportTransform(deviceContext);

		ID3D11Buffer* pConstBuffer = constantBuffer;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ThrowIfFailed(deviceContext->Map(pConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
		*(XMMATRIX*)mappedResource.pData = transformMatrix;
		deviceContext->Unmap(pConstBuffer, 0);
		deviceContext->VSSetConstantBuffers(0, 1, &pConstBuffer);
#endif
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
		//Vector source = Vector4Load(sprite->source);
		//Vector destination = Vector4Load(sprite->destination);
		Vector origin = Vector2Load(&sprite->origin);
		Vector invTexSize = Vector2Load(&inverseTextureSize);

		//float4 color = sprite->color;
		//f32 rotation = sprite->rotation;
		//f32 depth = sprite->depth;
		u32 flags = sprite->flags;

		origin = origin * invTexSize;

		Vector destinationOrigin = Vector2Load(sprite->destination.x, sprite->destination.y);
		Vector sourceSize = Vector2Load(sprite->source.z, sprite->source.w);
		Vector destinationSize = Vector2Load(sprite->destination.z, sprite->destination.w);

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

		for (int i = 0; i < VerticesPerSprite; ++i)
		{
			// Calculate position.
			Vector cornerOffset = (cornerOffsets[i] - origin) * destinationSize;
			Vector position = cornerOffset + destinationOrigin;

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
		float4 dest(x, y, (float)texture->GetWidth(), (float)texture->GetHeight());
		float4 color(1, 1, 1, 1);
		m_pImpl->Draw(texture, dest, nullptr, color, 0);
	}
}