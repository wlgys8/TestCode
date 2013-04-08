#ifndef __TC_RENDERSTATISTICS_H__
#define __TC_RENDERSTATISTICS_H__
#include "TCCommon.h"
NS_TC_BEGIN

class RenderStatistics{
	friend class TCSceneRenderer;
private:
	static int _batched;
	static int _drawCalls;

public:
	static void clear(); 
	static int batched();
	static int drawCalls();
};

NS_TC_END
#endif