#include "TCObject.h"

NS_TC_BEGIN
	
const std::string& TCObject::name(){
	return _name;
}
void TCObject::setName(const std::string& name){
	_name=name;
}
NS_TC_END