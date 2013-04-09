#ifndef __TC_MEMORY_STATISTICS_H__
#define __TC_MEMORY_STATISTICS_H__
#include "TCCommon.h"
NS_TC_BEGIN

class MemoryStatistic{

	friend class TCObject;

private:
	static int _objectCount;

public:
	static int objectCount(){
		return _objectCount;
	}

};

NS_TC_END

#endif