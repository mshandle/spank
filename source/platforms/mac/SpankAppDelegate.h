/*!
 * \file SpankAppDelegate.h
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import <UIKit/UIKit.h>

@interface SpankAppDelegate : NSObject <UIApplicationDelegate> {
	UIWindow* window;
	UIView* pViewArray[100];
	int nextViewIndex;
}

@property (nonatomic, retain) UIWindow *window;

+ (SpankAppDelegate*)GetInstance;

- (int)createNormalView;
- (int)createOpenGLView;
- (void)destroyView:(int)viewId;

- (BOOL)attachView:(int)viewId;
- (void)dettachView:(int)viewId;

@end
