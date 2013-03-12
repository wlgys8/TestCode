#ifndef __TC_RANDOM_H__
#define __TC_RANDOM_H__
#include "TCMacros.h"
NS_TC_BEGIN
class Random{

private:
	static bool _hasSetSeed;
public:
	static void setSeed(int seed);

	static float value();//[0,1]

	static float between(float min,float max);//[min,max]

};

NS_TC_END
#endif