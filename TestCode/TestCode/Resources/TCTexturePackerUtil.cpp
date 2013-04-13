#include "TCTexturePackerUtil.h"
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
#include "TCAndroidSystemInfo.h"
#endif
NS_TC_BEGIN
bool TCTexturePackerUtil::loadJsonFile(std::string path,TexturePacker& packerOutput){
	DataStream* dataStream= 0;
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
	dataStream= TCFileUtils::getFileDataFromZip(AndroidSystemInfo::sourceDir().c_str(), path.c_str());
#else
	dataStream= TCFileUtils::getFileData(path.c_str());
#endif
	

	bool ret=false;
	if(dataStream){
		do{
			Json::Reader reader;
			Json::Value root;
			if(!reader.parse((char*)dataStream->data(),root,false)){
				break;
			}
			TPMeta& meta=packerOutput.meta;
			//read meta//
			Json::Value	metaValue=root["meta"];
			meta.app= metaValue["app"].asString();
			meta.version=metaValue["version"].asString();
			meta.image=metaValue["image"].asString();
			meta.format=metaValue["format"].asString();
			meta.size=Vector2f((float)metaValue["size"]["w"].asInt(),(float)metaValue["size"]["h"].asInt());
			meta.scale=metaValue["scale"].asString();
			//read frames//
			std::map<std::string,TPFrame>& frames=packerOutput.frames;
			Json::Value jsonFrames=root["frames"];
			Json::Value::Members keys=jsonFrames.getMemberNames();
			for(Json::Value::Members::iterator it=keys.begin();it!=keys.end();it++){
				TPFrame frame=TPFrame();
				Json::Value jsonFrame=jsonFrames[*it];
				frame.rotated=jsonFrame["rotated"].asBool();
				frame.trimmed=jsonFrame["trimmed"].asBool();
				frame.frame=Rect((float)jsonFrame["frame"]["x"].asInt(),
					(float)jsonFrame["frame"]["y"].asInt(),
					(float)jsonFrame["frame"]["w"].asInt(),
					(float)jsonFrame["frame"]["h"].asInt());
				frames[*it]=frame;
			}
			ret=true;
		}while(0);
		dataStream->releaseData();//release right now
	}
	
	return ret;
}
NS_TC_END