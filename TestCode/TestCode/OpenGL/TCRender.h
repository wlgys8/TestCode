#ifndef __TC_RENDER_H__
#define __TC_RENDER_H__

#include "TCCommon.h"
#include "tcgles.h"
#include "TCSingleton.h"

NS_TC_BEGIN
class TCRender{
private:
	TCRender();
	~TCRender();
public:
	void onResize(long width,long height);
	void onRender();

	static TCRender* instance();
};

NS_TC_END
#endif