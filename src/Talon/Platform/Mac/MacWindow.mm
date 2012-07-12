
#include <Talon/Platform/Window.h>
#include <string>

#import <Cocoa/Cocoa.h>

@interface MacWindowDelegate : NSObject<NSWindowDelegate>
{
@public
	Talon::Window::Impl* impl;
}

class Talon::Window::Impl
{
public:
	Window* instance;
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
    Window::Window(const std::string title, int width, int height)
        : m_width(width)
        , m_height(height)
        , m_title(title)
        , m_renderDevice(nullptr)
        , m_pImpl(std::make_unique<Impl>())
	{
		NSWindow* window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
													   styleMask:NSTitledWindowMask|NSClosableWindowMask|NSMiniaturizableWindowMask|NSResizableWindowMask
														 backing:NSBackingStoreBuffered
														   defer:NO
														  screen:[NSScreen mainScreen]];


		m_pImpl->instance = this;
		m_pImpl->window = window;
		m_pImpl->delegate = [[MacWindowDelegate alloc] init];
		
		window.title = @"Talon";
		window.backgroundColor = [NSColor blackColor];
		
		m_pImpl->delegate->impl = m_pImpl.get();
		window.delegate = m_pImpl->delegate;
		
		[window makeKeyAndOrderFront:[NSApplication sharedApplication]];
		[window setReleasedWhenClosed:NO];
		
		OnCreated();
	}

	Window::~Window()
	{
	}

	void Window::DoEvents()
	{
	}
	
	void* Window::GetWindow() const
	{
		return (void*)m_pImpl->window;
	}
}