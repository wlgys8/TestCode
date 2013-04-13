#ifndef __TC_USER_PREF_H__
#define __TC_USER_PREF_H__
#include "TCCommon.h"
#include <string>
#include "json/json.h"
#include "TCObject.h"

NS_TC_BEGIN

//Use JSON to serialize pref
//File path:Cache/user_pref.json
class UserPref:public TCObject{

private:
	Json::Value _pref;
	std::string _dirPath;
	UserPref();
public:

	void setBoolean(const std::string& key,bool value);
	void setInt(const std::string& key,int value);
	void setFloat(const std::string& key,float value);

	bool getBoolean(const std::string& key,bool defaultValue=false);
	int getInt(const std::string& key,int defaultValue=0);
	float getFloat(const std::string& key,float defalutValue=0);

	void save();

	static UserPref* instance();

};

NS_TC_END

#endif