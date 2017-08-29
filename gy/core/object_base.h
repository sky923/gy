#ifndef __gy_core_object_base_h__
#define __gy_core_object_base_h__

#include "../pil/type.h"
#include "../pil/string.h"
#include <functional>

class GObjectBase
{
private:
	identity_t Id;
	str8_t IdAsString;
	str8_t ClassName;
	bool bIsDynamicAllocated;
	bool bIsReservedDestruction;
protected:
	GObjectBase();
public:
	virtual ~GObjectBase();
	void destroy();
	void immediatelyDestroy();
public:
	void *operator new (size_t size);
	void operator delete (void* ptr);
protected:
	GObjectBase* findObjectBase(const std::function<bool(GObjectBase*)>& finder);
	GObjectBase* getObjectBase(identity_t Id);
public:
	identity_t getId() const;
	str8_t getIdAsString() const;
	str8_t getClassName() const;
	bool IsDynamicAllocated() const;
	bool IsReservedDestruction() const;
	bool IsEnabledTick() const;
};

#endif
