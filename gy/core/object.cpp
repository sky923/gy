#include "object.h"

GObject::GObject()
: bIsInitialized(false)
, bIsFinalized(false)
, bIsEnabledTick(false)
, bIsActivated(false)
{
}

GObject::~GObject()
{
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

result_t GObject::onPreFinalize() { return GY_SUCCESS; }
result_t GObject::onFinalize() { return GY_SUCCESS; }
result_t GObject::onPostFinalize() { return GY_SUCCESS; }