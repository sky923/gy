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
		
		return gy::appInstance->executeEventDispatcherThread();
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

result_t GApplication::executeEventDispatcherThread()
{
	std::cout << "mainThreadId = " << mainThreadId << std::endl;

	/*
	std::thread sub([&tryFinishApp]()
	{
		//int i = 0;
		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}

			SwitchToThread();
		}

		tryFinishApp = true;
	});
	*/


	std::thread eventDispatchThread([&]() 
	{
		//@todo:
		onExecuteEventDispatcher();
	});
	eventDispatchThreadId = eventDispatchThread.get_id();
	std::cout << "eventDispatchThreadId = " << eventDispatchThreadId << std::endl;


	return onExecute();
}
