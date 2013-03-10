#ifndef __TC_TEXTUREPACKERUTIL_H__
#define __TC_TEXTUREPACKERUTIL_H__
#include <map>
#include <string>
#include "TCVector2f.h"
#include "TCFileUtils.h"
#include "json/json.h"
#include "Rect.h"
NS_TC_BEGIN
class TPMeta{
public:
	std::string app;
	std::string version;
	std::string image;
	std::string format;
	std::string scale;
	Vector2f size;
};
class TPFrame{
public:
	Rect frame;
	bool rotated;
	bool trimmed;
	Rect spriteSourceSize;
	Vector2f sourceSize;
};
class TexturePacker{
public:
	std::map<std::string,TPFrame> frames;
	TPMeta meta;
};



class TCTexturePackerUtil{

public:
	static bool loadJsonFile(std::string path,TexturePacker& packerOutput);
};
NS_TC_END

#endif