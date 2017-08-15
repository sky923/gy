#ifndef __gy_pil_string_h__
#define __gy_pil_string_h__

#include "platform.h"
#include <string>


//#if GY_OS_WINDOWS_IS_ENABLED && GY_COMPILER_MSVC_IS_ENABLED
//typedef wchar_t c16_t;
//typedef std::wstring str16_t;
//#else
typedef char16_t c16_t;
typedef std::u16string str16_t;
//#endif
//typedef std::char8_t c8_t;
//typedef std::u8string str8_t;
typedef char c8_t;
typedef std::string str8_t;

namespace std
{
	//@ref: http://stackoverflow.com/questions/32055357/visual-studio-c-2015-stdcodecvt-with-char16-t-or-char32-t
	//@ref: https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
	
	std::u16string to_u16string(int __val);
	std::u16string to_u16string(unsigned __val);
	std::u16string to_u16string(long __val);
	std::u16string to_u16string(unsigned long __val);
	std::u16string to_u16string(long long __val);
	std::u16string to_u16string(unsigned long long __val);
	std::u16string to_u16string(float __val);
	std::u16string to_u16string(double __val);
	std::u16string to_u16string(long double __val);

	ostream& operator << (ostream& os, const c16_t* c16);
	ostream& operator << (ostream& os, const u16string& str16);
}

#define str16of(t) u ## #t
#define str16cond(t, cond) (cond ? str16_t(t) : str16_t())
#define _16(t) u ## t
#define make_str16(t) str16_t(u ## t)
#define to_str16(t) std::to_u16string(t)

#define str8of(t) u8 ## #t
#define str8cond(t, cond) (cond ? str8_t(t) : str8_t())
#define _8(t) u8 ## t
#define make_str8(t) str8_t(u8 ## t)
#define to_str8(t) std::to_string(t)

#if GY_OS_WINDOWS_IS_ENABLED && GY_COMPILER_MSVC_IS_ENABLED
#	define u16_sep u"\\"
#	define u8_sep u8"\\"
#	define u16_0 u'\0'
#	define u8_0 u8'\0'
#else
#	define u16_sep u"/"
#	define u8_sep u8"/"
#	define u16_0 u'\0'
#	define u8_0 '\0'
#endif

// Converted to Multi-bytes(UTF-8) Characters
str8_t str16to8(const str16_t &wbcs);
str8_t str16to8(const c16_t wbc);
#define str8(t) str16to8(t)
#define cstr8(t) str16to8(t).c_str()

// Converted to Wide-bytes(UTF-8) Characters
str16_t str8to16(const str8_t &mbcs);
str16_t str8to16(const c8_t mbcs);
#define str16(t) str8to16(t)
#define cstr16(t) str8to16(t).c_str()

#endif
