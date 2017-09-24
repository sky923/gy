#include "application.h"
#include <cassert>
#include <thread>
#include <iostream>

namespace gy
{
	std::shared_ptr<GApplication> appInstance;
}

result_t startApplication(std::shared_ptr<GApplication>&& newApplicaion)
{
	gy::appInstance = newApplicaion;

	if (gy::appInstance)
	{
		gy::appInstance->mainThreadId = std::this_thread::get_id();
		
		GApplication::processInitialization();
		
		return gy::appInstance->execute();
	}

	return GY_FAIL;
}

GApplication::GApplication()
: bHasStartedEventDispatch(false)
, bTryToExit(false)
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

result_t GApplication::execute()
{
	std::cout << "mainThreadId = " << mainThreadId << std::endl;
	
	return onExecute();
}

