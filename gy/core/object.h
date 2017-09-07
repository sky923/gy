#ifndef __gy_core_object_h__
#define __gy_core_object_h__

#include "../pil/type.h"
#include "../pil/string.h"
#include <functional>

class GObject
{
protected:
	identity_t Id;
	str8_t IdAsString;
	str8_t ClassName;
	bool bIsDynamicAllocated;
	bool bIsReservedDestruction;
	bool bIsInitialized;
	bool bIsFinalized;
	bool bIsEnabledTick;
	bool bIsActivated;
protected:
	GObject();
public:
	virtual ~GObject();
	void destroy();
	void immediatelyDestroy();
public:
	void *operator new (size_t size);
	void operator delete (void* ptr);
protected:
	static GObject* findObject(const std::function<bool(GObject*)>& finder);
	static GObject* getObject(identity_t Id);
public:
	identity_t getId() const;
	str8_t getIdAsString() const;
	str8_t getClassName() const;
	bool IsDynamicAllocated() const;
	bool IsReservedDestruction() const;
	bool IsEnabledTick() const;
	void SetEnabledTick(bool bEnabledTick);
	bool IsActivated() const;
private:
	result_t initialize();
protected:
	static void processInitialization();
	virtual result_t onPreInitialize();
	virtual result_t onInitialize();
	virtual result_t onPostInitialize();
private:
	result_t finalize();
protected:
	static void processFinalization();
	virtual result_t onPreFinalize();
	virtual result_t onFinalize();
	virtual result_t onPostFinalize();
};

#endif
