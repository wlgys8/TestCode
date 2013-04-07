#ifndef __TC_OBJECT_H__
#define __TC_OBJECT_H__
#include <string>
#include "TCCommon.h"

NS_TC_BEGIN

class TCObject{

private:
	std::string _name;
protected:
	TCObject();
	~TCObject();
public:
	virtual const std::string& name();
	virtual void setName(const std::string& name);

private:
	static int _count;
public:
	static int count();
};

NS_TC_END

#endif