#ifndef __TC_AUDIOLOADER_H__
#define __TC_AUDIOLOADER_H__

#include "TCCommon.h"
NS_TC_BEGIN

class AudioLoader{


public:

	static unsigned char* loadMp3(unsigned char* fileStream,const int& size);

	static unsigned char* loadOgg(unsigned char* fileStream,const int& size);

};
NS_TC_END
#endif