#include "Map/MapData.h"
#include "TCResources.h"
#include <iostream>
#include<sstream>
#include "DataStream.h"
void MapData::init(const std::string& filename){
	DataStream* dataStream=TCResources::loadDataStreamInAssets(filename);
	std::istringstream ins((char*)dataStream->data());
	std::string str;
	std::getline(ins,str);//get first line

	std::istringstream firstLine(str);
	std::getline(firstLine,str,',');
	_xsize=atoi(str.c_str());
	std::getline(firstLine,str,',');
	_ysize=atoi(str.c_str());

	_data=new char*[_ysize];
	int i=0;
	while(std::getline(ins,str)){
		std::istringstream line(str);
		_data[i]=new char[_xsize];
		int j=0;
		while(std::getline(line,str,',')){
			_data[i][j]=str[0];
			if(_data[i][j]=='1'){
				_fruitCount++;
			}
			j++;
			if(j==_xsize){
				break;
			}
		}
		i++;
		if(i==_ysize){
			break;
		}
	}
	
}
int MapData::fruitCount(){
	return _fruitCount;
}
MapData::MapData():
_xsize(0),
	_ysize(0),
	_fruitCount(0)
{
	_data=0;
}

MapData::~MapData(){
	if(_data){
		for(int i=0;i<_ysize;i++){
			TC_DELETE_ARRAY(_data[i]);
		}
		TC_DELETE_ARRAY(_data);
		_data=0;
	}
}

MapData* MapData::readFrom(const std::string& fileName){
	MapData* mp=new MapData();
	mp->init(fileName);
	mp->autoRelease();
	return mp;
}

