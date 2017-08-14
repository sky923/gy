#ifndef __gy_core_object_h__
#define __gy_core_object_h__

#include "../pil/type.h"
#include <memory>

class GObjectBase
{
protected:
	GObjectBase();
public:
	virtual ~GObjectBase();
};

#endif