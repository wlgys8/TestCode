#include "FruitMap.h"
#include "TCVector2f.h"
#include "TCTouchComponent.h"
#include "GameMain.h"
#include "TCRandom.h"
#include "Map/ConnectionEffect.h"
#include "Audio/AudioManager.h"
#include "ui/GameOverDialog.h"
#include "data/GameData.h"
static int xsize=9;
static int ysize=13;
static int xoffset=-240;
static int yoffset=370;
static const int tileWidth=60;
static const int tileHeight=-60;

FruitMap::FruitMap(){
	selectedOne=Vector2(-1,-1);
	_node=BaseNode::alloc();
	_node->retain<BaseNode>();

	_matchSound=AudioManager::instance()->createSource("match.wav");
	_matchSound->retain();
	_data=0;
}
void FruitMap::loadMap(MapData* data){
	clearMap();
	generateMap(data);
}

void FruitMap::resetMap(){
	clearMap();
	generateMap(_data);
}

bool FruitMap::findAvaliablePair(std::list<Vector2> *path){
	if(!_fruitMap){
		return false;
	}
	typedef std::map<FruitType,std::vector<Vector2> > TypeMap;
	TypeMap typeMap;
	
	for (int i=0;i<ysize;i++)
	{
		for(int j=0;j<xsize;j++){
			ptr_fruit fruit= _fruitMap[i][j];
			if(!fruit){
				continue;
			}
			FruitType type=fruit->type();
			TypeMap::iterator it= typeMap.find(type);
			if(it==typeMap.end()){
				typeMap[type]=std::vector<Vector2>();
			}
			std::vector<Vector2>& list=typeMap[type];
			
			std::vector<Vector2>::iterator fit;

			for(fit=list.begin();fit!=list.end();fit++){
				if(match(i,j,(*fit).x,(*fit).y,path)){
					return true;
				}
			}
			
			list.push_back(Vector2(i,j));
		}
	}
	return false;
}
void FruitMap::generateMap(MapData* data){
	
	if(_fruitMap){
		clearMap();
	}
	if(_data){
		_data->autoRelease();
	}
	if(data){
		data->retain();
	}
	_data=data;
	if(!_data){
		return;
	}
	FruitType types[]={
		FRUIT_APPLE,
		FRUIT_BOLO,
		FRUIT_CAOMEI,FRUIT_MANGGUO,
		FRUIT_ORANGE,
		FRUIT_PUTAO,
		FRUIT_XIGUA,
		FRUIT_YINTAO,
		FRUTT_LANMEI,
		FRUIT_LI,
		FRUIT_YINXING,
		FRUIT_SIYECAO,
	};
	xsize=_data->sizeX();
	ysize=_data->sizeY();
	int* fruitT;
	int halfSize = _data->fruitCount() / 2;
	fruitT = new int[halfSize];
	for(int i = 0 ; i < halfSize ; i++){
		fruitT[i]=(int)(Random::value()*12);
	}
	int index = 0;

	_fruitMap=new ptr_fruit*[ysize];
	for(int i=0;i<ysize;i++){
		_fruitMap[i]=new ptr_fruit[xsize];
		for(int j=0;j<xsize;j++){
			if(_data->getInfo(i,j)=='1'){
				Fruit* fruit=Fruit::alloc(types[fruitT[index]]);
				_fruitMap[i][j]=fruit;
				fruit->retain();
				_node->addChild(fruit->sprite());
				fruit->sprite()->setLocalPosition(Vector2f(xoffset+tileWidth*j,yoffset+tileHeight*i));
				index++;
				_restFruitCount++;
				if(index >= halfSize){
					index = 0;
				}
			}else{
				_fruitMap[i][j]=0;
			}
		}
	}
	if(!findAvaliablePair(&_avaliablePath)){
		refreshMap();
	}
	delete[] fruitT;
}

void FruitMap::refreshMap(){
	std::vector<ptr_fruit> list=std::vector<ptr_fruit>();
	for(int i=0;i<ysize;i++){
		for(int j=0;j<xsize;j++){
			if(_fruitMap[i][j]){
				list.push_back(_fruitMap[i][j]);
			}
		}
	}
	for(int i=0;i<ysize;i++){
		for(int j=0;j<xsize;j++){
			if(_fruitMap[i][j]){
				int rd=(int)((list.size()-1)*Random::value());
				_fruitMap[i][j]=list[rd]; 
				_fruitMap[i][j]->sprite()->setLocalPosition(ij2xy(Vector2(i,j)));
				list.erase(list.begin()+rd);
				
			}
		}
	}
	findAvaliablePair(&_avaliablePath);
}
void FruitMap::clearMap(){
	if(!_fruitMap){
		return;
	}
	for(int i=0;i<ysize;i++){
		for(int j=0;j<xsize;j++){
			if(_fruitMap[i][j]){
				_fruitMap[i][j]->sprite()->removeSelf();
				_fruitMap[i][j]->autoRelease();
				_fruitMap[i][j]=0;
			}
		}
		TC_DELETE_ARRAY(_fruitMap[i]);
	}
	TC_DELETE_ARRAY(_fruitMap);
	_restFruitCount=0;
}

