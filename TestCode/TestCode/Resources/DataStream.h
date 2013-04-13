#ifndef __TC_DATASTREAM_H__
#define __TC_DATASTREAM_H__

#include "AutoReleaseObject.h"

NS_TC_BEGIN


class DataStream:public AutoReleaseObject{

private:
	unsigned char* _stream;
	unsigned long _size;
	DataStream(unsigned char* stream,unsigned long size);
	~DataStream();
public:

	const unsigned char* data()const;
	
	const unsigned long& size() const{
		return _size;
	}
	void releaseData();

	static DataStream* alloc(unsigned char* stream,unsigned long size);

};


NS_TC_END
#endif