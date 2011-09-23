/*!
 * \file Image.h
 * \date 08-08-2011 21:36:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "IObject.h"

class Image : public IObject
{
public:
	DECLARE_RTTI(Image, IObject);

	Image(const char* pszImageFile);
	virtual ~Image();

	int GetWidth() const;
	int GetHeight() const;

	void* GetPixelData();
	int GetBPP() const;

private:
	bool CreateImage(const char* pszImageFile);

private:
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nBPP;
	uchar* m_pPixelData;

};
#endif // __IMAGE_H__
