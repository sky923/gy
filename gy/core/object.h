#ifndef __gy_core_object_h__
#define __gy_core_object_h__

#include "object_base.h"

class GObject : public GObjectBase
{
protected:
	bool bIsInitialized;
	bool bIsFinalized;
	bool bIsEnabledTick;
	bool bIsActivated;
protected:
	GObject();
public:
	virtual ~GObject();
public:
	bool IsEnabledTick() const;
	void SetEnabledTick(bool bEnabledTick);
	bool IsActivated() const;
private:
	void initialize();
	void finalize();

};

#endif
