#ifndef __MAPDATA_H__
#define __MAPDATA_H__

#include "AutoReleaseObject.h"
#include <string>
USING_NS_TC;
class MapData:public AutoReleaseObject{

private:
	int _xsize;
	int _ysize;
	int _fruitCount;
	char** _data;
	MapData();
	~MapData();
	void init(const std::string& filename);
public:

	int sizeX(){
		return _xsize;
	}
	int sizeY(){
		return _ysize;
	}
	int fruitCount();

	char getInfo(int x,int y) const{
		return _data[x][y];
	}
	static MapData* readFrom(const std::string& fileName);
};
#endif