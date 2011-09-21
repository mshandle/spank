/*!
 * \file Image.cpp
 * \date 08-08-2011 22:58:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import <UIKit/UIKit.h>
#include <Image.h>
#include <util/IDebugUtil.h>
#include <util/IFileUtil.h>

Image::Image(const char* pszImageFile)
{
	m_nImageWidth = 0;
	m_nImageHeight = 0;
	m_nBPP = 0;
	m_pPixelData = NULL;
	m_bOK = CreateImage(pszImageFile);
}

Image::~Image()
{
	SAFE_DELETE_ARRAY(m_pPixelData);
}

uint Image::GetWidth() const
{
	return m_nImageWidth;
}

uint Image::GetHeight() const
{
	return m_nImageHeight;
}

void* Image::GetPixelData()
{
	return m_pPixelData;
}

uint Image::GetBPP() const
{
	return m_nBPP;
}

bool Image::CreateImage(const char* pszImageFile)
{
	//czj:add 20110918
	NSString *tmpImgPath  = [NSString stringWithFormat:@"%s", pszImageFile];
	UIImage *tmpImg = [UIImage imageNamed:tmpImgPath];

	if (tmpImg == nil) return false;

	m_nImageWidth = CGImageGetWidth(tmpImg.CGImage);
	m_nImageHeight = CGImageGetHeight(tmpImg.CGImage);
	m_nBPP = CGImageGetBitsPerPixel(tmpImg.CGImage);

	m_pPixelData=(uchar *)malloc(m_nImageWidth * m_nImageHeight * 4);
	memset(m_pPixelData, 0, m_nImageWidth * m_nImageHeight * 4);

	CGContextRef textureContext = CGBitmapContextCreate(m_pPixelData,
		m_nImageWidth,
		m_nImageHeight,
		8,
		m_nImageWidth * 4,
		CGImageGetColorSpace(tmpImg.CGImage),
		kCGImageAlphaPremultipliedLast);
	
	CGContextTranslateCTM(textureContext, 0, tmpImg.size.height);
	CGContextScaleCTM(textureContext, 1.0, -1.0);
	
	CGContextDrawImage(textureContext, CGRectMake(0, 0, m_nImageWidth, m_nImageHeight), tmpImg.CGImage);
	CGContextRelease(textureContext);

	return true;
}
