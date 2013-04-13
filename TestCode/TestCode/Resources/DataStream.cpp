#include "DataStream.h"

NS_TC_BEGIN

DataStream::DataStream(unsigned char* stream,unsigned long size):
_size(size),
_stream(stream)
{

}

const unsigned char* DataStream::data() const{
	return _stream;
}

void DataStream::releaseData(){
	TC_DELETE_ARRAY(_stream);
	_size=0;
}
DataStream::~DataStream(){
	TC_DELETE_ARRAY(_stream);
}

DataStream* DataStream::alloc(unsigned char* stream,unsigned long size){
	DataStream* ret=new DataStream(stream,size);
	ret->autoRelease();
	return ret;
}

NS_TC_END