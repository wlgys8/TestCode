#include "Font/TCCustomFont.h"
#include "TCTextureRegionManager.h"
#include "TextureRegion.h"
NS_TC_BEGIN

CustomFont::CustomFont(){

}

void CustomFont::registerPair(const std::string& key,const std::string& imageName ){
	TextureRegion* region=TextureRegionManager::instance()->get(imageName);
	if(!region){
		return;
	}
	TextureRegion* ret=indexOf(key);
	if(ret){
		return;
	}
	region->retain();
	_fontMap.insert(FontMap::value_type(key,region));
}

TextureRegion* CustomFont::indexOf(const std::string key){
	FontMap::iterator it=_fontMap.find(key);
	if(it!=_fontMap.end()){
		return it->second;
	}
	return 0;
}

void CustomFont::clear(){
	FontMap::iterator it;
	for(it=_fontMap.begin();it!=_fontMap.end();it++){
		it->second->release();
	}
	_fontMap.clear();
}

CustomFont::~CustomFont(){
	clear();
}

CustomFont* CustomFont::alloc(){
	CustomFont*ret=new CustomFont();
	ret->autoRelease();
	return ret;
}


NS_TC_END