
#include <Talon/Talon.h>
#include <Talon/Engine.h>

#import "AppDelegate.h"

static CVReturn OnDisplayLink(CVDisplayLinkRef displayLink,
	const CVTimeStamp *inNow,
	const CVTimeStamp *inOutputTime, 
	CVOptionFlags flagsIn, 
	CVOptionFlags *flagsOut, 
	void *displayLinkContext)
{
	AppDelegate* app = (__bridge AppDelegate*)displayLinkContext;
	
	auto engine = app->m_engine.get();
	if (engine->IsRunning())
		engine->RunFrame();
	else
		[[NSApplication sharedApplication] terminate:app];
	
	return kCVReturnSuccess;
}

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	// Insert code here to initialize your application
	m_engine = std::make_shared<Talon::Engine>();
	m_engine->Initialize(NULL);
	
	CVDisplayLinkCreateWithActiveCGDisplays(&m_displayLink);
	CVDisplayLinkSetCurrentCGDisplay(m_displayLink, kCGDirectMainDisplay);
	CVDisplayLinkSetOutputCallback(m_displayLink, OnDisplayLink, (__bridge void*) self);
	CVDisplayLinkStart(m_displayLink);
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
	if (CVDisplayLinkIsRunning(m_displayLink))
		CVDisplayLinkStop(m_displayLink);
	
	m_engine->Shutdown();
	
	return NSTerminateNow;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
	return NO;
}

@end
