
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
@public
	std::shared_ptr<Talon::Engine> m_engine;
	CVDisplayLinkRef m_displayLink;
}

@end
