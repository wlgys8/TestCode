#ifndef __TC_AUDIOSOURCE_H__
#define __TC_AUDIOSOURCE_H__
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>


class ATest{
	typedef std::map<std::string,std::string>  SourceMap;

public:
	SourceMap _map;
	ATest();
};



#endif