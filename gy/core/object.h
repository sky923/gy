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
	result_t initialize();
protected:
	virtual result_t onPreInitialize();
	virtual result_t onInitialize();
	virtual result_t onPostInitialize();
private:
	result_t finalize();
protected:
	virtual result_t onPreFinalize();
	virtual result_t onFinalize();
	virtual result_t onPostFinalize();
};

#endif
