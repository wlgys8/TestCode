#ifndef __TC_TEXTUREREGIONMANAGER_H__
#define __TC_TEXTUREREGIONMANAGER_H__
#include "TCSingleton.h"
#include "TextureRegion.h"
#include <map>
NS_TC_BEGIN
	class TextureRegion;
class TextureRegionManager:public TCSingleton<TextureRegionManager>{
friend class TCSingleton<TextureRegionManager>;	
typedef  std::map<const std::string,TextureRegion*> Map;
typedef  Map::iterator Iterator;
private:
	Map _regionMap;
	~TextureRegionManager();
	void add(TextureRegion* region);
public:
	TextureRegion* alloc(const std::string& name,TCTexture* tex,float left,float bottom,float width,float height);
	
	TextureRegion* get(const std::string& key);

};
NS_TC_END
#endif