
#pragma once

#include <Talon/TalonPublic.h>
#include <functional>

namespace Talon
{
	class IndexBuffer;
	class VertexBuffer;
	class Window;

	class TalonApi RenderDevice
	{
	public:
		RenderDevice(Window* window);
		virtual ~RenderDevice();

		Window* GetWindow() const;
		bool IsInitialized() const;

		IndexBuffer* GetActiveIndexBuffer() const;
		void SetActiveIndexBuffer(IndexBuffer* value);

		VertexBuffer* GetActiveVertexBuffer() const;
		void SetActiveVertexBuffer(VertexBuffer* value);

		void DrawIndexed(u32 indexCount, u32 startIndex, i32 baseVertexLocation);

		void BeginFrame();
		void EndFrame();

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
		D3D_FEATURE_LEVEL GetFeatureLevel() const;
		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetDeviceContext() const;
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
		friend class GLContext;
		void WithContext(std::function<void()> fn);
#endif

	protected:
		void SetWindow(Window* value);
		void SetInitialized(bool value);

	private:
		Window* m_window;
		IndexBuffer* m_activeIndexBuffer;
		VertexBuffer* m_activeVertexBuffer;
		bool m_initialized;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}