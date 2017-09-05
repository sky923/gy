#include "application.h"
#include <cassert>

namespace gy
{
	std::shared_ptr<GApplication> appInstance;
}

result_t startApplication(std::shared_ptr<GApplication>&& newApplicaion)
{
	gy::appInstance = newApplicaion;

	if (gy::appInstance && gy::appInstance->IsEnabledTick())
	{
		return gy::appInstance->execute();
	}

	return GY_FAIL;
}

GApplication::GApplication()
{
	SetEnabledTick(true);
	
	assert(nullptr == gy::appInstance && "Already exist an GApplication instance.");
}

GApplication::~GApplication()
{
}

std::shared_ptr<GApplication> GApplication::get()
{
	return gy::appInstance;
}
//
//result_t GApplication::onPreInitialize() { return GY_SUCCESS; }
//result_t GApplication::onInitialize() { return GY_SUCCESS; }
//result_t GApplication::onPostInitialize() { return GY_SUCCESS; }

result_t GApplication::execute()
{
	result_t result = GY_FAIL;

	result = onExecute();
	if (result != GY_SUCCESS)
	{
		return result;
	}

	return result;
}

//result_t GApplication::onPreFinalize() { return GY_SUCCESS; }
//result_t GApplication::onFinalize() { return GY_SUCCESS; }
//result_t GApplication::onPostFinalize() { return GY_SUCCESS; }