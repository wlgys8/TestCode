#include "TCTexture.h"
#include "GLES/gl.h"
NS_TC_BEGIN

float TCTexture::_vertexArray[8]={0,0,0,0,0,0,0,0};
float TCTexture::_textureArray[8]={0,0,1,0,1,1,0,1};
unsigned short TCTexture::_indices[6]={0,1,3,3,1,2};
TCTexture::TCTexture():_texId(0),_width(0),_height(0){	
}

TCTexture::~TCTexture(){
	DebugLog("Destroy texture: %s",_filename.c_str());
	if(!isRecycled()){
		recycle();
	}
}
static void debugBitmap(TCBitmap* bitmap){
	for(int i=0;i<bitmap->width()*bitmap->height();i++){
		DebugLog("%d,%d,%d,%d",bitmap->pixelData()[4*i],bitmap->pixelData()[4*i+1],bitmap->pixelData()[4*i+2],bitmap->pixelData()[4*i+3]);
	}
}
TCTexture* TCTexture::createTextureFromBitmap(TCBitmap* bitmap){
	DebugLog("createTexture");
	if(bitmap==NULL){
		DebugLog("Bitmap is NULL");
		return NULL;
	}
//	debugBitmap(bitmap);
	TCTexture* ret=new TCTexture();
	ret->autoRelease();
	glEnable(GL_TEXTURE_2D); 
	glGenTextures(1,&ret->_texId);
	glBindTexture(GL_TEXTURE_2D,ret->_texId);
	if(bitmap->format()==RGBA_8888){
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,bitmap->width(),bitmap->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,bitmap->pixelData());
	}
	else if(bitmap->format()==RGBA_4444){
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,bitmap->width(),bitmap->height(),0,GL_RGBA,GL_UNSIGNED_SHORT_4_4_4_4,bitmap->pixelData());
	}
	else if(bitmap->format()==RGB_565){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap->width(),bitmap->height(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, bitmap->pixelData());
	}
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	ret->_width=bitmap->width();
	ret->_height=bitmap->height();
	DebugLog("end createTexture");
	return ret;
}

void calVertexArray(float left,float bottom,float width,float height,float* outArray){
	const float right=left+width;
	const float top=bottom+height;
	outArray[0]=left;
	outArray[1]=bottom;
	outArray[2]=right;
	outArray[3]=bottom;
	outArray[4]=right;
	outArray[5]=top;
	outArray[6]=left;
	outArray[7]=top;
}

void TCTexture::recycle(){
	glDeleteTextures(1,&_texId);
	_texId=0;
}
void TCTexture::drawAt(float x,float y, const Rect& src){

	calVertexArray(x+_width*src.xMin()-_width/2,y+_height*src.yMin()-_height/2,_width*src.width(),_height*src.height(),_vertexArray);
	calVertexArray(src.xMin(),src.yMin(),src.width(),src.height(),_textureArray);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_texId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,_vertexArray);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2,GL_FLOAT,0,_textureArray);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,_indices);
	glPopMatrix();

}






NS_TC_END