#include "TCPaint.h"
NS_TC_BEGIN

Paint::Paint():_blendSrc(BLEND_SRC_ALPHA),_blendDst(BLEND_ONE_MINUS_SRC_ALPHA){

}
Paint::~Paint(){

}
void Paint::setBlendMode(const BlendMode& src,const BlendMode& dst){
	_blendSrc=src;
	_blendDst=dst;
}

bool operator==(const Paint& p1,const Paint& p2){
	return p1._blendSrc==p2._blendSrc&&p1._blendDst==p2._blendDst;
}
bool operator!=(const Paint& p1,const Paint& p2){
	return !(p1==p2);
}

NS_TC_END