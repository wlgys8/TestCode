#include "TCResources.h"
#include "TCTextureRegionManager.h"
#include "TextureRegion.h"
NS_TC_BEGIN
TCResources::TCResources(){
	_textureMap=TextureMap();
}
TCResources::~TCResources(){
	TextureMap::iterator it;
	for(it=_textureMap.begin();it!=_textureMap.end();it++){
		it->second->release();
	}
	_textureMap.clear();
}

TCTexture* TCResources::findTexture(const string& texturePath) {
	TextureMap::iterator it=_textureMap.find(texturePath);
	if(it==_textureMap.end()){
		return 0;
	}
	return it->second;
	
}
TCTexture* TCResources::loadTexture(const std::string &path,BitmapFormat format){
	TCTexture* ret=instance()-> findTexture(path);
	if(ret){
		DebugLog("texture has existed,path=%s",path.c_str());
		return ret;
	}
	TCBitmap* bitmap=TCBitmap::decodeBitmap("assets/"+path,format);
	if(!bitmap){
		return NULL;
	}
	ret=TCTexture::createTextureFromBitmap(bitmap);
	if(!ret){
		return NULL;
	}
	instance()->_textureMap[path]=ret;
	ret->retain();
	return ret;
}

void TCResources::loadTexturePacker(const std::string path, TexturePacker& outputPacker){
	TCTexturePackerUtil::loadJsonFile("assets/"+path,outputPacker);
	DebugLog(outputPacker.meta.image.c_str());
}

void TCResources::loadTextureRegions(const std::string& texPath,const std::string jsonFilePath,BitmapFormat format){
	TCTexture* tex=loadTexture(texPath,format);
	TexturePacker pk;
	loadTexturePacker(jsonFilePath,pk);
	std::map<std::string,TPFrame>::iterator it;
	float w=pk.meta.size.x;
	float h=pk.meta.size.y;
	for(it=pk.frames.begin();it!=pk.frames.end();it++){
		float left=it->second.frame.xMin()/w;
		float top=it->second.frame.yMin()/h;
		float width=it->second.frame.width()/w;
		float height=it->second.frame.height()/h;
		TextureRegionManager::instance()->alloc(it->first,tex,left,1-top-height,width,height);
	}

}

NS_TC_END