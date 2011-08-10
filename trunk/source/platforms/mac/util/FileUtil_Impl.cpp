/*!
 * \file FileUtil_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil_Impl.h"
#include <util/IDebugUtil.h>
#include <IConfig.h>
#include <lpng154/png.h>

IFileUtil& IFileUtil::GetInstance()
{
	static FileUtil_Impl s_FileUtil_Impl;
	return s_FileUtil_Impl;
}

static void PngReaderCallback(png_structp pPngStruct, png_bytep pData, png_size_t nSize)
{
	StreamReader* pStream = (StreamReader*)png_get_io_ptr(pPngStruct);
	
	if (!pStream->Read(pData, nSize))
	{
		png_error(pPngStruct,"pngReaderCallback failed");
	}
}

FileUtil_Impl::FileUtil_Impl()
{
	// TODO: 
}

FileUtil_Impl::~FileUtil_Impl()
{
	Terminate();
}

bool FileUtil_Impl::Initialize()
{
	const char* pszResourceDir = IConfig::GetInstance().GetString("RESOURCE_DIR");
	if (!pszResourceDir || strlen(pszResourceDir) <= 0)
	{
		LOGE("invalid resource dir");
		return false;
	}
	
	m_strRootPath = pszResourceDir;
	m_strRootPath += "/";
	return true;
}

void FileUtil_Impl::Terminate()
{
	// TODO: 
}

StreamReader* FileUtil_Impl::LoadFile(const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) return NULL;
	
	std::string strFullPath = m_strRootPath + pszFileName;
	
	FILE* pFile = fopen(strFullPath.c_str(), "rb");
	if (pFile == NULL)
	{
		LOGE("open file failed: %s", strFullPath.c_str());
		return NULL;
	}
	
	fseek(pFile, 0, SEEK_END);
	uint nFileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	
	char* pszBuffer = new char[nFileSize+1];
	int nReadSize = fread(pszBuffer, 1, nFileSize, pFile);
	fclose(pFile);
	
	if (nReadSize < nFileSize)
	{
		SAFE_DELETE_ARRAY(pszBuffer);
		return NULL;
	}
	
	pszBuffer[nFileSize] = '\0';
	
	StreamReader* pStreamReader = new StreamReader(pszBuffer, nFileSize, true);
	if (!pStreamReader || !pStreamReader->IsOK())
	{
		LOGE("create stream reader failed with file size: %d", nFileSize);
		SAFE_DELETE(pStreamReader);
		SAFE_DELETE_ARRAY(pszBuffer);
		return NULL;
	}
	
	return pStreamReader;
}

StreamReader* FileUtil_Impl::LoadImageFile(const char* pszFileName, uint* pnWidth, uint* pnHeight)
{
	StreamReader* pTextureStream = LoadFile(pszFileName);
	if (!pTextureStream || !pTextureStream->IsOK())
	{
		SAFE_RELEASE(pTextureStream);
		return false;
	}
	
	png_structp pPngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pPngStruct)
	{
		png_destroy_read_struct(&pPngStruct, NULL, NULL);
		// TODO: logout
		SAFE_DELETE(pTextureStream);
		return false;
	}
	
	png_infop pPngInfo = png_create_info_struct(pPngStruct);
	if (!pPngInfo)
	{
		png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
		// TODO: logout
		SAFE_DELETE(pTextureStream);
		return false;
	}
	
	if (setjmp(png_jmpbuf(pPngStruct)))
	{
		png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
		// TODO: logout
		SAFE_DELETE(pTextureStream);
		return false;
	}
	
	//define our own callback function for I/O instead of reading from a file
	png_set_read_fn(pPngStruct, pTextureStream, PngReaderCallback);
	
	png_read_info(pPngStruct, pPngInfo);
	int nTextureWidth = png_get_image_width(pPngStruct, pPngInfo);
	int nTextureHeight = png_get_image_height(pPngStruct, pPngInfo);
	png_byte nColorType = png_get_color_type(pPngStruct, pPngInfo);	//ø…“‘ «PNG_COLOR_TYPE_RGB,PNG_COLOR_TYPE_PALETTE.......µ»
	png_byte nBitDepth = png_get_bit_depth(pPngStruct, pPngInfo);
	
	// Convert stuff to appropriate formats!
	if(nColorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_packing(pPngStruct);
		png_set_palette_to_rgb(pPngStruct); //Expand data to 24-bit RGB or 32-bit RGBA if alpha available.
	}
	
	// TODO: why?
	if (nColorType == PNG_COLOR_TYPE_GRAY && nBitDepth < 8) png_set_expand_gray_1_2_4_to_8(pPngStruct);
	if (nColorType == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(pPngStruct);
	if (nBitDepth == 16) png_set_strip_16(pPngStruct);
	
	//Expand paletted or RGB images with transparency to full alpha channels so the data will be available as RGBA quartets.
	if(png_get_valid(pPngStruct, pPngInfo, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(pPngStruct);
	}
	
	// read image data into pRowPointers
	uchar** pRowPointers = new uchar*[nTextureHeight];
	for (int y = 0; y < nTextureHeight; y++)
	{
		pRowPointers[y] = new uchar[nTextureWidth * 4]; //each pixel(RGBA) has 4 bytes
	}
	png_read_image(pPngStruct, pRowPointers);
	
	// free the stream object and png structure
	png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
	SAFE_RELEASE(pTextureStream);
	
	// store image data into our pRGBAData
	uchar* pTextureDataRGBA = new uchar[nTextureWidth * nTextureHeight * 4];  //each pixel(RGBA) has 4 bytes
	//unlike store the pixel data from top-left corner, store them from bottom-left corner for OGLES Texture drawing...
	int nCurrPos = (nTextureWidth * nTextureHeight * 4) - (4 * nTextureWidth);
	for(int row = 0; row < nTextureHeight; row++)
	{
		for(int col = 0; col < (4 * nTextureWidth); col += 4)
		{
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col];        // red
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 1];    // green
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 2];    // blue
			pTextureDataRGBA[nCurrPos++] = pRowPointers[row][col + 3];    // alpha
		}
		nCurrPos = (nCurrPos - (nTextureWidth * 4) * 2); //move the pointer back two rows
	}
	
	// free pRowPointers
	for (int y = 0; y < nTextureHeight; y++)
	{
		SAFE_DELETE_ARRAY(pRowPointers[y]);
	}
	SAFE_DELETE_ARRAY(pRowPointers);
	
	StreamReader* pStreamReader = new StreamReader(pTextureDataRGBA, nTextureWidth * nTextureHeight * 4, true);
	if (!pStreamReader || !pStreamReader->IsOK())
	{
		LOGE("create texture stream reader failed with texture size: %d", nTextureWidth * nTextureHeight * 4);
		SAFE_DELETE(pStreamReader);
		SAFE_DELETE_ARRAY(pTextureDataRGBA);
		return NULL;
	}
	
	*pnWidth = nTextureWidth;
	*pnHeight = nTextureHeight;
	return pStreamReader;
}