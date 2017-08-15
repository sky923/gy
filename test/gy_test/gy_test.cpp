#include <gy/gy.h>
#include <iostream>
#include <stdio.h>

GY_APPLICATION(EntryPoint)
{
private:
	void test_compiler()
	{
		std::cout << _8("GY_COMPILER_MAJOR_VERSION = ") << GY_COMPILER_MAJOR_VERSION << std::endl;
		std::cout << _8("GY_COMPILER_MINOR_VERSION = ") << GY_COMPILER_MINOR_VERSION << std::endl;
		std::cout << _8("GY_COMPILER_PATCH_VERSION = ") << GY_COMPILER_PATCH_VERSION << std::endl;
	}
	
	void test_unicode()
	{
		std::cout.imbue(std::locale(""));
		c8_t test[] = _8("c8_t = 안A녕하세요B!!!\U0001F609\U0010FFFF🤖");
		std::cout << test << std::endl;
		
		c16_t test16[] = _16("c16_t = 안A녕하세요B!!!\U0001F605\U0010FFFF👻");
		std::cout << test16 << std::endl;
	}
	
protected:
	virtual result_t onPreInitialize() override
	{
		test_compiler();
		test_unicode();

		return GY_SUCCESS;
	}
};
