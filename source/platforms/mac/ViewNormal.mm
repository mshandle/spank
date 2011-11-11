/*!
 * \file ViewNormal.mm
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import "ViewNormal.h"
#import <util/ScreenUtil.h>
#import <InputMgr.h>
#import <msg/MsgMgr.h>
#import <util/ConfigUtil.h>

@implementation ViewNormal

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
	self.backgroundColor = UIColor.whiteColor;
	
    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchStart(0, vPos.x, vPos.y);
	MsgMgr::GetInstance().DispatchMessage();
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchMove(0, vPos.x, vPos.y);
	MsgMgr::GetInstance().DispatchMessage();
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchEnd(0, vPos.x, vPos.y);
	MsgMgr::GetInstance().DispatchMessage();
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchEnd(0, vPos.x, vPos.y);
	MsgMgr::GetInstance().DispatchMessage();
}

- (void)dealloc
{
    [super dealloc];
}

@end
