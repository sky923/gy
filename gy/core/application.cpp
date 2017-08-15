#include "application.h"

namespace gy
{
	std::shared_ptr<GApplication> appInstance;
}

result_t startApplication(std::shared_ptr<GApplication>&& newApplicaion)
{
	gy::appInstance = newApplicaion;

	if (gy::appInstance)
	{
		return gy::appInstance->execute();
	}

	return GY_FAIL;
}

GApplication::GApplication()
{
}

GApplication::~GApplication()
{
}

std::shared_ptr<GApplication> GApplication::get()
{
	return gy::appInstance;
}

result_t GApplication::initialize()
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

result_t GApplication::execute()
{
	result_t result = GY_FAIL;

	result = initialize();
	if (result != GY_SUCCESS)
	{
		return result;
	}
	
	result = onExecute();
	if (result != GY_SUCCESS)
	{
		return result;
	}
	
	result = finalize();
	if (result != GY_SUCCESS)
	{
		return result;
	}
	
	return result;
}

result_t GApplication::finalize()
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

