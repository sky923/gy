#include <gy/gy.h>
#include <iostream>
//#include <fcntl.h>
//#include <io.h>
#include <stdio.h>
//#include <Windows.h>

class GMyAppliaction : public GApplication
{
private:
	void test_unicode()
	{
//		SetConsoleOutputCP(CP_UTF8);
		std::cout.imbue(std::locale(""));
		c8_t test[] = _8("c8_t = 안A녕하세요B!!!\U0001F601\U0010FFFF😁");
		std::cout << test << std::endl;
		
		c16_t test16[] = _16("c16_t = 안A녕하세요B!!!\U0001F601\U0010FFFF😁");
		std::cout << test16 << std::endl;
	}
	
protected:
	virtual result_t execute() override
	{
		test_unicode();

		return GY_SUCCESS;
	}
};

int main(int argc, const char** argv)
{
	return gy::setApplication<GMyAppliaction>(argc, argv);
}
