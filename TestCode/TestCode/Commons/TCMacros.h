#ifndef __TC_MACROS_H__
#define __TC_MACROS_H__
#define DEBUG
#define NS_TC_BEGIN    namespace testCode{
#define NS_TC_END		}
#define USING_NS_TC    using namespace testCode;

#define TC_SCREEN_ORIENTION_PORTRAIT 0
#define TC_SCREEN_ORIENTION_LANDSCAPE 1
#define TC_SCREEN_ORIENTION TC_SCREEN_ORIENTION_LANDSCAPE

#define TC_DELETE(p)			if(p) { delete (p); (p) = 0; }
#define TC_DELETE_ARRAY(p)    if(p) { delete[] (p); (p) = 0; }
#define TC_RELEASE(p)		if(p) {p->release();p=0;}

#endif