
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>

namespace Talon
{
	class TalonApi WindowBase
	{
	public:
		WindowBase(std::wstring title, U32 width, U32 height);
		virtual ~WindowBase();

		inline const std::wstring& GetTitle() const { return m_title; }
		inline U32 GetWidth() const { return m_width; }
		inline U32 GetHeight() const { return m_height; }

		delegate<WindowBase, void(U32, U32)> Resized;
		delegate<WindowBase, void()> Closed;

	public:
		void DoEvents();

	protected:
		void OnResized(U32 width, U32 height);
		void OnClosed();

	private:
		U32 m_width;
		U32 m_height;
		std::wstring m_title;
	};
}