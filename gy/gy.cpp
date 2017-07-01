#include "gy.h"
#include <iostream>
#include "config/config.h"

int printVersion()
{
	std::cout << GY_VERSION_MAJOR << "." << GY_VERSION_MINOR << std::endl;
	std::cout << "Operating System ID = " << (int)gy::pil::getCurrentOS() << std::endl;
	return 0;
}