
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>

namespace Talon
{
	class RenderDevice;

	class TalonApi WindowBase
	{
	public:
		WindowBase(std::wstring title, int width, int height);
		virtual ~WindowBase();

		inline const std::wstring& GetTitle() const { return m_title; }
		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
		inline std::shared_ptr<RenderDevice> GetRenderDevice() const { return m_renderDevice; }

		delegate<WindowBase, void(int, int)> Resized;
		delegate<WindowBase, void()> Closed;
		delegate<WindowBase, void()> Created;
		delegate<WindowBase, void()> Destroyed;

	public:
		void DoEvents();

	protected:
		void OnResized(int width, int height);
		void OnClosed();
		void OnCreated();
		void OnDestroyed();

	private:
		i32 m_width;
		i32 m_height;
		std::wstring m_title;
		std::shared_ptr<RenderDevice> m_renderDevice;
	};
}