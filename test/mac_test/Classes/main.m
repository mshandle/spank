/*!
 * \file main.m
 * \date 27-08-2011 04:51:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import <UIKit/UIKit.h>
#import "SpankAppDelegate.h"

int main(int argc, char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, NSStringFromClass([SpankAppDelegate class]));
    [pool release];
    return retVal;
}
