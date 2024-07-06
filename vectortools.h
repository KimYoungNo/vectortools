//////////////////////////////////////////////////////////////////////////////
/*
  o -------------------------------------- o
    Compiler Options Used for Developement 
  o -------------------------------------- o
*/
//////////////////////////////////////////////////////////////////////////////

// Minimum C++ Standard:     C++11
// Recommended C++ Standard: C++20

// --------------------------------- gcc ---------------------------------- //
// Directives:      -std=c++20 -O3

// -------------------------------- clang --------------------------------- //
// Directives:      -std=c++20 -O3

// --------------------------------- msvc --------------------------------- //
// Directives:      /std:c++20 /Zc:__cplusplus /O2

#ifndef __VECTORTOOLS_H__
#define __VECTORTOOLS_H__

//////////////////////////////////////////////////////////////////////////////
/*
  o ------------------ o
    Preprocessor Macro
  o ------------------ o
*/
//////////////////////////////////////////////////////////////////////////////

// ----------------------------- user option ------------------------------ //
/*
 * Enabling NO_CXX20_VERSION_WARNING disables warnings for using a C++ standard
 * version lower than C++20. Be mindful that suppressing this warning may result
 * in overlooking potential compatibility issues or missing out on newer
 * language features. It's recommended to assess the implications before using
 * this option.
 */
#define NO_CXX20_VERSION_WARNING

/*
 * Enabling NO_VECTOR_LENGTH_CHECK disables all runtime error checks
 * for valid vector lengths in vector operations.
 * This may result in memory vulnerabilities.
 */
// #define NO_VECTOR_LENGTH_CHECK

/*
 * Enabling LONG_DOUBLE_AS_DEFAULT causes all functions returning doubles
 * to return long doubles instead. This can provide additional precision
 * but may result in reduced operation speed.
 */
// #define LONG_DOUBLE_AS_DEFAULT

/*
 * Enabling USE_DEFAULT_MULTITHREADING sets all multithreaded features
 * to use their default multithread setting.
 * This may lead to data corruption.
 */
// #define USE_DEFAULT_MULTITHREADING

// -------------------------- compiler statement -------------------------- //
// gcc options
#if defined(__GNUC__) && !defined(__clang__)
#   define __forceinline [[gnu::always_inline]]
#endif

// clang option
#ifdef __clang__
#   define __forceinline [[clang::always_inline]]
#endif

// msvc option
#ifdef _MSV_VER
#endif

// none of above
#if !defined(__GNUC__) && !defined(__clang__) && !defined(_MSC_VER)
#   define __forceinline inline
#endif

// -------------------- c++ standard version statement -------------------- //
// Macros for c++ standard version 
#define _CXX11_CPLUSPLUS 201103L
#define _CXX14_CPLUSPLUS 201402L
#define _CXX17_CPLUSPLUS 201703L
#define _CXX20_CPLUSPLUS 202002L

// Restriction for lower standard version of c++
#ifndef __cplusplus
#   error C++ compiler is required.
#elif __cplusplus < _CXX11_CPLUSPLUS
#   error C++11 or better is required.
#endif

// Empty macros for compatibility
#define _CXX17_NODISCARD
#define _CXX20_LIKELY
#define _CXX20_UNLIKELY
#define _CXX20_CONSTEXPR
#define _CXX20_CONSTEVAL

// Macro for each standard version's detail functionality
#if __cplusplus >= _CXX11_CPLUSPLUS
#   define _CXX11_FLAG
#endif

#if __cplusplus >= _CXX14_CPLUSPLUS
#   define _CXX14_FLAG
#endif

#if __cplusplus >= _CXX17_CPLUSPLUS
#   define _CXX17_FLAG

#   undef  _CXX17_NODISCARD
#   define _CXX17_NODISCARD [[nodiscard]]
#endif

#if __cplusplus >= _CXX20_CPLUSPLUS
#   define _CXX20_FLAG

#   undef  _CXX20_LIKELY
#   define _CXX20_LIKELY [[likely]]

#   undef  _CXX20_UNLIKELY
#   define _CXX20_UNLIKELY [[unlikely]]

#   undef  _CXX20_CONSTEXPR
#   define _CXX20_CONSTEXPR constexpr

#   undef  _CXX20_CONSTEVAL
#   define _CXX20_CONSTEVAL consteval
#endif

// Control warning message
#ifndef NO_CXX20_VERSION_WARNING
#   ifndef _CXX20_FLAG
#       pragma message(" \n\
    >> Use C++20 for more constexpr features. \n\
    >> Define macro \"NO_CXX20_VERSION_WARNING\" to ignore this warnings. \n\
    ")
#   endif
#endif

// Control default double
#ifndef LONG_DOUBLE_AS_DEFAULT
#   define VTOOL_DBL double
#else
#   define VTOOL_DBL long double
#endif

//////////////////////////////////////////////////////////////////////////////
// Include core header files
#include <vector>

#include "vtool_fft.h"
#include "vtool_utils.h"
#include "vtool_traits.h"
#include "vtool_windows.h"
#include "vtool_operator.h"

#undef NO_CXX20_VERSION_WARNING
#undef NO_VECTOR_LENGTH_CHECK
#undef LONG_DOUBLE_AS_DEFAULT
#undef USE_DEFAULT_MULTITHREADING

#undef _CXX11_CPLUSPLUS
#undef _CXX14_CPLUSPLUS
#undef _CXX17_CPLUSPLUS
#undef _CXX20_CPLUSPLUS

#undef _CXX11_FLAG
#undef _CXX14_FLAG
#undef _CXX17_FLAG
#undef _CXX20_FLAG

#undef _CXX17_NODISCARD
#undef _CXX20_LIKELY
#undef _CXX20_UNLIKELY
#undef _CXX20_CONSTEXPR
#undef _CXX20_CONSTEVAL

#endif  // __VECTORTOOLS_H__