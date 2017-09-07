#include "application.h"

#if GY_OS_OF_APPLE_IS_ENABLED

result_t GApplication::onPreInitialize() { return GY_SUCCESS; }
result_t GApplication::onInitialize() { return GY_SUCCESS; }
result_t GApplication::onPostInitialize() { return GY_SUCCESS; }

result_t GApplication::onExecute()
{
	getObject(getId());
	return GY_SUCCESS;
}

result_t GApplication::onPreFinalize() { return GY_SUCCESS; }
result_t GApplication::onFinalize() { return GY_SUCCESS; }
result_t GApplication::onPostFinalize() { return GY_SUCCESS; }

#endif // if GY_OS_IS_MACOS_ENABLED
