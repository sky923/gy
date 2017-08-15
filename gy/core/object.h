#ifndef __gy_core_object_h__
#define __gy_core_object_h__

#include "../pil/type.h"
#include <map>
#include <vector>
#include <memory>

class GObjectBase
{
private:
	//std::map<str8_t, std::shared_ptr<GObjectBase>> members;
	//@todo:
protected:
	GObjectBase();
public:
	virtual ~GObjectBase();
};

#endif
