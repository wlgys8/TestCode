#ifndef __TC_IMAGELISTRENDERELEMENT_H__
#define __TC_IMAGELISTRENDERELEMENT_H__
#include "RenderElements/TCRenderElement.h"

NS_TC_BEGIN
class TextureRegion;
class ImageListRenderElement:public RenderElement{

	typedef std::vector<TextureRegion*> ImageList;
private:
	ImageList _imageList;
	Vector2f _offset;
	Vector2f _rawSize;
	ImageListRenderElement();
	~ImageListRenderElement();
public:
	//====override methoid begin====
	void onRender(const TCMatrix3x3& localToWorldMatrix,const Paint& paint);

	Vector2f rawSize();

	void setList(std::vector<TextureRegion*> imageList);

	void clearList();

	void append(TextureRegion* region);

	void setOffset(const Vector2f& offset);

	static ImageListRenderElement* alloc();
};

NS_TC_END
#endif