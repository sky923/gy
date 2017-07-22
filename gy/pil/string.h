#ifndef __gy_pil_string_h__
#define __gy_pil_string_h__

#include "platform.h"
#include <string>

namespace std
{
	//@ref: http://stackoverflow.com/questions/32055357/visual-studio-c-2015-stdcodecvt-with-char16-t-or-char32-t
	//@ref: https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral

	typedef std::basic_ios<char16_t, std::char_traits<char16_t> > u16ios;
	typedef std::basic_streambuf<char16_t, std::char_traits<char16_t> > u16streambuf;
	typedef std::basic_istream<char16_t, std::char_traits<char16_t> > u16istream;
	typedef std::basic_ostream<char16_t, std::char_traits<char16_t> > u16ostream;
	typedef std::basic_iostream<char16_t, std::char_traits<char16_t> > u16iostream;
	typedef std::basic_stringbuf<char16_t, std::char_traits<char16_t>, std::allocator<char16_t> > u16stringbuf;
	typedef std::basic_istringstream<char16_t, std::char_traits<char16_t>, std::allocator<char16_t> > u16istringstream;
	typedef std::basic_ostringstream<char16_t, std::char_traits<char16_t>, std::allocator<char16_t> > u16ostringstream;
	typedef std::basic_stringstream<char16_t, std::char_traits<char16_t>, std::allocator<char16_t> > u16stringstream;
	typedef std::basic_filebuf<char16_t, std::char_traits<char16_t> > u16filebuf;
	typedef std::basic_ifstream<char16_t, std::char_traits<char16_t> > u16ifstream;
	typedef std::basic_ofstream<char16_t, std::char_traits<char16_t> > u16ofstream;
	typedef std::basic_fstream<char16_t, std::char_traits<char16_t> > u16fstream;
	
	//extern u16streambuf u16sb;
	extern u16ostream u16cout;
	std::u16string to_u16string(int __val);
	std::u16string to_u16string(unsigned __val);
	std::u16string to_u16string(long __val);
	std::u16string to_u16string(unsigned long __val);
	std::u16string to_u16string(long long __val);
	std::u16string to_u16string(unsigned long long __val);
	std::u16string to_u16string(float __val);
	std::u16string to_u16string(double __val);
	std::u16string to_u16string(long double __val);

	//typedef char char8_t;
	//typedef std::basic_ios<char8_t, std::char_traits<char8_t> > u8ios;
	//typedef std::basic_streambuf<char8_t, std::char_traits<char8_t> > u8streambuf;
	//typedef std::basic_istream<char8_t, std::char_traits<char8_t> > u8istream;
	//typedef std::basic_ostream<char8_t, std::char_traits<char8_t> > u8ostream;
	//typedef std::basic_iostream<char8_t, std::char_traits<char8_t> > u8iostream;
	//typedef std::basic_stringbuf<char8_t, std::char_traits<char8_t>, std::allocator<char8_t> > u8stringbuf;
	//typedef std::basic_istringstream<char8_t, std::char_traits<char8_t>, std::allocator<char8_t> > u8istringstream;
	//typedef std::basic_ostringstream<char8_t, std::char_traits<char8_t>, std::allocator<char8_t> > u8ostringstream;
	//typedef std::basic_stringstream<char8_t, std::char_traits<char8_t>, std::allocator<char8_t> > u8stringstream;
	//typedef std::basic_filebuf<char8_t, std::char_traits<char8_t> > u8filebuf;
	//typedef std::basic_ifstream<char8_t, std::char_traits<char8_t> > u8ifstream;
	//typedef std::basic_ofstream<char8_t, std::char_traits<char8_t> > u8ofstream;
	//typedef std::basic_fstream<char8_t, std::char_traits<char8_t> > u8fstream;
	//typedef std::basic_string<char8_t, char_traits<char8_t>, allocator<char8_t> > u8string;
}

typedef wchar_t uch_t;
typedef std::wstring ustr_t;

#define str16of(t) u ## #t
#define str16cond(t, cond) (cond ? str16_t(t) : str16_t())
#define _16(t) u ## t
#define make_str16(t) str16_t(u ## t)
#define to_str16(t) std::to_u16string(t)

//typedef std::char8_t c8_t;
//typedef std::u8string str8_t;
typedef char c_t;
typedef std::string str_t;
#define str8of(t) u8 ## #t
#define str8cond(t, cond) (cond ? str8_t(t) : str8_t())
#define _8(t) u8 ## t
#define make_str8(t) str8_t(u8 ## t)
#define to_str8(t) std::to_string(t)

#define TXT(t) _8(t)
#define SEP sSEP8

#if GY_OS_WINDOWS_IS_ENABLED && GY_COMPILER_MSVC_IS_ENABLED
#	define sSEP16 u"\\"
#	define sSEP8 u8"\\"
#else
#	define sSEP16 u"/"
#	define sSEP8 u8"/"
#endif

// Converted to Multi-bytes(UTF-8) Characters
str_t str16to8(const ustr_t &wbcs);
str_t str16to8(const uch_t wbc);
#define str8(t) str16to8(t)
#define cstr8(t) str16to8(t).c_str()

// Converted to Wide-bytes(UTF-8) Characters
ustr_t str8to16(const str_t &mbcs);
ustr_t str8to16(const c_t mbcs);
#define str16(t) str8to16(t)
#define cstr16(t) str8to16(t).c_str()

#endif