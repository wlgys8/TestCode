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


class AudioSource{
	friend class AudioManager;
private:
	BasicWAVEHeader _header;
	ALuint _buffer;
	ALuint _source;

public:
	AudioSource();
	AudioSource(const BasicWAVEHeader& header,const ALuint& buffer,const ALuint& source);
	~AudioSource();

};


class AudioManager:public TCSingleton<AudioManager>{
	friend class TCSingleton<AudioManager>;
	typedef std::map<std::string,AudioSource>  SourceMap;
private:
	AudioManager();
	~AudioManager();
	ALCdevice* _device;
	ALCcontext* _context;
	SourceMap _sourceMap;
	char* loadwav(const char*  filename,BasicWAVEHeader* header);
	ALuint createBufferFromWave(char* data,BasicWAVEHeader header);


public:
	void load(const  std::string& filePath);
	void play(const std::string& filePath);
	void unload(const std::string& filePath);
};

NS_TC_END


#endif



