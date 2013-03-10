#include "TCPaint.h"
NS_TC_BEGIN

Paint::Paint():_blendSrc(BLEND_ONE),_blendDst(BLEND_ONE_MINUS_SRC_ALPHA),_color(Color(1,1,1,1)){

}
Paint::~Paint(){

}
void Paint::setBlendMode(const BlendMode& src,const BlendMode& dst){
	_blendSrc=src;
	_blendDst=dst;
}

bool Paint::isBatchable(const Paint& p){
	return _blendSrc==p._blendSrc&&_blendDst==p._blendDst;
}

bool operator==(const Paint& p1,const Paint& p2){
	return p1._blendSrc==p2._blendSrc&&p1._blendDst==p2._blendDst&&p1._color==p2._color;
}
bool operator!=(const Paint& p1,const Paint& p2){
	return !(p1==p2);
}

NS_TC_END