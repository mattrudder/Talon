
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>


namespace Talon
{
	class RenderDevice;

#if TALON_WINDOWS
	struct RawInputEventArgs;
#endif

	class TalonApi Window
	{
	public:
		Window(const std::string title, int width, int height);
		virtual ~Window();

		const std::string& GetTitle() const;
		void SetTitle(const std::string& value);

		int GetWidth() const;
		int GetHeight() const;

		std::shared_ptr<RenderDevice> GetRenderDevice() const;

		delegate<Window, void(int, int)> Resized;
		delegate<Window, void()> Closed;
		delegate<Window, void()> Created;
		delegate<Window, void()> Destroyed;

		void DoEvents();

#if TALON_WINDOWS
		delegate<Window, void(RawInputEventArgs&)> RawInput;

		HWND GetHandle() const;
#endif

	protected:
		void OnResized(int width, int height);
		void OnClosed();
		void OnCreated();
		void OnDestroyed();

		void SetWidth(int value);
		void SetHeight(int value);
		void SetRenderDevice(std::shared_ptr<RenderDevice> value);

#if TALON_WINDOWS
		void OnRawInput(RawInputEventArgs& e);
#endif

	private:
		int m_width;
		int m_height;
		std::string m_title;
		std::shared_ptr<RenderDevice> m_renderDevice;

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}