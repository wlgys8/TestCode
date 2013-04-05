#include <string.h>
#include "TCSceneRenderer.h"
#include "GLES/gl.h"

NS_TC_BEGIN
TCSceneRenderer::TCSceneRenderer():
_size(0),
_lastTextureID(0),
_capacity(100)
{
	_vertexBuffer=new float[2*4*_capacity];
	_uvBuffer=new float[2*4*_capacity];
	_indicesBuffer=new unsigned short[6*_capacity];
	_colorBuffer=new unsigned char[4*4*_capacity];
}
TCSceneRenderer::~TCSceneRenderer(){
	TC_DELETE_ARRAY(_vertexBuffer);
	TC_DELETE_ARRAY(_uvBuffer);
	TC_DELETE_ARRAY(_indicesBuffer);
	TC_DELETE_ARRAY(_colorBuffer);
}

void TCSceneRenderer::checkAndExpand(){
	if(_size==_capacity){
			int newCapacity=2*_capacity;
			float* newVertexBuffer=new float[2*4*newCapacity];
			float* newUvBuffer=new float[2*4*newCapacity];
			unsigned char* newColorBuffer=new unsigned char[4*4*newCapacity];
			unsigned short* newIndices=new unsigned short[6*newCapacity];
			memcpy(newVertexBuffer,_vertexBuffer,sizeof(float)*2*4*_capacity);
			memcpy(newUvBuffer,_uvBuffer,sizeof(float)*2*4*_capacity);
			memcpy(newColorBuffer,_colorBuffer,sizeof(unsigned char)*4*4*_capacity);
			memcpy(newIndices,_indicesBuffer,sizeof(unsigned short)*6*_capacity);
			TC_DELETE_ARRAY(_vertexBuffer);
			TC_DELETE_ARRAY(_uvBuffer);
			TC_DELETE_ARRAY(_colorBuffer);
			TC_DELETE_ARRAY(_indicesBuffer);
			_vertexBuffer=newVertexBuffer;
			_uvBuffer=newUvBuffer;
			_colorBuffer=newColorBuffer;
			_indicesBuffer=newIndices;
			_capacity=newCapacity;
			DebugLog("[TCSceneRenderer]Expand Capacity to %d",_capacity);
	}
}
void TCSceneRenderer::drawBatch(const Paint& paint){
	int size=_size;
	if(size==0){
		return;
	}
	glBlendFunc(paint.blendSrc(),paint.blendDst());
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_lastTextureID);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,_vertexBuffer);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2,GL_FLOAT,0,_uvBuffer);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_UNSIGNED_BYTE,0,_colorBuffer);
	glDrawElements(GL_TRIANGLES,6*size,GL_UNSIGNED_SHORT,_indicesBuffer);
}
void TCSceneRenderer::flush(){
	drawBatch(_lastPaint);
	_size=0;
	_lastTextureID=0;
}
void TCSceneRenderer::render(const int& textureID,Vector2f* vertex,
	Vector2f* uv, const Paint& paint){
	if(textureID<0){
		DebugLog("texture id is 0!!");
		return;
	}
	checkAndExpand(); 
	if(_lastTextureID==0){
		_lastTextureID=textureID;
		_lastPaint=paint;
	}
	else if(_lastTextureID!=textureID){
		//draw
		flush();
		_lastTextureID=textureID;
		_lastPaint=paint;
	}else if(!_lastPaint.isBatchable(paint)){
		flush();
		_lastPaint=paint;
		_lastTextureID=textureID;
	}
	
	Color color=paint.color();
	for(int i=0;i<4;i++){
		_vertexBuffer[8*_size+2*i]=vertex[i].x;
		_vertexBuffer[8*_size+2*i+1]=vertex[i].y;
		_uvBuffer[8*_size+2*i]=uv[i].x;
		_uvBuffer[8*_size+2*i+1]=uv[i].y;
		_colorBuffer[16*_size+4*i]=(unsigned char)(color.r()*255);
		_colorBuffer[16*_size+4*i+1]=(unsigned char)(color.g()*255);
		_colorBuffer[16*_size+4*i+2]=(unsigned char)(color.b()*255);
		_colorBuffer[16*_size+4*i+3]=(unsigned char)(color.a()*255);
	}
	_indicesBuffer[6*_size]=4*_size;
	_indicesBuffer[6*_size+1]=4*_size+1;
	_indicesBuffer[6*_size+2]=4*_size+3;
	_indicesBuffer[6*_size+3]=4*_size+3;
	_indicesBuffer[6*_size+4]=4*_size+1;
	_indicesBuffer[6*_size+5]=4*_size+2;
	_size++;
}

static const unsigned short rectIndices[6]={
	0,1,3,3,1,2
};
void TCSceneRenderer::renderSolidRect(Vector2f* vertex,const Paint& paint){
	flush();
	Color color= paint.color();
	for(int i=0;i<4;i++){
		_vertexBuffer[2*i]=vertex[i].x;
		_vertexBuffer[2*i+1]=vertex[i].y;
		_colorBuffer[4*i]=(unsigned char)(color.r()*255);
		_colorBuffer[4*i+1]=(unsigned char)(color.g()*255);
		_colorBuffer[4*i+2]=(unsigned char)(color.b()*255);
		_colorBuffer[4*i+3]=(unsigned char)(color.a()*255);
	}
	glBlendFunc(paint.blendSrc(),paint.blendDst());
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,_vertexBuffer);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_UNSIGNED_BYTE,0,_colorBuffer);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,rectIndices);
}

TCSceneRenderer* TCSceneRenderer::instance(){
	static TCSceneRenderer _instance;
	return &_instance;
}
NS_TC_END