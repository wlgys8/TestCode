#include "Audio/TCAudioBuffer.h"
NS_TC_BEGIN
AudioBuffer::AudioBuffer(const ALuint& bufferId,const std::string& name):
_bufferId(bufferId),
	_name(name)
{


}

AudioBuffer::~AudioBuffer(){
	alDeleteBuffers(1,&_bufferId);
}

const std::string&AudioBuffer::name() const {
	return _name;
}
NS_TC_END