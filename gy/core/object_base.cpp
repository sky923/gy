#include "object_base.h"


struct SIdCounter
{
	
};

GObjectBase::GObjectBase()
{
}

GObjectBase::~GObjectBase()
{
}

void *GObjectBase::operator new(size_t size)
{
	auto newObject = (GObjectBase*)(::operator new(size));
	return newObject;
}

void GObjectBase::operator delete(void* ptr)
{
}

void GObjectBase::addTickFunction(const std::function<void(f_t)>& tickFunction)
{
	tickFunctions.push_back(tickFunction);
}

void GObjectBase::removeTickFunction(size_t index)
{
	if (index >= tickFunctions.size() || index <= -1)
		return;
	
	auto itr = tickFunctions.begin() + index;
	tickFunctions.erase(itr);
}

void GObjectBase::_tick(f_t deltaSeconds)
{
	for (auto& curTickFunction : tickFunctions)
	{
		if (curTickFunction)
		{
			curTickFunction(deltaSeconds);
		}
	}
}

identity_t GObjectBase::getId() const
{
	return Context.Id;
}
str8_t GObjectBase::getIdAsString() const
{
	return Context.IdAsString;
}
str8_t GObjectBase::getClassName() const
{
	return Context.ClassName;
}
bool GObjectBase::IsDynamicAllocated() const
{
	return Context.bIsDynamicAllocated;
}
bool GObjectBase::IsReservedDestruction() const
{
	return Context.bIsReservedDestruction;
}
