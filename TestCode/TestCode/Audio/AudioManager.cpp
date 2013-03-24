#include "AudioManager.h"
#include "alc.h"
#include "Audio/TCAudioSource.h"
NS_TC_BEGIN

	AudioSource::AudioSource(const BasicWAVEHeader& header,const ALuint& buffer,const ALuint& source){
		_header=header;
		_buffer=buffer;
		_source=source;
}

AudioSource::AudioSource(){
	_buffer=0;
	_source=0;
}
AudioSource::~AudioSource(){

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
	SourceMap::iterator it=_sourceMap.begin();
	for(it=_sourceMap.begin();it!=_sourceMap.end();it++){
		alDeleteSources(1,&(it->second._source));
	}
	_sourceMap.clear();

	alcMakeContextCurrent(0);
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

void AudioManager::load(const std::string& path){

	SourceMap::iterator it=_sourceMap.find(path);
	if(it!=_sourceMap.end()){
		DebugLog("audio has loaded:%s",path.c_str());
		return;
	}
	char* fileBuffer=0;
	do{
		BasicWAVEHeader header;
		fileBuffer=loadwav(path.c_str(),&header);
		if(!fileBuffer){
			DebugLog("Load audio failed:%s",path.c_str());
			break;
		}
		
		ALuint buffer= createBufferFromWave(fileBuffer,header);
		if(!buffer){
			DebugLog("Create Buffer From Wave Failed");
			break;
		}
		ALuint source = 0;
		alGenSources(1, &source );
		if(!source){
			DebugLog("alGenSources Failed");
			break;
		}
		alSourcei(source, AL_BUFFER, buffer);
		AudioSource src=AudioSource(header,buffer,source);
		std::string key=path;
		_sourceMap[key]=src;
	}while(0);
	TC_DELETE_ARRAY(fileBuffer);
}

char* AudioManager::loadwav(const char*  filename,BasicWAVEHeader* header){
	char* buffer = 0;
	FILE* file = fopen(filename,"rb");
	if (!file) {
		return 0;
	}

	if (fread(header,sizeof(BasicWAVEHeader),1,file)){
		if (!(//these things *must* be valid with this basic header
			memcmp("RIFF",header->riff,4) ||
			memcmp("WAVE",header->wave,4) ||
			memcmp("fmt ",header->fmt,4)  ||
			memcmp("data",header->data,4)
			)){

				buffer = (char*)malloc(header->dataSize);
				if (buffer){
					if (fread(buffer,header->dataSize,1,file)){
						fclose(file);
						return buffer;
					}
					free(buffer);
				}
		}
	}
	fclose(file);
	return 0;
}

ALuint AudioManager::createBufferFromWave(char* data,BasicWAVEHeader header){
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



void AudioManager::play(const std::string& filename){
	SourceMap::iterator it= _sourceMap.find(filename);
	if(it==_sourceMap.end()){
		DebugLog("sound not existed:%s",filename.c_str());
		return;
	}
	AudioSource src=it->second;

	// Play source
	alSourcePlay(src._source);

	int        sourceState = AL_PLAYING;
//	do {
//		alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
	//} while(sourceState == AL_PLAYING);

	// Release source
//	alDeleteSources(1, &source);

}

void AudioManager::unload(const std::string& filePath){
	SourceMap::iterator it=_sourceMap.find(filePath);
	if(it==_sourceMap.end()){
		DebugLog("Can't find audio:%s",filePath.c_str());
		return;
	}
	alDeleteSources(1,&(it->second._source));
	_sourceMap.erase(it);
}

NS_TC_END