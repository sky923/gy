#ifndef __pil_platform_h__
#define __pil_platform_h__

namespace gy
{
	namespace pil
	{
		enum class EOperatingSystem : int
		{
			Unknown = -1
			, WindowsStandalone = 1000
			, WindowsUniversal = WindowsStandalone + 101
			, WindowsDesktop = WindowsStandalone + 102
			, WindowsPhone = WindowsStandalone + 103
			, MacOS = 2000
			, IOS = MacOS + 101
			, Linux = 3000
			, Android = Linux + 101
		};

#if defined(ANDROID) || defined(__ANDROID__)
#	define GY_OS_ANDROID_IS_ENABLED 1
#	define GY_OS_ID EOperatingSystem::Android
#elif defined(linux) || defined(__linux) || defined(__linux__)
#	define GY_OS_LINUX_IS_ENABLED 1
#	define GY_OS_IS_STANDALONE 1
#	define GY_OS_ID EOperatingSystem::Linux
#elif defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#	include <sdkddkver.h>
#	define GY_OS_WINDOWS_IS_ENABLED 1
#	if !defined (NTDDI_VERSION) || NTDDI_VERSION < 0x06020000
#		define GY_OS_WINDOWS_VERSION_IS_BEFORE_8 1
#		define GY_OS_WIN_STANDALONE_IS_ENABLED 1
#		define GY_OS_IS_STANDALONE 1
#		define GY_OS_ID EOperatingSystem::WindowsStandalone
#	else
#		include <winapifamily.h>
#	endif
#	ifdef WINAPI_FAMILY
#		if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) && defined (_MSC_VER) && (_MSC_VER >= 1800)
#			define GY_OS_WIN_PHONE_IS_ENABLED 1
#			define GY_OS_ID EOperatingSystem::WindowsPhone
#			if defined (_S_XAML) // need adding to compiler option, preprocessor, if you need Xaml
#				define GY_OS_WIN_WITH_XAML 1
#			endif
#		elif (WINAPI_FAMILY == WINAPI_FAMILY_PC_APP) && defined (_MSC_VER) && (_MSC_VER >= 1800)
#			define GY_OS_WIN_DESKTOP_IS_ENABLED 1
#			define GY_OS_ID EOperatingSystem::WindowsPhone
#			if defined (_S_XAML) // need adding to compiler option, preprocessor, if you need Xaml
#				define GY_OS_WIN_WITH_XAML 1
#			endif
#		elif (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#			if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#				define GY_OS_WIN_STANDALONE_IS_ENABLED 1
#				define GY_OS_IS_STANDALONE 1
#				define GY_OS_ID EOperatingSystem::WindowsStandalone
#			else
#				define GY_OS_UNKNOWN_IS_ENABLED 1
#				define GY_OS_ID EOperatingSystem::Unknown
#				error Unsupported Platform Detected
#			endif
#		else
#			define GY_OS_UNKNOWN_IS_ENABLED 1
#			define GY_OS_ID EOperatingSystem::Unknown
#			error Unsupported Platform Detected
#		endif
#	else
#		error Unsupported Platform Detected, Only support for Windows 8 or later.
#	endif
#elif defined(__APPLE__)
#	include <TargetConditionals.h>
#	if defined(TARGET_OS_IPHONE) && (TARGET_OS_IPHONE == 1)
#		define GY_OS_IOS_IS_ENABLED 1
#		define GY_OS_ID EOperatingSystem::IOS
#	elif defined(TARGET_IPHONE_SIMULATOR) && (TARGET_IPHONE_SIMULATOR == 1)
#		define GY_OS_IOS_IS_ENABLED 1
#		define GY_OS_IOS_SIMULATOR_IS_ENABLED 1
#		define GY_OS_ID EOperatingSystem::IOS
#	elif defined(TARGET_OS_MAC) && (TARGET_OS_MAC == 1)
#		define GY_OS_MACOS_IS_ENABLED 1
#		define GY_OS_IS_STANDALONE 1
#		define GY_OS_ID EOperatingSystem::MacOS
#	else
#		define GY_OS_UNKNOWN_IS_ENABLED 1
#		define GY_OS_ID EOperatingSystem::Unknown
#		error Unsupported Platform Detected
#	endif
#else
#	define GY_OS_UNKNOWN_IS_ENABLED 1
#	define GY_OS_ID EOperatingSystem::Unknown
#	error Unsupported Platform Detected
#endif

#if GY_OS_UNKNOWN_IS_ENABLED
#	ifndef GY_OS_ID
#		define GY_OS_ID EOperatingSystem::Unknown
#	endif
#endif
		constexpr EOperatingSystem getCurrentOS() { return GY_OS_ID; }

