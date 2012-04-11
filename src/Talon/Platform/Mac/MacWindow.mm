
#include <Talon/Platform/Mac/MacWindow.h>
#include <string>

namespace Talon { namespace Mac
{
	MacWindow::MacWindow(std::wstring title, int width, int height)
		: WindowBase(title, width, height)
	{
	}

	MacWindow::~MacWindow()
	{
	}

	void MacWindow::DoEvents()
	{
	}
}}