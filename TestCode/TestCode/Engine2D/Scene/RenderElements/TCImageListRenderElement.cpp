#include "RenderElements/TCImageListRenderElement.h"
#include "TextureRegion.h"
#include "TCRenderUtil.h"
NS_TC_BEGIN

ImageListRenderElement::ImageListRenderElement():
_offset(Vector2f(0,0)),
_rawSize(Vector2f(0,0))
{

}

void ImageListRenderElement::setList(std::vector<TextureRegion*> imageList){
	clearList();
	_imageList=imageList;
	ImageList::iterator it;
	for(it=_imageList.begin();it!=_imageList.end();it++){
		TextureRegion* region=(*it);
		region->retain();
		_rawSize.x+=region->width();
		if(region->height()>_rawSize.y){
			_rawSize.y=region->height();
		}
	}
}

void ImageListRenderElement::clearList(){
	ImageList::iterator it;
	for(it=_imageList.begin();it!=_imageList.end();it++){
		(*it)->release();
	}
	_imageList.clear();
	_rawSize=Vector2f::zero();
}

void ImageListRenderElement::append(TextureRegion* region){
	if(!region){
		return;
	}
	region->retain();
	_imageList.push_back(region);
	_rawSize.x+=region->width();
	if(region->height()>_rawSize.y){
		_rawSize.y=region->height();
	}
}
void ImageListRenderElement::setOffset(const Vector2f& offset){
	_offset=offset;
}

Vector2f ImageListRenderElement::rawSize(){
	return _rawSize;
}

void ImageListRenderElement::onRender(const TCMatrix3x3& localToWorldMatrix,const Paint& paint){
	ImageList::iterator it;
	float pos=0;
	for(it=_imageList.begin();it!=_imageList.end();it++){
		TextureRegion* image=(*it);
		float left=_offset.x+pos;
		float bottom=_offset.y-image->height();
		RenderUtil::renderImage(image->textureID(),
			Rect(left,bottom,image->width(),image->height()),
			image->region(),
			localToWorldMatrix,paint);
		pos+=image->width();
	}
}

ImageListRenderElement::~ImageListRenderElement(){
	clearList();
}

ImageListRenderElement* ImageListRenderElement::alloc(){
	ImageListRenderElement* ret=new ImageListRenderElement();
	ret->autoRelease();
	return ret;
}
NS_TC_END