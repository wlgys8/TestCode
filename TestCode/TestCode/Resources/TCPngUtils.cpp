#include "TCPngUtils.h"
#include "TCFileUtils.h"
#include "unzip.h"

NS_TC_BEGIN

#define png_infopp_NULL (png_infopp)NULL
#define TC_RGB_PREMULTIPLY_APLHA(vr, vg, vb, va) \
	(unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
	((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
	((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
	((unsigned)(unsigned char)(va) << 24))
#define TC_RGBA_ALPHA(vr, vg, vb, va) \
	(unsigned)((unsigned)(unsigned char)(vr)  ) | \
	((unsigned)((unsigned char)(vg)  << 8)) | \
	((unsigned)((unsigned char)(vb) << 16)) | \
	((unsigned)(unsigned char)(va) << 24)
TCBitmap* TCPngUtils::decodePngByFileName(const char* fileName)
{
#if 1==1
	unsigned long size;
	unsigned char* buffer=TCFileUtils::getFileData(fileName,&size);
	return TCPngUtils::decodePngByFileData(fileName,buffer,size);
#else
	char png_header[8];
	png_structp png_ptr;
	png_infop info_ptr;
	int width, height, rowBytes;
	png_byte color_type; 
    png_byte bit_depth;
    png_colorp palette; 

    /* open file and test for it being a png */
    FILE *file = fopen(fileName, "rb");
	if(file==NULL){
		 DebugLog("file not exist...:%s",fileName);
		 return NULL;
	}
    fread(png_header, 1, 8, file);
    if(png_sig_cmp((png_bytep)png_header, 0, 8))
    {
        DebugLog("Not a PNG file...");
        fclose(file);
		return NULL;
    }
    /* initialize structures for reading a png file */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        DebugLog("ReadPngFile: Failed to read the PNG file");
        fclose(file);
		return NULL;
    }
    //I/O initialisation methods
    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, 8);  //Required!!!

    /* **************************************************
     * The high-level read interface in libpng (http://www.libpng.org/pub/png/libpng-1.2.5-manual.html)
     * **************************************************
     */
		png_byte channels= png_get_channels(png_ptr,info_ptr);
		DebugLog("channels:%d",channels);
       png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
       width = info_ptr->width;
       height = info_ptr->height;
		color_type = info_ptr->color_type;
	   bit_depth = info_ptr->bit_depth;
		DebugLog("%s:\n colorType:%d\nbitDepth:%d",fileName,color_type,bit_depth);
		DebugLog("channels:%d",channels);
       unsigned char* rgba = new unsigned char[width * height * 4];  //each pixel(RGBA) has 4 bytes
       png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

       //unlike store the pixel data from top-left corner, store them from bottom-left corner for OGLES Texture drawing...
       int pos = (width * height * 4) - (4 * width);
       for(int row = 0; row < height; row++)
       {
          for(int col = 0; col < (4 * width); col += 4)
          {
              rgba[pos++] = row_pointers[row][col];        // red
              rgba[pos++] = row_pointers[row][col + 1]; // green
              rgba[pos++] = row_pointers[row][col + 2]; // blue
              rgba[pos++] = row_pointers[row][col + 3]; // alpha
          }
          pos=(pos - (width * 4)*2); //move the pointer back two rows
       }

	TCBitmap* bitmap=new TCBitmap();

	bitmap->_pixelData=rgba;
	bitmap->_imageWidth=width;
	bitmap->_imageHeight=height;

    //clean up after the read, and free any memory allocated
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(file);
    return bitmap;
#endif
}


void pngReaderCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	ImageSource* isource = (ImageSource*)png_get_io_ptr(png_ptr);

	if(isource->offset + length <= isource->size)
	{
		memcpy(data, isource->data + isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr,"pngReaderCallback failed");
	}
}

TCBitmap* TCPngUtils::decodePngByFileData(const char* filename,void * data, unsigned long dataLength)
{
	png_byte        header[8]   = {0}; 
	png_structp     png_ptr     =   0;
	png_infop       info_ptr    = 0;
	unsigned char * imageData  = 0;
	TCBitmap* ret=NULL;
	const unsigned long headerSize=8;
	do 
	{
		// png header len is 8 bytes
		DebugLog("file size:%lu",dataLength);

		if(dataLength<8){
			DebugLog("file header error");
			break;
		}
		// check the data is png or not
		memcpy(header, data, 8);
		if(png_sig_cmp(header, 0, 8)){
			DebugLog("not png file");
			break;
		}

		// init png_struct
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		if(! png_ptr){
			DebugLog("create png ptr failed");
			break;
		}
		// init png_info
		info_ptr = png_create_info_struct(png_ptr);
		if(!info_ptr){
			DebugLog("create png info failed");
			break;
		}

		if(setjmp(png_jmpbuf(png_ptr))){
			DebugLog("setjmp failed");
			break;
		}

		// set the read call back function
		ImageSource imageSource;
		imageSource.data    = (unsigned char*)data;
		imageSource.size    = dataLength;
		imageSource.offset  = 0;
		png_set_read_fn(png_ptr, &imageSource, pngReaderCallback);


		// read png
		// PNG_TRANSFORM_EXPAND: perform set_expand()
		// PNG_TRANSFORM_PACKING: expand 1, 2 and 4-bit samples to bytes
		// PNG_TRANSFORM_STRIP_16: strip 16-bit samples to 8 bits
		// PNG_TRANSFORM_GRAY_TO_RGB: expand grayscale samples to RGB (or GA to RGBA)
		png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_PACKING 
			| PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_GRAY_TO_RGB, 0);

		int         color_type  = 0;
		png_uint_32 nWidth = 0;
		png_uint_32 nHeight = 0;
		int         nBitsPerComponent = 0;
		png_get_IHDR(png_ptr, info_ptr, &nWidth, &nHeight, &nBitsPerComponent, &color_type, 0, 0, 0);

		DebugLog(":\n colorType:%d\nbitDepth:%d",color_type,nBitsPerComponent);
		DebugLog("channels:%d",info_ptr->channels);

		if(!TCBitmap::checkIsPowerOf2(nWidth)||!TCBitmap::checkIsPowerOf2(nHeight)){ //only supprot power of 2 now
			break;
		}
		// init image info
		bool m_bPreMulti = true;
		bool m_bHasAlpha = ( info_ptr->color_type & PNG_COLOR_MASK_ALPHA ) ? true : false;
		
		// allocate memory and read data
		int bytesPerComponent = 3;
		if (m_bHasAlpha)
		{
			bytesPerComponent = 4;
		}
		imageData = new unsigned char[nHeight * nWidth * bytesPerComponent];
		if(! imageData){
			DebugLog("out of memory");
			break;
		}

		png_bytep * rowPointers = png_get_rows(png_ptr, info_ptr);

		// copy data to image info
		int bytesPerRow = nWidth * bytesPerComponent;

		if(m_bHasAlpha)
		{
			unsigned int *tmp = (unsigned int *)imageData;
			for(int i = nHeight-1; i>=0; i--)
			{
			//	DebugLog("i=%d",i);
				for(int j = 0; j < bytesPerRow; j += 4)
				{
					*tmp++ = TC_RGB_PREMULTIPLY_APLHA( rowPointers[i][j], rowPointers[i][j + 1], 
						rowPointers[i][j + 2], rowPointers[i][j + 3] );
				}
			}
		}
		else
		{
			for (int j = nHeight-1; j>=0; j--)
			{
				memcpy(imageData + j * bytesPerRow, rowPointers[j], bytesPerRow);
			}
		}
		//	m_nBitsPerComponent = nBitsPerComponent;

		ret=new TCBitmap(filename,imageData,nWidth,nHeight,RGBA_8888);
		ret->autoRelease();
		imageData  = 0;
	} while (0);

	TC_DELETE_ARRAY(imageData);

	if (png_ptr)
	{
		png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
	}
	return ret;
}

TCBitmap* TCPngUtils::decodePngByFileNameInZip(const char* zipPath,const char* filename){

	unsigned long filesize;
	unsigned char* buffer=TCFileUtils::getFileDataFromZip(zipPath,filename,&filesize);
	TCBitmap* ret=TCPngUtils::decodePngByFileData(filename,buffer,filesize);
	if(ret==NULL){
		DebugLog("init width pngData failed");
		return NULL;
	}
	DebugLog("decode png file success!!");
	return ret;
}

NS_TC_END