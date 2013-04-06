#include "TCAudioLoader.h"
#include "vorbisfile.h"

NS_TC_BEGIN

unsigned char* AudioLoader::loadMp3(unsigned char* fileStream,const int& size){
/*
	int mpgError=mpg123_init();
	if(mpgError!=MPG123_OK){
		DebugLog("failed to init mpg123");
		return 0;
	}
	
	mpg123_handle * mpg123=mpg123_new(mpg123_decoders()[0],&mpgError);
	mpg123_open_feed(mpg123);
	mpg123_feed(mpg123,fileStream,size);
	long rate;
	int channel;
	int encoding;
	mpgError=mpg123_getformat(mpg123,&rate,&channel,&encoding);

	DebugLog("%l,%d,%d",rate,channel,encoding);*/
	return 0;
	//mpg123_read()
//	mpg123_decode(mpg123,fileStream,size);
}

unsigned char* AudioLoader::loadOgg(unsigned char* fileStream,const int& size){

	return 0;
}


NS_TC_END