		enum class ECompiler : int
		{
			Unknown = -1
			, Clang = 1000
			, MSVC = 2000
			, GNUC = 3000
		};
		
//@ref: http://stackoverflow.com/questions/2658461/what-predefined-macro-can-i-use-to-detect-clang
#if defined (__clang__)
#	define GY_COMPILER_CLANG_IS_ENABLED 1
#	define GY_COMPILER_ID ECompiler::Clang
		//@todo:
#	define GY_COMPILER_IS_SUPPORTED_LARGE_NUMBER 1
		//@todo:
#	define GY_COMPILER_MAJOR_VERSION 3
#	define GY_COMPILER_MINOR_VERSION 0
#	define GY_COMPILER_MAINTENANCE_VERSION 0
#elif defined (_MSC_VER)
#	if (_MSC_VER >= 1900) && (_MSC_VER < 1910)
#		define GY_COMPILER_MSVC_IS_ENABLED 1
#		define GY_COMPILER_ID ECompiler::MSVC
#		define GY_COMPILER_IS_SUPPORTED_LARGE_NUMBER 1
#		define GY_COMPILER_MAJOR_VERSION 14
#		define GY_COMPILER_MINOR_VERSION 0
#		define GY_COMPILER_MAINTENANCE_VERSION 0
#	elif (_MSC_VER >= 1910) //&& _MSC_VER < 2000
#		define GY_COMPILER_MSVC_IS_ENABLED 1
#		define GY_COMPILER_ID ECompiler::MSVC
#		define GY_COMPILER_IS_SUPPORTED_LARGE_NUMBER 1
#		define GY_COMPILER_MAJOR_VERSION 141
#		define GY_COMPILER_MINOR_VERSION 0
#		define GY_COMPILER_MAINTENANCE_VERSION 0
#	else
#		define GY_COMPILER_IS_SUPPORTED_LARGE_NUMBER 0
#		define GY_COMPILER_MAJOR_VERSION 0
#		define GY_COMPILER_MINOR_VERSION 0
#		define GY_COMPILER_MAINTENANCE_VERSION 0
#		error Unsupported Compiler Detected
#	endif
#elif defined (__GNUC__)
#	define GY_COMPILER_GNUC_IS_ENABLED 1
#	define GY_COMPILER_ID ECompiler::GNUC
		//@todo:
#	define GY_COMPILER_IS_SUPPORTED_LARGE_NUMBER 1
		//@todo:
#	define GY_COMPILER_MAJOR_VERSION 6
#	define GY_COMPILER_MINOR_VERSION 0
#	define GY_COMPILER_MAINTENANCE_VERSION 0
#else
#	define GY_COMPILER_UNKNOWN_IS_ENABLED 1
#	define GY_COMPILER_ID ECompiler::Unknown
		//@todo:
#	define GY_COMPILER_IS_SUPPORTED_LARGE_NUMBER 0
#	define GY_COMPILER_MAJOR_VERSION 6
#	define GY_COMPILER_MINOR_VERSION 0
#	define GY_COMPILER_MAINTENANCE_VERSION 0
#	error Unsupported Compiler Detected
#endif
		constexpr ECompiler getCurrentCompiler() { return GY_COMPILER_ID; }
	}
}

#endif