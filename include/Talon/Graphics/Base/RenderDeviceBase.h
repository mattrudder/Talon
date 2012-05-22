
#pragma once

#include <Talon/TalonPublic.h>


namespace Talon
{
	class IndexBuffer;
	class VertexBuffer;
	class Window;

	class TalonApi RenderDeviceBase
	{
	public:
		RenderDeviceBase(Window* window);
		virtual ~RenderDeviceBase();

		Window* GetWindow() const;
		bool IsInitialized() const;
		IndexBuffer* GetActiveIndexBuffer() const;
		void SetActiveIndexBuffer(IndexBuffer* value);
		VertexBuffer* GetActiveVertexBuffer() const;
		void SetActiveVertexBuffer(VertexBuffer* value);
		void BeginFrame();
		void EndFrame();

	protected:
		void SetWindow(Window* value);
		void SetInitialized(bool value);

	private:
		Window* m_window;
		IndexBuffer* m_activeIndexBuffer;
		VertexBuffer* m_activeVertexBuffer;
		bool m_initialized;
	};
}