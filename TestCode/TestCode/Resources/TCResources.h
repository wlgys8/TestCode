#ifndef __TC_RESOURCES_H__
#define __TC_RESOURCES_H__
#include <vector>
#include <string>
#include <map>
#include "TCCommon.h"
#include "TCSingleton.h"
#include "TCTexture.h"
#include "TCBitmap.h"

#include "TCTexturePackerUtil.h"


using namespace std;
NS_TC_BEGIN

	enum ResourcesType{
		RES_TYPE_UNKNOWN=0,
		RES_TYPE_TEXTURE=1,
		RES_TYPE_BITMAP=2,
};
template<class T>
struct TYPE_OF{
	enum{
		type=RES_TYPE_UNKNOWN,
	};
};
#define DECLARE_RESOURCES_TYPE(CLASSNAME,TYPEVALUE) \
	template<> \
struct TYPE_OF<CLASSNAME>{\
	enum{\
	type=TYPEVALUE,\
};\
};
DECLARE_RESOURCES_TYPE(TCTexture,RES_TYPE_TEXTURE)
DECLARE_RESOURCES_TYPE(TCBitmap,RES_TYPE_BITMAP)

#undef DECLARE_RESOURCES_TYPE

class AudioBuffer;

class TCResources:public TCSingleton<TCResources>{
	typedef map<string,TCTexture*> TextureMap;
	friend class TCSingleton<TCResources>; 
private:
	TextureMap _textureMap;
	TCResources();
	~TCResources();
	static std::string _rootPath;
public:
	//object
	TCTexture* findTexture(const string& texturePath) ;

	static inline void setRootPath(const std::string& rootPath){
		_rootPath=rootPath;
	}
	//static
	static TCTexture* loadTexture(const std::string &path,BitmapFormat format);
	static inline TCTexture* loadTexture(const std::string &path){
		return loadTexture(path,RGBA_8888);
	}

	static void loadTexturePacker(const std::string path,TexturePacker& outputPacker);

	static void loadTextureRegions(const std::string& texPath,const std::string jsonFilePath,BitmapFormat format);

	static AudioBuffer* loadAudioInAssets(const std::string& srcPath);

	static unsigned char* loadDataStreamInAssets(const std::string& srcPath,unsigned long* size);

private:

};




NS_TC_END
#endif