Vector2 FruitMap::xy2ij(Vector2f xy){
	int j=(int)((xy.x-xoffset+tileWidth/2)/tileWidth);
	int i=(int)((xy.y-yoffset+tileHeight/2)/tileHeight);
	return Vector2(i,j);
}
Vector2f FruitMap::ij2xy(Vector2 ij){
	return Vector2f(xoffset+tileWidth*ij.y,yoffset+tileHeight*ij.x);
}
int FruitMap::select(Vector2 ij){
	if(selectedOne.x<0){
		selectedOne=ij;
		return 2;
	}
	else{
		std::list<Vector2> path;
		if(match(selectedOne.x,selectedOne.y,ij.x,ij.y,&path)){
			std::list<Vector2f> fpath;
			std::list<Vector2>::iterator it;
			for(it=path.begin();it!=path.end();it++){
				fpath.push_back(ij2xy((*it)));
			}
			ConnectionEffect::instance()->generateConnection(
				fpath
				);
			_fruitMap[selectedOne.x][selectedOne.y]->sprite()->removeSelf();
			_fruitMap[selectedOne.x][selectedOne.y]->autoRelease();
			_fruitMap[selectedOne.x][selectedOne.y]=0;

			_fruitMap[ij.x][ij.y]->sprite()->removeSelf();
			_fruitMap[ij.x][ij.y]->autoRelease();
			_fruitMap[ij.x][ij.y]=0;

			selectedOne.x=-1;
			selectedOne.y=-1;
			_matchSound->play();
			_restFruitCount-=2;
			if(_restFruitCount<2){
				GameOverDialog::instance()->show(true);// over
				if(GameData::currentLevel==GameData::unlockedLevel){
					GameData::unlockedLevel++;
				}
				return 0;
			}

			if(_avaliablePath.front()==selectedOne||_avaliablePath.front()==ij||_avaliablePath.back()==selectedOne||_avaliablePath.back()==ij){
				if(!findAvaliablePair(&_avaliablePath)){
					refreshMap();
				}
			}
			return 0;
		}
		selectedOne=ij;
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

bool FruitMap::isConnectedByOneCross(Vector2 v1,Vector2 v2,std::list<Vector2>* path){
	Vector2 c1=Vector2(v1.x,v2.y);
	Vector2 c2=Vector2(v2.x,v1.y);
	if(!_fruitMap[c1.x][c1.y]&&isConnectedDirectly(v1,c1)&&isConnectedDirectly(v2,c1)){
		path->push_back(v1);
		path->push_back(c1);
		path->push_back(v2);
		return true;
	}else if(!_fruitMap[c2.x][c2.y]&&isConnectedDirectly(v1,c2)&&isConnectedDirectly(v2,c2)){
		path->push_back(v1);
		path->push_back(c2);
		path->push_back(v2);
		return true;
	}
	return false;
}

bool FruitMap::isConnectedByTwoCross(Vector2 v1,Vector2 v2,std::list<Vector2>* path){
	for(int i=v1.x-1;i>=0;i--){
		if(_fruitMap[i][v1.y]){
			break;
		}

		if(isConnectedByOneCross(Vector2(i,v1.y),v2,path)){
			path->push_front(v1);
			return true;
		}
	}
	for(int i=v1.x+1;i<ysize;i++){
		if(_fruitMap[i][v1.y]){
			break;
		}
		if(isConnectedByOneCross(Vector2(i,v1.y),v2,path)){
			path->push_front(v1);
			return true;
		}
	}
	for(int j=v1.y-1;j>=0;j--){
		if(_fruitMap[v1.x][j]){
			break;
		}
		if(isConnectedByOneCross(Vector2(v1.x,j),v2,path)){
			path->push_front(v1);
			return true;
		}
	}
	for(int j=v1.y+1;j<xsize;j++){
		if(_fruitMap[v1.x][j]){
			break;
		}
		if(isConnectedByOneCross(Vector2(v1.x,j),v2,path)){
			path->push_front(v1);
			return true;
		}
	}
	return false;
}
bool FruitMap::match(const int& i1,const int& j1,const int& i2,const int& j2,std::list<Vector2>* path){
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
		path->push_back(v1);
		path->push_back(v2);
		return true;
	}
	if(isConnectedByOneCross(v1,v2,path)){
		return true;
	}
	if(isConnectedByTwoCross(v1,v2,path)){
		return true;
	}
	return false;
}

FruitMap::~FruitMap(){
	clearMap();
	_node->release();
	_node=0;

	if(_matchSound){
		_matchSound->release();
		_matchSound=0;
	}

	if(_data){
		_data->release();
		_data=0;
	}

}