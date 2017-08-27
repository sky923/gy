#ifndef __gy_core_object_h__
#define __gy_core_object_h__

#include "object_base.h"

class GObject : public GObjectBase
{
public:
	struct SContext : public GObjectBase::SContext
	{
		bool bIsInitialized;
		bool bIsFinalized;
	};
private:
	SContext Context;
};

#endif
