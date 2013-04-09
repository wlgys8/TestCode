#include "Debug/TCRenderStatistics.h"

NS_TC_BEGIN

int RenderStatistics::_batched=0;
int RenderStatistics::_drawCalls=0;

void RenderStatistics::clear(){
	_batched=0;
	_drawCalls=0;
}

int RenderStatistics::batched(){
	return _batched;
}

int RenderStatistics::drawCalls(){
	return _drawCalls;
}

NS_TC_END
