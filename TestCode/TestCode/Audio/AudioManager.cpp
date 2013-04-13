#include "AudioManager.h"
#include "alc.h"
#include "Audio/TCAudioSource.h"
#include "TCFileUtils.h"
NS_TC_BEGIN

AudioSource::AudioSource(const ALuint& source){
	_source=source;
}

AudioSource::~AudioSource(){
	if(_source){
		alDeleteSources(1,&_source);
		_source=0;
	}
}
void AudioSource::play(bool loop){
	if(loop){
		alSourcei(_source,AL_LOOPING,AL_TRUE);
	}
	alSourcePlay(_source);
}
AudioManager::AudioManager(){
	_device = 0;
	_context = 0;
	const ALint context_attribs[] = { ALC_FREQUENCY, 22050, 0 };

	// Initialization
	_device = alcOpenDevice(0);
	if(!_device){
		DebugLog("can't open device");
		return;
	}
	_context = alcCreateContext(_device, context_attribs);
	alcMakeContextCurrent(_context);
}

AudioManager::~AudioManager(){
	BufferMap::iterator it=_bufferMap.begin();
	for(it=_bufferMap.begin();it!=_bufferMap.end();it++){
		it->second->release();
	}
	_bufferMap.clear();
	alcMakeContextCurrent(0);
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

AudioBuffer* AudioManager::find(const std::string& filePath){
	BufferMap::iterator it=_bufferMap.find(filePath);
	if(it!=_bufferMap.end()){
		return it->second;
	}
	return 0;
}

AudioBuffer* AudioManager::load(const std::string& filePath,DataStream* stream){
	AudioBuffer* ret=find(filePath);
	if(ret!=0){
		return ret;
	}
	unsigned char* wavBuffer=0;
	do{
		BasicWAVEHeader header;
		wavBuffer=loadwav(stream->data(),stream->size(),&header);
		if(!wavBuffer){
			DebugLog("Load audio failed:%s",filePath.c_str());
			break;
		}

		ALuint buffer= createBufferFromWave(wavBuffer,header);
		if(!buffer){
			DebugLog("Create Buffer From Wave Failed");
			break;
		}
		ret=new AudioBuffer(buffer,filePath);
		_bufferMap[filePath]=ret;
		DebugLog("load %s success!",filePath.c_str());
	}while(0);
	TC_DELETE_ARRAY(wavBuffer);
	return ret;
}

AudioSource* AudioManager::createSource(const AudioBuffer* buffer){
	ALuint source = 0;
	alGenSources(1, &source );
	if(!source){
		DebugLog("alGenSources Failed");
		return 0;
	}
	alSourcei(source, AL_BUFFER, buffer->bufferId());
	AudioSource* ret=new AudioSource(source);
	ret->autoRelease();
	return ret;
}

AudioSource* AudioManager::createSource(const std::string& filePath){
	AudioBuffer* buf= find(filePath);
	if(!buf){
		DebugLog("%s should be load first",filePath.c_str());
		return 0;
	}
	return createSource(buf);
}
unsigned char* AudioManager::loadwav(const unsigned char* fileStream,const unsigned long& size,BasicWAVEHeader* header){
	size_t headerSize=sizeof(BasicWAVEHeader);
	unsigned char* buffer=0;
	do{
		if(size<headerSize){
			break;
		}
		memcpy(header,fileStream,headerSize);
		if (!(//these things *must* be valid with this basic header
			memcmp("RIFF",header->riff,4) ||
			memcmp("WAVE",header->wave,4) ||
			memcmp("fmt ",header->fmt,4)  ||
			memcmp("data",header->data,4)
			)){
				buffer=(unsigned char*)malloc(header->dataSize);
				if(!buffer){
					break;
				}
				memcpy(buffer,fileStream,header->dataSize);
		}
	}while(0);

	return buffer;
}

ALuint AudioManager::createBufferFromWave(unsigned char* data,BasicWAVEHeader header){
	ALuint buffer = 0;
	ALuint format = 0;
	switch (header.bitsPerSample){
	case 8:
		format = (header.channels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
		break;
	case 16:
		format = (header.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		break;
	default:
		return 0;
	}

	alGenBuffers(1,&buffer);
	alBufferData(buffer,format,data,header.dataSize,header.samplesPerSec);
	return buffer;
}


void AudioManager::unload(const std::string& filePath){
	BufferMap::iterator it=_bufferMap.find(filePath);
	if(it==_bufferMap.end()){
		DebugLog("Can't find audio:%s",filePath.c_str());
		return;
	}
	if(it->second->referCount()!=1){
		DebugLog("%s not really unloaded",filePath.c_str());
	}
	it->second->release();
	_bufferMap.erase(it);
}

AudioManager* AudioManager::instance(){
	static AudioManager _instance;
	return &_instance;
}

NS_TC_END