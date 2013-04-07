#ifndef __MAP_DATA_MANAGER_H__
#define __MAP_DATA_MANAGER_H__

#include "Map/MapData.h"
#include <map>

USING_NS_TC;

class MapDataManager{

	typedef std::map<std::string,MapData*> DataMap;
private:
	DataMap _dataMap;

	~MapDataManager();
	MapDataManager();
public:

	void loadAllMapData();

	MapData* find(const std::string& name);

	static MapDataManager* instance();

};
#endif