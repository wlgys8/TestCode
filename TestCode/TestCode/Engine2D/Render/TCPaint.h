#ifndef __TC_PAINT_H__
#define __TC_PAINT_H__
#include "tcgles.h"
#include "TCMacros.h"
#include "TCColor.h"
NS_TC_BEGIN

#define  BLEND_ZERO GL_ZERO
#define BLEND_ONE  GL_ONE
#define BLEND_SRC_ALPHA GL_SRC_ALPHA
#define BLEND_DST_ALPHA GL_DST_ALPHA
#define BLEND_ONE_MINUS_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
#define BLEND_ONE_MINUS_DST_ALPHA GL_ONE_MINUS_DST_ALPHA
typedef GLenum BlendMode;

class Paint{

private:
	BlendMode _blendSrc;
	BlendMode _blendDst;
	Color _color;
public:
	Paint();
	~Paint();
	void setBlendMode(const BlendMode& src,const BlendMode& dst);
	inline BlendMode blendSrc()const{
		return _blendSrc;
	}
	inline BlendMode blendDst() const{
		return _blendDst;
	}
	bool isBatchable(const Paint& p);

	inline void setColor(const Color& color){
		_color=color;
	}
	inline Color color() const {
		return _color;
	}

	friend bool operator==(const Paint& p1,const Paint& p2);
	friend bool operator!=(const Paint& p1,const Paint& p2);
};
NS_TC_END

#endif