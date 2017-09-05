#include "object.h"
#include <list>

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
	std::list<GObject*> objectForInitializingVector;
	std::list<GObject*> objectForFinalizingVector;
};

GObject::GObject()
: bIsInitialized(false)
, bIsFinalized(false)
, bIsEnabledTick(false)
, bIsActivated(false)
{
	auto& refContainer = CObjectReferenceContainer::get();
	refContainer.objectForInitializingVector.push_back(this);
}

GObject::~GObject()
{
	if (bIsInitialized && !bIsFinalized)
	{
		finalize();
		destroy();
	}
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
	findObjectBase([](GObjectBase* ObjectBase)
	{
		return false;
	});
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
}

result_t GObject::onPreFinalize() { return GY_SUCCESS; }
result_t GObject::onFinalize() { return GY_SUCCESS; }
result_t GObject::onPostFinalize() { return GY_SUCCESS; }