#include <gy/gy.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <Windows.h>

class GMyAppliaction : public GApplication
{
protected:
	virtual result_t execute() override
	{
		SetConsoleOutputCP(CP_UTF8);
		std::cout.imbue(std::locale(""));
		c_t test[] = _8("안A녕하세요B!!!\U0010FFFF😁");
		std::cout << test << std::endl;

		return GY_SUCCESS;
	}
};

int main(int argc, const char** argv)
{
	return gy::setApplication<GMyAppliaction>(argc, argv);
}