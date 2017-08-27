#ifndef __gy_core_object_base_h__
#define __gy_core_object_base_h__

#include "../pil/type.h"
#include "../pil/string.h"
#include <map>
#include <vector>
#include <memory>

class GObjectBase
{
public:
	struct SContext
	{
		identity_t Id;
		str8_t IdAsString;
		str8_t ClassName;
		bool bIsDynamicAllocated;
		bool bIsReservedDestruction;
	};
private:
	SContext Context;
protected:
	GObjectBase();
public:
	virtual ~GObjectBase();
public:
	void *operator new (size_t size);
	void operator delete (void* ptr);
private:
	std::vector<std::function<void(f_t)>> tickFunctions;
protected:
	void addTickFunction(const std::function<void(f_t)>& tickFunction);
	void removeTickFunction(size_t index);
private:
	void _tick(f_t deltaSeconds);
public:
	identity_t getId() const;
	str8_t getIdAsString() const;
	str8_t getClassName() const;
	bool IsDynamicAllocated() const;
	bool IsReservedDestruction() const;
};

#endif
