#ifndef __TC_AUDIO_BUFFER_H__
#define __TC_AUDIO_BUFFER_H__
#include "alc.h"
#include "al.h"
#include "AutoReleaseObject.h"
#include <string>

NS_TC_BEGIN

class AudioBuffer:public AutoReleaseObject{
	friend class AudioManager;
private:
	ALuint _bufferId;
	std::string _name;
protected:
	AudioBuffer(const ALuint& bufferId,const std::string& name);
	~AudioBuffer();
public:
	const std::string& name() const;

	inline  int bufferId() const {
		return _bufferId;
	}

};

NS_TC_END

#endif