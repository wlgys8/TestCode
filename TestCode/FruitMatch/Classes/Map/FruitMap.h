#ifndef __FRUITMAP_H__
#define __FRUITMAP_H__
#include "TCSingleton.h"
#include "Fruit/Fruit.h"
#include <set>
#include "TCTouchComponent.h"
#include <list>
#include "Audio/AudioManager.h"
#include "Map/MapData.h"

USING_NS_TC;

class FruitMap:public TCSingleton<FruitMap>{
	friend class TCSingleton<FruitMap>;
	typedef  Fruit* ptr_fruit;
public:
	Vector2 selectedOne;

	inline BaseNode* node(){
		return _node;
	}
	bool match(const int& i1,const int& j1,const int& i2,const int& j2,std::list<Vector2>* path);

	Vector2 xy2ij(Vector2f xy);
	Vector2f ij2xy(Vector2 ij);

	int select( Vector2 ij);//0:match,1=unmatch,2=wait for next select
	void clearMap();
	void resetMap(MapData* data=0);
	void refreshMap();
	bool findAvaliablePair(std::list<Vector2> *path);

	

private:
	void generateMap(MapData* data=0);

protected:
	FruitMap();
private:
	ptr_fruit** _fruitMap;//null represent empty
	MapData* _data;
	BaseNode* _node;
	AudioSource* _matchSound;
	int _restFruitCount;
	std::list<Vector2> _avaliablePath;
	~FruitMap();

	bool isConnectedDirectly(Vector2 v1,Vector2 v2); 

	bool isConnectedByOneCross(Vector2 v1,Vector2 v2,std::list<Vector2>* path);

	bool isConnectedByTwoCross(Vector2 v1,Vector2 v2,std::list<Vector2>* path);

};
#endif