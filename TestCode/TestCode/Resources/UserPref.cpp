
#include "UserPref.h"
#include "io/DirectoryUtil.h"
#include <fstream>
#ifdef ANDROID
#include "TCAndroidSystemInfo.h"
#endif
NS_TC_BEGIN

UserPref::UserPref(){
	_dirPath="";
#ifdef _WINDOWS
	if(!DirectoryUtil::exist("Cache/")){
		DirectoryUtil::createDirectory("Cache");
	}
	_dirPath="Cache/";
#endif

#ifdef ANDROID
	_dirPath=AndroidSystemInfo::cacheDir();
#endif

	std::ifstream fs;
	fs.open((_dirPath+"user_pref.json").c_str());
	Json::Reader reader;
	if(!reader.parse(fs,_pref,false)){
		DebugLog("load user pref failed!!");
	}
}
void UserPref::setBoolean(const std::string& key,bool value){
	_pref[key]=value;
}

void UserPref::setInt(const std::string& key,int value){
	_pref[key]=value;
}

void UserPref::setFloat(const std::string& key,float value){
	_pref[key]=value;
}

bool UserPref::getBoolean(const std::string& key,bool defaultValue/* =false */){
	Json::Value ret=_pref.get(key,defaultValue);
	return ret.asBool();
}
int UserPref::getInt(const std::string& key,int defaultValue/* =0 */){
	return _pref.get(key,defaultValue).asInt();
}
float UserPref::getFloat(const std::string& key,float defalutValue/* =0 */){
	return (float)_pref.get(key,(double)defalutValue).asDouble();
}

void UserPref::save(){
	Json::FastWriter writer;
	std::string jsonFile=writer.write(_pref);
	std::ofstream file;
	file.open((_dirPath+"user_pref.json").c_str());
	file<<jsonFile;
	file.close();
}

UserPref* UserPref::instance(){
	static UserPref ret;
	return &ret;
}
NS_TC_END