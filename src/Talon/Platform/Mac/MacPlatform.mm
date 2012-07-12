
#include "TalonPrefix.h"

#include <Talon/Platform/Platform.h>

#import <Cocoa/Cocoa.h>

namespace Talon 
{
	bool Platform::SetWorkingPath(const std::string& path)
	{
        return true;
	}
    
	std::string Platform::GetEnginePath()
	{
        return [[[NSBundle mainBundle] bundlePath] UTF8String];
	}
	
	std::string Platform::GetResourcePath(const std::string& fileName)
	{
		NSString* relativePath = [[NSString alloc] initWithUTF8String:fileName.c_str()];
		NSString* resourcePath = [[NSBundle mainBundle] bundlePath];

		// If the debugger is hooked up, don't look inside the app bundle for resources.
		// NOTE: This could be a really bad idea... :P
		//if (talonAmIBeingDebugged())
			resourcePath = [resourcePath stringByDeletingLastPathComponent];

		return [[resourcePath stringByAppendingPathComponent:relativePath] UTF8String];
	}
	
	std::string Platform::GetTextFromFile(const std::string& fileName)
	{
		NSError* error;
		NSStringEncoding encoding;
		std::string absolutePath = GetResourcePath(fileName);
		NSString* nsAbsolutePath = [[NSString alloc] initWithUTF8String:absolutePath.c_str()];
		NSString* fileContents = [[NSString alloc] initWithContentsOfFile:nsAbsolutePath usedEncoding:&encoding error:&error];
		
		return [fileContents UTF8String];
	}
}