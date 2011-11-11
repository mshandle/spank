/*!
 * \file ViewOpenGL.mm
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import "ViewOpenGL.h"
#import <GLES2/gl2.h>
#import <GLES2/gl2ext.h>
#import <util/ScreenUtil.h>
#import <ICore.h>
#import <InputMgr.h>
#import <IRenderer2D.h>

@implementation ViewOpenGL

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext {   
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}

- (void)setupFrameBuffer {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

- (void)setupDisplayLink {
    displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
}

-(void) startLoop {
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

-(void) stopLoop {
    [displayLink removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)render:(CADisplayLink*)displayLink {
	ICore::GetInstance().Update(1.0f/60.0f);
	ICore::GetInstance().Render();
	
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        [self setupDisplayLink];
    }
    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchStart(0, vPos.x, vPos.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchMove(0, vPos.x, vPos.y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchEnd(0, vPos.x, vPos.y);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint pos = [[touches anyObject] locationInView: self.superview];
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, pos.x, pos.y);
	InputMgr::GetInstance().OnTouchEnd(0, vPos.x, vPos.y);
}

- (void)dealloc
{
    [_context release];
    _context = nil;
    [super dealloc];
}

@end
