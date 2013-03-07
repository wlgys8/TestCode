#include "AutoReleaseObject.h"
NS_TC_BEGIN
void AutoReleaseObject::autoRelease(){
	AutoReleasePool::instance()->add(this);
}

NS_TC_END