#ifndef __TC_AUDIOMANAGER_H__
#define __TC_AUDIOMANAGER_H__
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include "alc.h"
#include "al.h"
#include "TCMacros.h"
#include "TCSingleton.h"
#include "Audio/TCAudioBuffer.h"
NS_TC_BEGIN
typedef struct {
	char  riff[4];//'RIFF'
	unsigned int riffSize;
	char  wave[4];//'WAVE'
	char  fmt[4];//'fmt '
	unsigned int fmtSize;
	unsigned short format;
	unsigned short channels;
	unsigned int samplesPerSec;
	unsigned int bytesPerSec;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char  data[4];//'data'
	unsigned int dataSize;
}BasicWAVEHeader;


class AudioSource:public AutoReleaseObject{
	friend class AudioManager;
private:
	ALuint _source;
	AudioSource(const ALuint& source);
	~AudioSource();
public:
	
	void play();

};


class AudioManager{
	typedef std::map<std::string,AudioBuffer*>  BufferMap;
private:
	AudioManager();
	~AudioManager();
	ALCdevice* _device;
	ALCcontext* _context;
	BufferMap _bufferMap;
	unsigned char* loadwav(unsigned char*  fileStream,const unsigned long& size,BasicWAVEHeader* header);
	unsigned char* loadwav(const char* filename,BasicWAVEHeader* header);

	ALuint createBufferFromWave(unsigned char* data,BasicWAVEHeader header);

public:
	AudioBuffer* load(const std::string& filePath,unsigned char* fileStream,const unsigned long& size);
	AudioSource* createSource(const AudioBuffer* buffer);
	AudioSource* createSource(const std::string& filePath);
	void unload(const std::string& filePath);

	AudioBuffer* find(const std::string& filePath);

	static AudioManager* instance();
};

NS_TC_END


#endif



