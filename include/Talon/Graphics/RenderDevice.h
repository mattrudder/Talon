
#pragma once

#include <Talon/TalonPublic.h>

#include <Talon/Graphics/ShaderType.h>

#include <functional>
#include <unordered_map>

namespace Talon
{
	class IndexBuffer;
	class InputLayout;
	class Shader;
	class VertexBuffer;
	class Window;

	class TalonApi RenderDevice
	{
	public:
		RenderDevice(Window* window);
		virtual ~RenderDevice();

		Window* GetWindow() const;
		bool IsInitialized() const;

		std::shared_ptr<IndexBuffer> GetActiveIndexBuffer() const;
		void SetActiveIndexBuffer(std::shared_ptr<IndexBuffer> value);

		std::shared_ptr<InputLayout> GetActiveInputLayout() const;
		void SetActiveInputLayout(std::shared_ptr<InputLayout> value);

		std::shared_ptr<VertexBuffer> GetActiveVertexBuffer() const;
		void SetActiveVertexBuffer(std::shared_ptr<VertexBuffer> value);

		std::shared_ptr<Shader> GetActiveShader(ShaderType type);
		void SetActiveShader(ShaderType type, std::shared_ptr<Shader> value);

		void DrawIndexed(u32 indexCount, u32 startIndex, i32 baseVertexLocation);

		void BeginFrame();
		void EndFrame();

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		D3D_FEATURE_LEVEL GetFeatureLevel() const;
		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetDeviceContext() const;
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
		friend class GLContext;
		void* GetContext();
		void WithContext(std::function<void()> fn);
#endif

	protected:
		void SetWindow(Window* value);
		void SetInitialized(bool value);

		void SetActiveIndexBufferCore(std::shared_ptr<IndexBuffer> value);
		void SetActiveInputLayoutCore(std::shared_ptr<InputLayout> value);
		void SetActiveVertexBufferCore(std::shared_ptr<VertexBuffer> value);
		void SetActiveShaderCore(ShaderType type, std::shared_ptr<Shader> value);

	private:
		Window* m_window;
		std::shared_ptr<IndexBuffer> m_activeIndexBuffer;
		std::shared_ptr<InputLayout> m_activeInputLayout;
		std::shared_ptr<VertexBuffer> m_activeVertexBuffer;
		std::unordered_map<u32, std::shared_ptr<Shader>> m_activeShaders;

		bool m_initialized;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}