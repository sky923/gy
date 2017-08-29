#include "object_base.h"
#include "application.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>

class CObjectIdGenerator
{
	friend class GObjectBase;
public:
//	const size_t maximumIdOfObject = 16777216; // 1 << 24
private:
	CObjectIdGenerator() : nextId(0) {}
public:
	virtual ~CObjectIdGenerator() {}
	static CObjectIdGenerator& get()
	{
		static CObjectIdGenerator instance;
		return instance;
	}
protected:
	identity_t nextId;
	identity_t makeNewId()
	{
		if (nextId == GY_INVALID)
		{
			assert(false && "Couldn't make a new ID anymore.");
			return GY_INVALID;
		}
		
		identity_t newId = nextId;
		++nextId;
		return newId;
	}
};

class CObjectReferenceContainer
{
	friend class GObjectBase;
	
private:
	CObjectReferenceContainer() {}
public:
	virtual ~CObjectReferenceContainer() {}
	static CObjectReferenceContainer& get()
	{
		static CObjectReferenceContainer instance;
		return instance;
	}
protected:
	std::unordered_map<identity_t, GObjectBase*> objectMapById;
	std::unordered_map<identity_t, GObjectBase*> dynamicAllocatedObjectMapById;
	std::unordered_map<identity_t, identity_t> dynamicAllocatedObjectMapByPointer;
	std::unordered_map<identity_t, GObjectBase*> staticAllocatedObjectMapById;
	std::vector<GObjectBase*> objectVector;
};

GObjectBase::GObjectBase()
: Id(GY_INVALID)
, bIsDynamicAllocated(false)
, bIsReservedDestruction(false)
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	auto convId = (identity_t)(static_cast<GObjectBase*>(this));
	auto itr = refContainer.dynamicAllocatedObjectMapByPointer.find(convId);
	if (itr != refContainer.dynamicAllocatedObjectMapByPointer.end())
	{
		bIsDynamicAllocated = true;
		identity_t foundId = (*itr).second;
		Id = foundId;
	}
	else
	{
		Id = CObjectIdGenerator::get().makeNewId();
		refContainer.staticAllocatedObjectMapById[Id] = this;
		refContainer.objectVector.push_back(this);
		refContainer.objectMapById.insert({Id, this});
	}
}

GObjectBase::~GObjectBase()
{
}
void GObjectBase::destroy()
{
	if (bIsDynamicAllocated)
	{
		delete(this);
	}
	else
	{
		bIsReservedDestruction = true;
	}
}
void GObjectBase::immediatelyDestroy()
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	if (bIsDynamicAllocated)
	{
		
		refContainer.dynamicAllocatedObjectMapById.erase(Id);
		refContainer.dynamicAllocatedObjectMapByPointer.erase((identity_t)(static_cast<GObjectBase*>(this)));
	}
	
	auto& objectVector = refContainer.objectVector;
	auto itr = std::find(objectVector.begin(), objectVector.end(), this);
	if (itr != objectVector.end())
	{
		objectVector.erase(itr);
	}
	
	refContainer.objectMapById.erase(Id);
	refContainer.staticAllocatedObjectMapById.erase(Id);
	
	bIsReservedDestruction = true;
	
	if (bIsDynamicAllocated)
	{
		::delete(this);
	}
}
void *GObjectBase::operator new(size_t size)
{
	auto newObject = (GObjectBase*)(::operator new(size));
	
	identity_t newId = CObjectIdGenerator::get().makeNewId();
	
	auto& refContainer = CObjectReferenceContainer::get();
	refContainer.dynamicAllocatedObjectMapById[newId] = newObject;
	refContainer.dynamicAllocatedObjectMapByPointer[(identity_t)(newObject)] = newId;
	refContainer.objectVector.push_back(newObject);
	refContainer.objectMapById.insert({newId, newObject});
	
	return newObject;
}

void GObjectBase::operator delete(void* ptr)
{
	auto objectForDeleting = static_cast<GObjectBase*>(ptr);
	if (objectForDeleting)
	{
		objectForDeleting->bIsReservedDestruction = true;
	}
	else
	{
		::operator delete(ptr);
	}
}

GObjectBase* GObjectBase::findObjectBase(const std::function<bool(GObjectBase*)>& finder)
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	for (auto& curObject : refContainer.objectVector)
	{
		if (finder && curObject && finder(curObject))
			return curObject;
	}
	
	return nullptr;
}

GObjectBase* GObjectBase::getObjectBase(identity_t inId)
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	auto itr = refContainer.objectMapById.find(inId);
	if (itr == refContainer.objectMapById.end())
		return nullptr;
	
	return (*itr).second;
}

identity_t GObjectBase::getId() const
{
	return Id;
}
str8_t GObjectBase::getIdAsString() const
{
	return IdAsString;
}
str8_t GObjectBase::getClassName() const
{
	return ClassName;
}
bool GObjectBase::IsDynamicAllocated() const
{
	return bIsDynamicAllocated;
}
bool GObjectBase::IsReservedDestruction() const
{
	return bIsReservedDestruction;
}

