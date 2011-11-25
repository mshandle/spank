/*!
 * \file SpankAppDelegate.h
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import <UIKit/UIKit.h>

enum CONST_DEFINE
{
	BASE_CONTROL_ID = 10000,
};

@interface SpankAppDelegate : NSObject <UIApplicationDelegate> {
	UIWindow* window;
	UIView* pViewArray[100];
	int nextViewIndex;
	int nextControlId;
}

@property (nonatomic, retain) UIWindow *window;

+ (SpankAppDelegate*)GetInstance;

- (int)createNormalView;
- (int)createOpenGLView;
- (void)destroyView:(int)viewId;

- (BOOL)attachView:(int)viewId;
- (void)dettachView:(int)viewId;

- (int)createButton:(int)viewId x:(int)x y:(int)y width:(int)width height:(int)height text:(const char*)text;
- (int)createEditText:(int)viewId x:(int)x y:(int)y width:(int)width height:(int)height;
- (void)destroyButton:(int)viewId buttonId:(int)buttonId;

@end
