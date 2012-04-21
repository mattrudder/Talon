
#include <Talon/Platform/Mac/MacWindow.h>
#include <string>

#import <Cocoa/Cocoa.h>

@interface MacWindowDelegate : NSObject<NSWindowDelegate>
{
@public
	Talon::MacWindow::Impl* impl;
}

struct Talon::MacWindow::Impl
{
	MacWindow* instance;
	NSWindow* window;
	MacWindowDelegate* delegate;
	
	void OnResized(int width, int height)
	{
		instance->OnResized(width, height);
	}
	
	void OnClosed()
	{
		instance->OnClosed();
	}
};

@end

@implementation MacWindowDelegate

- (void)windowDidResize:(NSNotification *)notification
{
	impl->OnResized(impl->window.frame.size.width, impl->window.frame.size.height);
}

- (void)windowWillClose:(NSNotification *)notification
{
	impl->OnClosed();
}

@end

namespace Talon
{	
	MacWindow::MacWindow(std::wstring title, int width, int height)
		: WindowBase(title, width, height)
		, m_impl(make_unique<Impl>())
	{	
		NSWindow* window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
													   styleMask:NSTitledWindowMask|NSClosableWindowMask|NSMiniaturizableWindowMask|NSResizableWindowMask
														 backing:NSBackingStoreBuffered
														   defer:NO
														  screen:[NSScreen mainScreen]];


		m_impl->instance = this;
		m_impl->window = window;
		m_impl->delegate = [[MacWindowDelegate alloc] init];
		
		window.title = @"Talon";
		window.backgroundColor = [NSColor blackColor];
		
		m_impl->delegate->impl = m_impl.get();
		window.delegate = m_impl->delegate;
		
		[window makeKeyAndOrderFront:[NSApplication sharedApplication]];
		[window setReleasedWhenClosed:NO];
		
		OnCreated();
	}

	MacWindow::~MacWindow()
	{
		OnDestroyed();
	}

	void MacWindow::DoEvents()
	{
	}
	
	void* MacWindow::GetWindow() const
	{
		return (__bridge void*)m_impl->window;
	}
}