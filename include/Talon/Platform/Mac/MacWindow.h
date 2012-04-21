
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Platform/Base/WindowBase.h>

namespace Talon
{
	class TalonApi MacWindow : public WindowBase
	{
	public:
		MacWindow(std::wstring title, int width, int height);
		virtual ~MacWindow();

	public:
		void DoEvents();
		
		void* GetWindow() const;

		struct Impl;

	private:
		std::unique_ptr<Impl> m_impl;
	};
}