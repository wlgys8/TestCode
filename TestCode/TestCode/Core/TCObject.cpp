#include "TCObject.h"
#include "Debug/TCMemoryStatistics.h"
NS_TC_BEGIN
	

int TCObject::_count=0;

TCObject::TCObject(){
	_count++;
}
TCObject::~TCObject(){
	_count--;
}
const std::string& TCObject::name(){
	return _name;
}
void TCObject::setName(const std::string& name){
	_name=name;
}

int TCObject::count(){
	return _count;
}
NS_TC_END