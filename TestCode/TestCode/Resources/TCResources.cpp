#include "TCResources.h"
#include "TCTextureRegionManager.h"
#include "TextureRegion.h"
#include "Audio/TCAudioBuffer.h"
#include "Audio/AudioManager.h"

#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
#include "Android/TCAndroidSystemInfo.h"
#endif
NS_TC_BEGIN

std::string TCResources::_rootPath="assets/";

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
	TCBitmap* bitmap=TCBitmap::decodeBitmap(_rootPath+path,format);
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
	TCTexturePackerUtil::loadJsonFile(_rootPath+path,outputPacker);
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

AudioBuffer* TCResources::loadAudioInAssets(const std::string& srcPath){
	AudioBuffer* ret=AudioManager::instance()->find(srcPath);
	if(ret){
		return ret;
	}
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

	DataStream* fileStream=TCFileUtils::getFileDataFromZip(AndroidSystemInfo::sourceDir().c_str(),(_rootPath+srcPath).c_str());
	if(!fileStream){
		DebugLog("load %s failed.",srcPath.c_str());
		return 0;
	}
	return AudioManager::instance()->load(srcPath,fileStream);
#else
	DataStream* fileStream=TCFileUtils::getFileData((_rootPath+srcPath).c_str());
	if(!fileStream){
		DebugLog("load %s failed.",srcPath.c_str());
		return 0;
	}
	return AudioManager::instance()->load(srcPath,fileStream);	
#endif
	
}

DataStream* TCResources::loadDataStreamInAssets(const std::string& srcPath){
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
	return TCFileUtils::getFileDataFromZip(AndroidSystemInfo::sourceDir().c_str(),(_rootPath+srcPath).c_str());
#else
	return TCFileUtils::getFileData((_rootPath+srcPath).c_str());

#endif
}

NS_TC_END