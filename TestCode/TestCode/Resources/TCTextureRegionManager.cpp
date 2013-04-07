#include "TCTextureRegionManager.h"
NS_TC_BEGIN

TextureRegionManager::~TextureRegionManager(){
	Iterator it;
	for(it=_regionMap.begin();it!=_regionMap.end();it++){
		it->second->release();
	}
	_regionMap.clear();
}
TextureRegion* TextureRegionManager::alloc(const std::string& name,TCTexture* tex,float left,float bottom,float width,float height){
	TextureRegion* ret=new TextureRegion(name,tex,left,bottom,width,height);
	ret->autoRelease();
	add(ret);
	return ret;
}
void TextureRegionManager::add(TextureRegion* region){
	Iterator it= _regionMap.find(region->name());
	assert( it==_regionMap.end());
	region->retain();
	 _regionMap[region->name()]=region;
}

TextureRegion* TextureRegionManager::get(const std::string& key){
	Iterator it= _regionMap.find(key);
	if(it!=_regionMap.end()){
		return it->second;
	}
	DebugLog("find %s failed.",key.c_str());
	return NULL;
}
NS_TC_END