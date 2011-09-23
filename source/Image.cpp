/*!
 * \file Image.cpp
 * \date 08-08-2011 22:58:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <Image.h>
#include <util/IDebugUtil.h>
#include <util/IFileUtil.h>
#include <lpng154/png.h>

static void PngReaderCallback(png_structp pPngStruct, png_bytep pData, png_size_t nSize)
{
	StreamReader* pStream = (StreamReader*)png_get_io_ptr(pPngStruct);

	if (!pStream->Read(pData, nSize))
	{
		png_error(pPngStruct,"pngReaderCallback failed");
	}
}

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

int Image::GetWidth() const
{
	return m_nImageWidth;
}

int Image::GetHeight() const
{
	return m_nImageHeight;
}

void* Image::GetPixelData()
{
	return m_pPixelData;
}

int Image::GetBPP() const
{
	return m_nBPP;
}

bool Image::CreateImage(const char* pszImageFile)
{
	StreamReader* pTextureStream = IFileUtil::GetInstance().LoadFile(pszImageFile);
	if (!pTextureStream || !pTextureStream->IsOK())
	{
		SAFE_RELEASE(pTextureStream);
		return false;
	}

	png_structp pPngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pPngStruct)
	{
		png_destroy_read_struct(&pPngStruct, NULL, NULL);
		// logout
		LOGE("load image file failed: %s", pszImageFile);
		SAFE_DELETE(pTextureStream);
		return false;
	}

	png_infop pPngInfo = png_create_info_struct(pPngStruct);
	if (!pPngInfo)
	{
		png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
		// logout
		LOGE("create png info failed: %s", pszImageFile);
		SAFE_DELETE(pTextureStream);
		return false;
	}

	setjmp(png_jmpbuf(pPngStruct));

	// define our own callback function for I/O instead of reading from a file
	png_set_read_fn(pPngStruct, pTextureStream, PngReaderCallback);

	png_read_info(pPngStruct, pPngInfo);
	m_nImageWidth = png_get_image_width(pPngStruct, pPngInfo);
	m_nImageHeight = png_get_image_height(pPngStruct, pPngInfo);
	// can be PNG_COLOR_TYPE_RGB, PNG_COLOR_TYPE_PALETTE, ...
	png_byte nColorType = png_get_color_type(pPngStruct, pPngInfo);
	m_nBPP = png_get_bit_depth(pPngStruct, pPngInfo);

	// convert stuff to appropriate formats!
	if(nColorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_packing(pPngStruct);
		// expand data to 24-bit RGB or 32-bit RGBA if alpha available
		png_set_palette_to_rgb(pPngStruct);
	}

	// expand data to 24-bit RGB or 32-bit RGBA if alpha available
	if (nColorType == PNG_COLOR_TYPE_GRAY && m_nBPP < 8) png_set_expand_gray_1_2_4_to_8(pPngStruct);
	if (nColorType == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(pPngStruct);
	if (m_nBPP == 16) png_set_strip_16(pPngStruct);

	// expand paletted or RGB images with transparency to full alpha channels so the data will be available as RGBA quartets.
	if(png_get_valid(pPngStruct, pPngInfo, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(pPngStruct);

	// read image data into pRowPointers
	uchar** pRowPointers = new uchar*[m_nImageHeight];
	for (int y = 0; y < m_nImageHeight; y++)
	{
		pRowPointers[y] = new uchar[m_nImageWidth * 4]; //each pixel(RGBA) has 4 bytes
	}
	png_read_image(pPngStruct, pRowPointers);

	// free the stream object and png structure
	png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
	SAFE_RELEASE(pTextureStream);

	// store image data into our pRGBAData, each pixel(RGBA) has 4 bytes
	m_pPixelData = new uchar[m_nImageWidth * m_nImageHeight * 4];
	//unlike store the pixel data from top-left corner, store them from bottom-left corner for OGLES Texture drawing...
	int nCurrPos = (m_nImageWidth * m_nImageHeight * 4) - (4 * m_nImageWidth);
	for(int row = 0; row < m_nImageHeight; row++)
	{
		for(int col = 0; col < (4 * m_nImageWidth); col += 4)
		{
			m_pPixelData[nCurrPos++] = pRowPointers[row][col + 0];    // red
			m_pPixelData[nCurrPos++] = pRowPointers[row][col + 1];    // green
			m_pPixelData[nCurrPos++] = pRowPointers[row][col + 2];    // blue
			m_pPixelData[nCurrPos++] = pRowPointers[row][col + 3];    // alpha
		}
		nCurrPos = (nCurrPos - (m_nImageWidth * 4) * 2); //move the pointer back two rows
	}

	// free pRowPointers
	for (int y = 0; y < m_nImageHeight; y++)
	{
		SAFE_DELETE_ARRAY(pRowPointers[y]);
	}
	SAFE_DELETE_ARRAY(pRowPointers);

	return true;
}
