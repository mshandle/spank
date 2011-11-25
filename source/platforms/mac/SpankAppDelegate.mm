/*!
 * \file SpankAppDelegate.cpp
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import "SpankAppDelegate.h"
#import "ViewOpenGL.h"
#import "ViewNormal.h"
#import <util/ConfigUtil.h>
#import <util/ScreenUtil.h>
#import <ICore.h>

SpankAppDelegate* g_pInstance = NULL;

@implementation SpankAppDelegate

@synthesize window;

+ (SpankAppDelegate*)GetInstance
{
	return g_pInstance;
}

- (int)createNormalView
{
	CGRect screenBounds = [[UIScreen mainScreen] bounds];
	pViewArray[nextViewIndex] = [[[ViewNormal alloc] initWithFrame:screenBounds] autorelease];
	
	pViewArray[nextViewIndex].frame = CGRectMake(0, 0, screenBounds.size.height, screenBounds.size.width);
	pViewArray[nextViewIndex].center = CGPointMake(screenBounds.size.width / 2.0, screenBounds.size.height / 2.0);
	
	// Rotate the view 90 degrees around its new center point. 
	CGAffineTransform transform = pViewArray[nextViewIndex].transform;
	transform = CGAffineTransformRotate(transform, (M_PI / 2.0));
	pViewArray[nextViewIndex].transform = transform;

	return nextViewIndex++;
}

- (int)createOpenGLView
{
	CGRect screenBounds = [[UIScreen mainScreen] bounds];
	pViewArray[nextViewIndex] = [[[ViewOpenGL alloc] initWithFrame:screenBounds] autorelease];
	return nextViewIndex++;
}

- (void)destroyView:(int)viewId
{
	// TODO: 
}

- (BOOL)attachView:(int)viewId
{
	UIView* view = pViewArray[viewId];
	
	[self.window addSubview:view];
	if ([view isKindOfClass:[ViewOpenGL class]] == TRUE)
	{
		ViewOpenGL* openglView = (ViewOpenGL*)view;
		[openglView startLoop];
	}
	
	return TRUE;
}

- (void)dettachView:(int)viewId
{
	UIView* view = pViewArray[viewId];

	if ([view isKindOfClass:[ViewOpenGL class]] == TRUE)
	{
		ViewOpenGL* openglView = (ViewOpenGL*)view;
		[openglView stopLoop];
	}
	
	[view removeFromSuperview];
}

- (int)createButton:(int)viewId x:(int)x y:(int)y width:(int)width height:(int)height text:(const char*)text
{
	UIView* view = pViewArray[viewId];
	if (view == nil) return 0;
	
	UIButton* myButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	myButton.tag = nextControlId++;
    myButton.frame = CGRectMake(x, y, width, height); // position in the parent view and set the size of the button
	
	NSString* strText = [NSString stringWithUTF8String:text];
    [myButton setTitle:strText forState:UIControlStateNormal];
//    // add targets and actions
//    [myButton addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
    // add to a view
    [view addSubview:myButton];
	
	return myButton.tag;
}

- (int)createEditText:(int)viewId x:(int)x y:(int)y width:(int)width height:(int)height
{
	UIView* view = pViewArray[viewId];
	if (view == nil) return 0;
	
	UITextField * textFieldRounded = [[UITextField alloc] initWithFrame:CGRectMake(x, y, width, height)];
	textFieldRounded.tag = nextControlId++;
	
	//    // add targets and actions
	//    [myButton addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
    // add to a view
    [view addSubview:textFieldRounded];
	return textFieldRounded.tag;
}

- (void)destroyButton:(int)viewId buttonId:(int)buttonId
{
	UIView* view = pViewArray[viewId];
	if (view == nil) return;
	
	UIView* control = [view viewWithTag:buttonId];
	if (control == nil) return;
	
	[control removeFromSuperview];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	g_pInstance = self;
	memset(pViewArray, 0, sizeof(pViewArray));
	nextViewIndex = 1;
	nextControlId = BASE_CONTROL_ID;

	[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight];
	ConfigUtil::GetInstance().AddInt("SCREEN_ROTATION", ScreenUtil::SR_P90);
	
	// spank initialize
	NSString* rootPath = [[NSBundle mainBundle] resourcePath];
	const char* pszRootPath = [rootPath cStringUsingEncoding: [NSString defaultCStringEncoding]];
	ConfigUtil::GetInstance().AddString("RESOURCE_DIR", pszRootPath);

	// Override point for customization after application launch.
	CGRect screenBounds = [[UIScreen mainScreen] bounds];
	ConfigUtil::GetInstance().AddInt("SURFACE_WIDTH", screenBounds.size.width);
	ConfigUtil::GetInstance().AddInt("SURFACE_HEIGHT", screenBounds.size.height);
	
	// create window
	self.window = [[[UIWindow alloc] initWithFrame:screenBounds] autorelease];

	// initialize
	if (!ICore::GetInstance().Initialize()) return FALSE;

	[self.window makeKeyAndVisible];
    return TRUE;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
	ICore::GetInstance().Terminate();
}

- (void)dealloc
{
    [super dealloc];
}

@end
