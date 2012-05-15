
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>


namespace Talon
{
	class RenderDevice;

	class TalonApi WindowBase
	{
	public:
		WindowBase(std::string title, int width, int height);
		virtual ~WindowBase();

		const std::string& GetTitle() const;
		void SetTitle(const std::string& value);
		int GetWidth() const;
		int GetHeight() const;
		std::shared_ptr<RenderDevice> GetRenderDevice() const;
		delegate<WindowBase, void(int, int)> Resized;
		delegate<WindowBase, void()> Closed;
		delegate<WindowBase, void()> Created;
		delegate<WindowBase, void()> Destroyed;
		void DoEvents();

	protected:
		void OnResized(int width, int height);
		void OnClosed();
		void OnCreated();
		void OnDestroyed();
		void SetWidth(int value);
		void SetHeight(int value);
		void SetRenderDevice(std::shared_ptr<RenderDevice> value);

	private:
		std::string m_title;
		int m_width;
		int m_height;
		std::shared_ptr<RenderDevice> m_renderDevice;
	};
}