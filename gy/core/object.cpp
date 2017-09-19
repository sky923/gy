#include "object.h"
#include "application.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>
#include <list>

// 생성
// 1. create
// 1. operator new
// 2. initialize 리스트에 등록
// 3. flush initialize 호출 시 생성된 순서대로 initialize멤버 호출
// 4. bIsInitialize가 true이면 해당 GObject를 실행(execute)한다

// 해제
// 1. destroy
// 1. operator delete
// 2. finalize 리스트에 등록 (단, immediatelyDestroy함수 호출 시에는 등록하지 않고, 호출 시점 바로 제거하도록 한다)
// 3. flush finalize 호출 시 생성된 순서대로 finalize멤버 호출
// 4. bIsFinialize가 true일 경우 메모리에서 해제(::delete)

class CObjectIdGenerator
{
	friend class GObject;
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
	friend class GObject;

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
	std::unordered_map<identity_t, GObject*> objectMapById;
	std::unordered_map<identity_t, GObject*> dynamicAllocatedObjectMapById;
	std::unordered_map<identity_t, identity_t> dynamicAllocatedObjectMapByPointer;
	std::unordered_map<identity_t, GObject*> staticAllocatedObjectMapById;
	std::vector<GObject*> objectVector;
	
	std::list<GObject*> objectForInitializingList;
	std::list<GObject*> objectForFinalizingList;
};

GObject::GObject()
: Id(GY_INVALID)
, bIsDynamicAllocated(false)
, bIsReservedDestruction(false)
, bIsInitialized(false)
, bIsFinalized(false)
, bIsEnabledTick(false)
, bIsActivated(false)
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	auto convId = (identity_t)(static_cast<GObject*>(this));
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
	
	refContainer.objectForInitializingList.push_back(this);
}

GObject::~GObject()
{
	if (bIsInitialized && !bIsFinalized)
	{
		finalize();
		destroy();
	}
}
void GObject::destroy()
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
void GObject::immediatelyDestroy()
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	if (bIsDynamicAllocated)
	{
		
		refContainer.dynamicAllocatedObjectMapById.erase(Id);
		refContainer.dynamicAllocatedObjectMapByPointer.erase((identity_t)(static_cast<GObject*>(this)));
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
void *GObject::operator new(size_t size)
{
	auto newObject = (GObject*)(::operator new(size));
	
	identity_t newId = CObjectIdGenerator::get().makeNewId();
	
	auto& refContainer = CObjectReferenceContainer::get();
	refContainer.dynamicAllocatedObjectMapById[newId] = newObject;
	refContainer.dynamicAllocatedObjectMapByPointer[(identity_t)(newObject)] = newId;
	refContainer.objectVector.push_back(newObject);
	refContainer.objectMapById.insert({newId, newObject});
	
	return newObject;
}

void GObject::operator delete(void* ptr)
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	auto objectForDeleting = static_cast<GObject*>(ptr);
	if (objectForDeleting)
	{
		objectForDeleting->bIsReservedDestruction = true;
		refContainer.objectForFinalizingList.push_back(objectForDeleting);
	}
	else
	{
		::operator delete(ptr);
	}
}

GObject* GObject::findObject(const std::function<bool(GObject*)>& finder)
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	for (auto& curObject : refContainer.objectVector)
	{
		if (finder && curObject && finder(curObject))
			return curObject;
	}
	
	return nullptr;
}

GObject* GObject::getObject(identity_t inId)
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	auto itr = refContainer.objectMapById.find(inId);
	if (itr == refContainer.objectMapById.end())
		return nullptr;
	
	return (*itr).second;
}

identity_t GObject::getId() const
{
	return Id;
}
str8_t GObject::getIdAsString() const
{
	return IdAsString;
}
str8_t GObject::getClassName() const
{
	return ClassName;
}
bool GObject::IsDynamicAllocated() const
{
	return bIsDynamicAllocated;
}
bool GObject::IsReservedDestruction() const
{
	return bIsReservedDestruction;
}
bool GObject::IsEnabledTick() const
{
	return bIsEnabledTick;
}
void GObject::SetEnabledTick(bool bEnabledTick)
{
	bIsEnabledTick = bEnabledTick;
}
bool GObject::IsActivated() const
{
	return bIsActivated;
}


result_t GObject::initialize()
{
	result_t result = GY_FAIL;

	result = onPreInitialize();
	if (result != GY_SUCCESS)
	{
		return result;
	}

	result = onInitialize();
	if (result != GY_SUCCESS)
	{
		return result;
	}

	result = onPostInitialize();
	if (result != GY_SUCCESS)
	{
		return result;
	}

	return result;
}

void GObject::processInitialization()
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	for (auto& curObject : refContainer.objectForInitializingList)
	{
		curObject->initialize();
	}
	
	refContainer.objectForFinalizingList.clear();
}

result_t GObject::onPreInitialize() { return GY_SUCCESS; }
result_t GObject::onInitialize() { return GY_SUCCESS; }
result_t GObject::onPostInitialize() { return GY_SUCCESS; }

result_t GObject::finalize()
{
	result_t result = GY_FAIL;

	result = onPreFinalize();
	if (result != GY_SUCCESS)
	{
		return result;
	}

	result = onFinalize();
	if (result != GY_SUCCESS)
	{
		return result;
	}

	result = onPostFinalize();
	if (result != GY_SUCCESS)
	{
		return result;
	}

	return result;
}

void GObject::processFinalization()
{
	auto& refContainer = CObjectReferenceContainer::get();
	
	for (auto& curObject : refContainer.objectForFinalizingList)
	{
		curObject->finalize();
	}
	
	refContainer.objectForFinalizingList.clear();
}

result_t GObject::onPreFinalize() { return GY_SUCCESS; }
result_t GObject::onFinalize() { return GY_SUCCESS; }
result_t GObject::onPostFinalize() { return GY_SUCCESS; }
