#include "application.h"

#if GY_OS_OF_APPLE_IS_ENABLED
#import <iostream>
#import <Cocoa/Cocoa.h>

@interface GNSApplication : NSApplication
@end

@interface GNSApplicationDelegate : NSObject <NSApplicationDelegate>
@end

@interface GNSApplication ()
-(void) sendEvent:(NSEvent *)theEvent;
@end

@implementation GNSApplication
-(void) sendEvent:(NSEvent *)event
{
	if ([event type] == NSKeyUp && ([event modifierFlags] & NSCommandKeyMask))
	{
		[[self keyWindow] sendEvent:event];
	}
	else
	{
		[super sendEvent:event];
	}
}
-(void) makeRunning
{
	_running = YES;
}
-(void) terminate:(id)sender
{
	_running = NO;
}
@end

@interface GNSApplicationDelegate ()
@end

@implementation GNSApplicationDelegate
-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
	return YES;
}
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
	//	_GLFWwindow* window;
	//
	//	for (window = _glfw.windowListHead;  window;  window = window->next)
	//		_glfwInputWindowCloseRequest(window);
	//
	
	return NSTerminateCancel;
}

- (void)applicationDidChangeScreenParameters:(NSNotification *) notification
{
	//	_glfwInputMonitorChange();
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	[NSApp stop:nil];
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	{
		NSEvent *event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
											location:NSMakePoint(0, 0)
									   modifierFlags:0
										   timestamp:0
										windowNumber:0
											 context:nil
											 subtype:0
											   data1:0
											   data2:0];
		[NSApp postEvent:event atStart:YES];
	}
	[pool drain];
}
@end


void createMenu()
{
	if (NSApp == nil)
		return;
	
	// creation default menu bar
	NSMenu *menubar = [[NSMenu alloc] init];
	NSMenuItem *appMenuItem = [[NSMenuItem alloc] init];
	NSMenu *appMenu = [[NSMenu alloc] init];
	NSString *appName = [[NSProcessInfo processInfo] processName];
	NSString *quitTitle = [@"Quit " stringByAppendingString:appName];
	NSMenuItem *quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
														  action:@selector(terminate:)
												   keyEquivalent:@"q"];
	[appMenu addItem:quitMenuItem];
	[appMenuItem setSubmenu:appMenu];
	[menubar addItem:appMenuItem];
	[NSApp setMainMenu:menubar];
}

GNSApplication *createApplication()
{
	auto application = (GNSApplication *)[GNSApplication sharedApplication];
	
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
	
	return application;
}

GNSApplication *_application = nil;
result_t initializeAppKit()
{
	@autoreleasepool
	{
		_application = createApplication();
		if (_application == nil)
		{
			assert(false);
			return GY_FAIL;
		}
		
		createMenu();
		
		id appDelegate = [[GNSApplicationDelegate alloc] init];
		[NSApp setDelegate: appDelegate];
		
		//		[NSApp finishLaunching];
		[NSApp run];
	}
	return GY_SUCCESS;
}

result_t GApplication::onPreInitialize() { return GY_SUCCESS; }
result_t GApplication::onInitialize() { return GY_SUCCESS; }
result_t GApplication::onPostInitialize() { return GY_SUCCESS; }

result_t GApplication::onExecute()
{
	if (GY_FAIL == initializeAppKit())
		return GY_FAIL;
	
	getObject(getId());
	bHasStartedEventDispatch = true;
	bTryToExit = true;
	
	//	while (bHasStartedEventDispatch)
	//	{
	//		std::this_thread::sleep_for(std::chrono::seconds(1));
	//	}
	//
	[NSApp makeRunning];
	
	while ([NSApp isRunning])
	{
		while (true)
		{
			@autoreleasepool
			{
				NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
													untilDate:[NSDate distantPast]
													   inMode:NSDefaultRunLoopMode
													  dequeue:YES];
				if (event == nil)
					break;
				
				[NSApp sendEvent:event];
			}
		}
	}
	
	return GY_SUCCESS;
}

result_t GApplication::onPreFinalize() { return GY_SUCCESS; }
result_t GApplication::onFinalize() { return GY_SUCCESS; }
result_t GApplication::onPostFinalize() { return GY_SUCCESS; }

#endif // if GY_OS_IS_MACOS_ENABLED
