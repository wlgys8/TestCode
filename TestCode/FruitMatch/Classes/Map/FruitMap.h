#ifndef __FRUITMAP_H__
#define __FRUITMAP_H__
#include "TCSingleton.h"
#include "Fruit/Fruit.h"
#include <set>
#include "TCTouchComponent.h"
#include <list>
USING_NS_TC;

class FruitMap:public TCSingleton<FruitMap>{
	friend class TCSingleton<FruitMap>;
	typedef  Fruit* ptr_fruit;
public:
	inline BaseNode* node(){
		return _node;
	}
	bool match(const int& i1,const int& j1,const int& i2,const int& j2,std::list<Vector2>* path);
	Vector2 selectedOne;
	Vector2 selectedTwo;

	Vector2 xy2ij(Vector2f xy);
	Vector2f ij2xy(Vector2 ij);

	int select( Vector2 ij);//0:match,1=unmatch,2=wait for next select
protected:
	FruitMap();
private:
	ptr_fruit** _fruitMap;//null represent empty
	BaseNode* _node;
	~FruitMap();
	
	bool isConnectedDirectly(Vector2 v1,Vector2 v2); 

	bool isConnectedByOneCross(Vector2 v1,Vector2 v2,std::list<Vector2>* path);

	bool isConnectedByTwoCross(Vector2 v1,Vector2 v2,std::list<Vector2>* path);

};
#endif