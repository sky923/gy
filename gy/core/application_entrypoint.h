#ifndef __gy_core_application_support_h__
#define __gy_core_application_support_h__

#include "../pil/type.h"

#if GY_OS_WIN_DESKTOP_IS_ENABLED || GY_OS_WIN_PHONE_IS_ENABLED
//-------+---------+---------+---------+---------+---------+---------+---------+
//@todo.sky923:
#	define GY_APPLICATION(entry_point_class_name)
#	error Not supported platform!
//-------+---------+---------+---------+---------+---------+---------+---------+
#elif defined (GY_OS_ANDROID_IS_ENABLED)
//-------+---------+---------+---------+---------+---------+---------+---------+
//@todo.sky923:
#	define GY_APPLICATION(entry_point_class_name)
#	error Not supported platform!
//-------+---------+---------+---------+---------+---------+---------+---------+
#elif defined (GY_OS_IS_STANDALONE) || defined (GY_OS_IOS_IS_ENABLED)
//-------+---------+---------+---------+---------+---------+---------+---------+
#	include <clocale>
#	if defined (GY_OS_WINDOWS_IS_ENABLED)
#		define GY_ENABLED_UNICODE_SUPPORTED_CONSOLE 0//std::cout.imbue(std::locale("")); std::wcout.imbue(std::locale(""))
#	else
#		define GY_ENABLED_UNICODE_SUPPORTED_CONSOLE 0
#	endif // defined (GY_ENABLED_OS_WINDESKTOP)
#	define GY_APPLICATION(entry_point_class_name) \
	\
	class entry_point_class_name;\
	int main(int argc, const c8_t **argv)\
	{\
		GY_ENABLED_UNICODE_SUPPORTED_CONSOLE;\
		return gy::setApplication<entry_point_class_name>(argc, argv);\
	}\
	class entry_point_class_name : public GApplication
//-------+---------+---------+---------+---------+---------+---------+---------+
#else
//-------+---------+---------+---------+---------+---------+---------+---------+
#	define GY_APPLICATION(entry_point_class_name)
#	error Not supported platform!
//-------+---------+---------+---------+---------+---------+---------+---------+
#endif

#endif // ifndef __gy_core_application_support_h__
