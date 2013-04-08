#include "Map/MapDataManager.h"

const int MAP_COUNT=2;
static std::string mapNames[MAP_COUNT]={
	"level_0.txt",
	"level_1.txt"
};

MapDataManager::MapDataManager(){

}

void MapDataManager::loadAllMapData(){
	for(int i=0;i<MAP_COUNT;i++){
		MapData* data=MapData::readFrom("levels/"+mapNames[i]);
		if(data){
			_dataMap[mapNames[i]]=data;
			data->retain();
			DebugLog("load %s success",mapNames[i].c_str());
		}else{
			DebugLog("load mapData %s failed.",mapNames[i].c_str());

		}
	}
}

MapData* MapDataManager::find(const std::string& name){
	DebugLog("find map data:%s",name.c_str());
	DataMap::iterator it=_dataMap.find(name);
	if(it!=_dataMap.end()){
		return it->second;
	}
	return 0;
}

MapDataManager::~MapDataManager(){
	DataMap::iterator it;
	for(it=_dataMap.begin();it!=_dataMap.end();it++){
		it->second->release();
	}
	_dataMap.clear();
}

MapDataManager* MapDataManager::instance(){
	static MapDataManager ret;
	return &ret;
}