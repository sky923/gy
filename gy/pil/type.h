#ifndef __gy_pil_type_h__
#define __gy_pil_type_h__

//@note: type naming rules
// G* : class of GObject based
// C* : normal class
// S* : struct
// E* : enum class (not an enum)
// k* : const type
// (all upper cases) * : define
// b* : boolean (true or flase, 0 or else)
// name of types are only use for lower case
// but, functions are not only lower case, as like, getValue
// and valiables are also as like function's rule

#include "platform.h"

namespace gy
{
	namespace type
	{
		//@note: default types for systems
		typedef bool b_t;
		typedef signed char i8_t;
		typedef unsigned char ui8_t;
		typedef signed short i16_t;
		typedef unsigned short ui16_t;
		typedef signed int i32_t;
		typedef unsigned int ui32_t;
		typedef float f_t;
		typedef double d_t;
		typedef void *vptr_t;
#if GY_COMPILER_IS_SUPPORTED_LARGE_NUMBER
		typedef signed long long i64_t;
		typedef unsigned long long ui64_t;
		typedef long double ld_t;
#else
#	error Unsupported Large Number as 64bits
#endif

		typedef ui32_t result_t;
#define GY_SUCCESS ((result_t)(0))
#define GY_FAIL ((result_t)(-1))

		typedef ui64_t identity_t;
#define GY_INVALID ((identity_t)(-1))
	}
}

using namespace gy::type;

// optional
//@ref: https://github.com/akrzemi1/Optional
//@note: it's temporarily things until compiler of c++17 or above has a big pie in industry.
//@ref: http://en.cppreference.com/w/cpp/utility/optional
//#include "type_optional.h"
//namespace std
//{
//	using experimental::optional;
//}

struct identifier_t { };
struct null_t { };

#endif
