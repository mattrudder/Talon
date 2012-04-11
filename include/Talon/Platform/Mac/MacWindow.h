
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Platform/Base/WindowBase.h>

namespace Talon { namespace Mac
{
	class TalonApi MacWindow : public WindowBase
	{
	public:
		MacWindow(std::wstring title, int width, int height);
		virtual ~MacWindow();

	public:
		void DoEvents();
	};
}}