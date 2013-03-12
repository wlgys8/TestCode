#include "FruitMap.h"
#include "TCVector2f.h"
#include "TCTouchComponent.h"
#include "GameMain.h"
#include "TCRandom.h"
#include "Map/ConnectionEffect.h"
static int xsize=9;
static int ysize=10;
static int xoffset=-200;
static int yoffset=-300;
FruitMap::FruitMap(){
	selectedOne=Vector2(-1,-1);
	selectedTwo=Vector2(-1,-1);
	_node=BaseNode::alloc();
	_node->retain<BaseNode>();
	_fruitMap=new ptr_fruit*[xsize];
	FruitType types[]={
		FRUIT_APPLE,
		FRUIT_BOLO,
		FRUIT_CAOMEI,FRUIT_MANGGUO,
		FRUIT_ORANGE,
		FRUIT_PUTAO,
		FRUIT_XIGUA,
		FRUIT_YINTAO,
		FRUTT_LANMEI,
	};
	srand((unsigned)time(NULL));
	int* fruitT;
	int halfSize = (xsize - 2) * (ysize - 2) / 2;
	fruitT = new int[halfSize];
	for(int i = 0 ; i < halfSize ; i++){
		fruitT[i]=(int)(Random::value()*9);
	}
	int index = 0;
	for(int i=0;i<xsize;i++){
		_fruitMap[i]=new ptr_fruit[ysize];
		for(int j=0;j<ysize;j++){
			if(i!=0&&i!=xsize-1&&j!=0&&j!=ysize-1){
				Fruit* fruit=Fruit::alloc(types[fruitT[index]]);
				_fruitMap[i][j]=fruit;
				fruit->retain();
				_node->addChild(fruit->sprite());
				fruit->sprite()->setLocalPosition(Vector2f(xoffset+50*i,yoffset+50*j));

				index++;
				if(index >= halfSize){
					index = 0;
				}
			}else{
				_fruitMap[i][j]=0;
			}
		}
	}

	delete[] fruitT;
}

Vector2 FruitMap::xy2ij(Vector2f xy){
	int i=(int)((xy.x-xoffset+25)/50);
	int j=(int)((xy.y-yoffset+25)/50);
	return Vector2(i,j);
}
Vector2f FruitMap::ij2xy(Vector2 ij){
	return Vector2f(xoffset+50*ij.x,yoffset+50*ij.y);
}
int FruitMap::select(Vector2 ij){
	if(selectedOne.x<0){
		selectedOne=ij;
		return 3;
	}
	else{
		if(match(selectedOne.x,selectedOne.y,ij.x,ij.y)){
			DebugLog("match");
			ConnectionEffect::instance()->generateConnection(
				ij2xy(selectedOne),ij2xy(ij)
				);
			_fruitMap[selectedOne.x][selectedOne.y]->sprite()->removeSelf();
			_fruitMap[selectedOne.x][selectedOne.y]->release();
			_fruitMap[selectedOne.x][selectedOne.y]=0;

			_fruitMap[ij.x][ij.y]->sprite()->removeSelf();
			_fruitMap[ij.x][ij.y]->release();
			_fruitMap[ij.x][ij.y]=0;

			selectedOne.x=-1;
			selectedOne.y=-1;
			GameMain::instance()->role()->attack();
			return 0;
		}
		DebugLog("unmatch");
		selectedOne.x=-1;
		selectedOne.y=-1;
		return 1;
	}
}
bool FruitMap::isConnectedDirectly(Vector2 v1,Vector2 v2){
	if(v1.x==v2.x){
		if(v1.y<v2.y){
			int j;
			for(j=v1.y+1;j<v2.y;j++){
				if(_fruitMap[v1.x][j]){
					break;
				}
			}
			if(j==v2.y){
				return true;
			}
		}else if(v1.y>v2.y){
			int j;
			for(j=v2.y+1;j<v1.y;j++){
				if(_fruitMap[v1.x][j]){
					break;
				}
			}
			if(j==v1.y){
				return true;
			}
		}else{
			return false;
		}
	}else if(v1.y==v2.y){
		if(v1.x<v2.x){
			int i;
			for(i=v1.x+1;i<v2.x;i++){
				if(_fruitMap[i][v1.y]){
					break;
				}
			}
			if(i==v2.x){
				return true;
			}
		}else if(v1.x>v2.x){
			int i;
			for(i=v2.x+1;i<v1.x;i++){
				if(_fruitMap[i][v1.y]){
					break;
				}
			}
			if(i==v1.x){
				return true;
			}
		}else{
			return false;
		}
		return false;
	}
	return false;
}

bool FruitMap::isConnectedByOneCross(Vector2 v1,Vector2 v2){
	Vector2 c1=Vector2(v1.x,v2.y);
	Vector2 c2=Vector2(v2.x,v1.y);
	return (!_fruitMap[c1.x][c1.y]&&isConnectedDirectly(v1,c1)&&isConnectedDirectly(v2,c1))||
		(!_fruitMap[c2.x][c2.y]&&isConnectedDirectly(v1,c2)&&isConnectedDirectly(v2,c2));
}

bool FruitMap::isConnectedByTwoCross(Vector2 v1,Vector2 v2){
	int row=xsize;
	int col=ysize;
	for(int i=v1.x-1;i>=0;i--){
		if(_fruitMap[i][v1.y]){
			break;
		}
		if(isConnectedByOneCross(Vector2(i,v1.y),v2)){
			return true;
		}
	}
	for(int i=v1.x+1;i<row;i++){
		if(_fruitMap[i][v1.y]){
			break;
		}
		if(isConnectedByOneCross(Vector2(i,v1.y),v2)){
			return true;
		}
	}
	for(int j=v1.y-1;j>=0;j--){
		if(_fruitMap[v1.x][j]){
			break;
		}
		if(isConnectedByOneCross(Vector2(v1.x,j),v2)){
			return true;
		}
	}
	for(int j=v1.y+1;j<col;j++){
		if(_fruitMap[v1.x][j]){
			break;
		}
		if(isConnectedByOneCross(Vector2(v1.x,j),v2)){
			return true;
		}
	}
	return false;
}
bool FruitMap::match(const int& i1,const int& j1,const int& i2,const int& j2){
	ptr_fruit f1=_fruitMap[i1][j1];
	ptr_fruit f2=_fruitMap[i2][j2];
	if(!f1||!f1){
		return false;
	}
	if(f1->type()!=f2->type()){
		return false;
	}
	Vector2 v1=Vector2(i1,j1);
	Vector2 v2=Vector2(i2,j2);
	if(isConnectedDirectly(v1,v2)){
		return true;
	}
	if(isConnectedByOneCross(v1,v2)){
		return true;
	}
	if(isConnectedByTwoCross(v1,v2)){
		return true;
	}
	return false;
}

FruitMap::~FruitMap(){
	for(int i=0;i<xsize;i++){
		for(int j=0;j<ysize;j++){
			if(_fruitMap[i][j]){
				_fruitMap[i][j]->release();
				_fruitMap[i][j]=0;
			}
		}
		TC_DELETE_ARRAY(_fruitMap[i]);
	}
	TC_DELETE_ARRAY(_fruitMap);
	_fruitMap=NULL;
	_node->release();
	_node=0;
}