#ifndef __TC_CUSTOM_FONT_H__
#define __TC_CUSTOM_FONT_H__
#include "AutoReleaseObject.h"
#include <string>
#include <map>
NS_TC_BEGIN
class TextureRegion;
class CustomFont:public AutoReleaseObject{
	typedef std::map<std::string,TextureRegion*> FontMap;

private:
	FontMap _fontMap;
private:
	CustomFont();
	~CustomFont();
public:

	void registerPair(const std::string& key,const std::string& imageName );
	
	TextureRegion* indexOf(const std::string key);

	void clear();

	static CustomFont* alloc();

};

NS_TC_END
#endif