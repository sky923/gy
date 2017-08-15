#include "string.h"
//#include "sDefinition.h"

#if GY_OS_WINDOWS_IS_ENABLED && GY_COMPILER_MSVC_IS_ENABLED
#include <Windows.h>
#endif
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

namespace std
{
	template <typename T> std::u16string _to_u16string(T const &i)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<c16_t, 0x10ffff, std::little_endian>, c16_t> conv;
		return (c16_t *)(conv.from_bytes(std::to_string(i)).c_str());
	}

	std::u16string to_u16string(int __val) { return _to_u16string(__val); }
	std::u16string to_u16string(unsigned __val) { return _to_u16string(__val); }
	std::u16string to_u16string(long __val) { return _to_u16string(__val); }
	std::u16string to_u16string(unsigned long __val) { return _to_u16string(__val); }
	std::u16string to_u16string(long long __val) { return _to_u16string(__val); }
	std::u16string to_u16string(unsigned long long __val) { return _to_u16string(__val); }
	std::u16string to_u16string(float __val) { return _to_u16string(__val); }
	std::u16string to_u16string(double __val) { return _to_u16string(__val); }
	std::u16string to_u16string(long double __val) { return _to_u16string(__val); }
	
	ostream& operator << (ostream& os, const c16_t* c16)
	{
		os << str16to8(c16);
		return os;
	}
	
	ostream& operator << (ostream& os, const u16string& str16)
	{
		os << str16to8(str16);
		return os;
	}
}

//str8_t str16to8(const str8_t &mbcs) { return mbcs; }

str8_t str16to8(const str16_t &wbcs)
{
#if S_ENABLED_OS_WINFAMILY
	const int len = ::WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)(&wbcs[0]), -1, nullptr, 0, nullptr, nullptr) - 1;	
	str_t mbcs(len, u8_0);
	::WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)(&wbcs[0]), len, &mbcs[0], len, nullptr, nullptr);
#else
	const size_t len = wbcs.length();
	str8_t mbcs(len + 1, u8_0);

	//@ref: http://stackoverflow.com/questions/11512656/how-to-print-c-wstring-utf-8-characters-to-mac-os-or-unix-terminal
	//@ref: http://stackoverflow.com/questions/7232710/convert-between-string-u16string-u32string
	std::wstring_convert<std::codecvt_utf8_utf16<c16_t>, c16_t> converter; // converts between UTF-8 and UTF-16
	mbcs = converter.to_bytes(wbcs);
#endif
	return mbcs;
}
str8_t str16to8(const c16_t wbcs)
{
#if GY_OS_WINDOWS_IS_ENABLED && GY_COMPILER_MSVC_IS_ENABLED
	const int len = ::WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)(&wbcs), -1, nullptr, 0, nullptr, nullptr) - 1;	
	str8_t mbcs(len, u8_0);
	::WideCharToMultiByte(CP_UTF8, 0, (wchar_t *)(&wbcs), -1, &mbcs[0], len, nullptr, nullptr);
#else
	str8_t mbcs(sizeof(c16_t), u8_0);
	//	wcstombs(&mbcs[0], &wbcs, 1);
	//	std::wstring_convert<std::codecvt_utf8<c16_t>, c16_t> converter;
	std::wstring_convert<std::codecvt_utf8_utf16<c16_t>, c16_t> converter; // converts between UTF-8 and UTF-16
	mbcs = converter.to_bytes(wbcs);
#endif
	return mbcs;
}
//str8_t str16to8(const c8_t mbc)
//{
//	return str8_t({ mbc, '\0' });
//}

str16_t str8to16(const str8_t &mbcs)
{
#if GY_OS_WINDOWS_IS_ENABLED && GY_COMPILER_MSVC_IS_ENABLED
	const int len = ::MultiByteToWideChar(CP_UTF8, 0, &mbcs[0], -1, nullptr, 0);
	str16_t wbcs(len + 1, u16_0);
	::MultiByteToWideChar(CP_UTF8, 0, (char *)&mbcs[0], -1, (wchar_t *)&wbcs[0], len);
#else
	const size_t len = mbcs.length();
	str16_t wbcs(len + 1, u16_0);
	//	mbstowcs(&wbcs[0], &mbcs[0], len);
	std::wstring_convert<std::codecvt_utf8_utf16<c16_t>, c16_t> converter; // converts between UTF-8 and UTF-16
	wbcs = converter.from_bytes(mbcs);
#endif

	return wbcs;
}
//str16_t str8to16(const str16_t &wbcs) { return wbcs; }
str16_t str8to16(c8_t mbc)
{
	str16_t wbcs(2, u16_0);
#if GY_OS_WINDOWS_IS_ENABLED && GY_COMPILER_MSVC_IS_ENABLED
	::MultiByteToWideChar(CP_UTF8, 0, &mbc, -1, (wchar_t *)(&wbcs[0]), 1);
#else
	//	mbstowcs(&wbcs[0], &mbcs, 1);
	std::wstring_convert<std::codecvt_utf8_utf16<c16_t>, c16_t> converter; // converts between UTF-8 and UTF-16
	wbcs = converter.from_bytes(mbc);
#endif
	return wbcs;
}
//str16_t str8to16(const c16_t wbc) { return str16_t({ wbc, '\0' }); }
