#include "application.h"

#if GY_OS_WIN_STANDALONE_IS_ENABLED
#include <Windows.h>
#include <iostream>

#include <process.h>
#include <iostream>
#include <TlHelp32.h>

result_t GApplication::onPreInitialize() { return GY_SUCCESS; }
result_t GApplication::onInitialize() { return GY_SUCCESS; }
result_t GApplication::onPostInitialize() { return GY_SUCCESS; }

result_t GApplication::onExecuteEventDispatcher() 
{
	while (1)
	{
	}

	return GY_SUCCESS; 
}

result_t GApplication::onPreFinalize() { return GY_SUCCESS; }
result_t GApplication::onFinalize() { return GY_SUCCESS; }
result_t GApplication::onPostFinalize() { return GY_SUCCESS; }

#endif // if GY_OS_WIN_STANDALONE_IS_ENABLED
