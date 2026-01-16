// pragma_warning.hpp

/****************************************************************************
Copyright (c) 2010-2024 yggdrasil

author: xu yang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __YGGR_BASE_PRAGMA_WARNING_PUSH_POP_HPP__
#define __YGGR_BASE_PRAGMA_WARNING_PUSH_POP_HPP__

#if defined(_MSC_VER) && (_MSC_VER)

#	define YGGR_DO_PRAGMA( __x__ ) __pragma( __x__ )
#	define YGGR_PRAGMA_WARNING_PUSH() YGGR_DO_PRAGMA(warning(push))
#	define YGGR_PRAGMA_WARNING_POP() YGGR_DO_PRAGMA(warning(pop))

#	define YGGR_PRAGMA_WARNING_DEFAULT_MSVC( __n__ ) YGGR_DO_PRAGMA(warning(default: __n__))
#	define YGGR_PRAGMA_WARNING_WARNING_MSVC YGGR_PRAGMA_WARNING_DEFAULT_MSVC
#	define YGGR_PRAGMA_WARNING_DISABLE_MSVC( __n__ ) YGGR_DO_PRAGMA(warning(disable: __n__))
#	define YGGR_PRAGMA_WARNING_ERROR_MSVC( __n__ ) YGGR_DO_PRAGMA(warning(error: __n__))

#	define YGGR_PRAGMA_WARNING_DEFAULT_NOT_MSVC( __n__ ) 
#	define YGGR_PRAGMA_WARNING_WARNING_NOT_MSVC( __n__ ) 
#	define YGGR_PRAGMA_WARNING_DISABLE_NOT_MSVC( __n__ )
#	define YGGR_PRAGMA_WARNING_ERROR_NOT_MSVC( __n__ )

#elif defined(__clang__) && (__clang__)

#	define YGGR_DO_PRAGMA( __x__ ) _Pragma(#__x__)
#	define YGGR_PRAGMA_WARNING_PUSH() YGGR_DO_PRAGMA(clang diagnostic push)
#	define YGGR_PRAGMA_WARNING_POP() YGGR_DO_PRAGMA(clang diagnostic pop)

#	define YGGR_PRAGMA_WARNING_DEFAULT_CLANG( __n__ ) YGGR_DO_PRAGMA(clang diagnostic default __n__)
#	define YGGR_PRAGMA_WARNING_WARNING_CLANG( __n__ ) YGGR_DO_PRAGMA(clang diagnostic warning __n__)
#	define YGGR_PRAGMA_WARNING_DISABLE_CLANG( __n__ ) YGGR_DO_PRAGMA(clang diagnostic ignored __n__)
#	define YGGR_PRAGMA_WARNING_ERROR_CLANG( __n__ ) YGGR_DO_PRAGMA(clang diagnostic error __n__)

#	define YGGR_PRAGMA_WARNING_DEFAULT_NOT_MSVC YGGR_PRAGMA_WARNING_DEFAULT_CLANG
#	define YGGR_PRAGMA_WARNING_WARNING_NOT_MSVC YGGR_PRAGMA_WARNING_WARNING_CLANG
#	define YGGR_PRAGMA_WARNING_DISABLE_NOT_MSVC YGGR_PRAGMA_WARNING_DISABLE_CLANG
#	define YGGR_PRAGMA_WARNING_ERROR_NOT_MSVC YGGR_PRAGMA_WARNING_ERROR_CLANG

#elif defined(__GNUC__) && (__GNUC__)

#	define YGGR_DO_PRAGMA( __x__ ) _Pragma(#__x__)
#	define YGGR_PRAGMA_WARNING_PUSH() YGGR_DO_PRAGMA(GCC diagnostic push)
#	define YGGR_PRAGMA_WARNING_POP() YGGR_DO_PRAGMA(GCC diagnostic pop)

#	define YGGR_PRAGMA_WARNING_DEFAULT_GCC( __n__ ) YGGR_DO_PRAGMA(GCC diagnostic default __n__)
#	define YGGR_PRAGMA_WARNING_WARNING_GCC( __n__ ) YGGR_DO_PRAGMA(GCC diagnostic warning __n__)
#	define YGGR_PRAGMA_WARNING_DISABLE_GCC( __n__ ) YGGR_DO_PRAGMA(GCC diagnostic ignored __n__)
#	define YGGR_PRAGMA_WARNING_ERROR_GCC( __n__ ) YGGR_DO_PRAGMA(GCC diagnostic error __n__)

#	define YGGR_PRAGMA_WARNING_DEFAULT_NOT_MSVC YGGR_PRAGMA_WARNING_DEFAULT_GCC
#	define YGGR_PRAGMA_WARNING_WARNING_NOT_MSVC YGGR_PRAGMA_WARNING_WARNING_GCC
#	define YGGR_PRAGMA_WARNING_DISABLE_NOT_MSVC YGGR_PRAGMA_WARNING_DISABLE_GCC
#	define YGGR_PRAGMA_WARNING_ERROR_NOT_MSVC YGGR_PRAGMA_WARNING_ERROR_GCC

#else

#	define YGGR_PRAGMA_WARNING_PUSH() 
#	define YGGR_PRAGMA_WARNING_POP()

#endif // _MSC_VER

// msvc
#if !defined(YGGR_PRAGMA_WARNING_DEFAULT_MSVC)
#	define YGGR_PRAGMA_WARNING_DEFAULT_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_DEFAULT_MSVC

#if !defined(YGGR_PRAGMA_WARNING_WARNING_MSVC)
#	define YGGR_PRAGMA_WARNING_WARNING_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_WARNING_MSVC

#if !defined(YGGR_PRAGMA_WARNING_DISABLE_MSVC)
#	define YGGR_PRAGMA_WARNING_DISABLE_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_DISABLE_MSVC

#if !defined(YGGR_PRAGMA_WARNING_ERROR_MSVC)
#	define YGGR_PRAGMA_WARNING_ERROR_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_ERROR_MSVC

// not_msvc
#if !defined(YGGR_PRAGMA_WARNING_DEFAULT_NOT_MSVC)
#	define YGGR_PRAGMA_WARNING_DEFAULT_NOT_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_DEFAULT_NOT_MSVC

#if !defined(YGGR_PRAGMA_WARNING_WARNING_NOT_MSVC)
#	define YGGR_PRAGMA_WARNING_WARNING_NOT_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_WARNING_NOT_MSVC

#if !defined(YGGR_PRAGMA_WARNING_DISABLE_NOT_MSVC)
#	define YGGR_PRAGMA_WARNING_DISABLE_NOT_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_DISABLE_NOT_MSVC

#if !defined(YGGR_PRAGMA_WARNING_ERROR_NOT_MSVC)
#	define YGGR_PRAGMA_WARNING_ERROR_NOT_MSVC( __n__ )
#endif // YGGR_PRAGMA_WARNING_ERROR_NOT_MSVC

// clang
#if !defined(YGGR_PRAGMA_WARNING_DEFAULT_CLANG)
#	define YGGR_PRAGMA_WARNING_DEFAULT_CLANG( __n__ )
#endif // YGGR_PRAGMA_WARNING_DEFAULT_CLANG

#if !defined(YGGR_PRAGMA_WARNING_WARNING_CLANG)
#	define YGGR_PRAGMA_WARNING_WARNING_CLANG( __n__ )
#endif // YGGR_PRAGMA_WARNING_WARNING_CLANG

#if !defined(YGGR_PRAGMA_WARNING_DISABLE_CLANG)
#	define YGGR_PRAGMA_WARNING_DISABLE_CLANG( __n__ )
#endif // YGGR_PRAGMA_WARNING_DISABLE_CLANG

#if !defined(YGGR_PRAGMA_WARNING_ERROR_CLANG)
#	define YGGR_PRAGMA_WARNING_ERROR_CLANG( __n__ )
#endif // YGGR_PRAGMA_WARNING_ERROR_CLANG

// gcc
#if !defined(YGGR_PRAGMA_WARNING_DEFAULT_GCC)
#	define YGGR_PRAGMA_WARNING_DEFAULT_GCC( __n__ )
#endif // YGGR_PRAGMA_WARNING_DEFAULT_GCC

#if !defined(YGGR_PRAGMA_WARNING_WARNING_GCC)
#	define YGGR_PRAGMA_WARNING_WARNING_GCC( __n__ )
#endif // YGGR_PRAGMA_WARNING_WARNING_GCC

#if !defined(YGGR_PRAGMA_WARNING_DISABLE_GCC)
#	define YGGR_PRAGMA_WARNING_DISABLE_GCC( __n__ )
#endif // YGGR_PRAGMA_WARNING_DISABLE_GCC

#if !defined(YGGR_PRAGMA_WARNING_ERROR_GCC)
#	define YGGR_PRAGMA_WARNING_ERROR_GCC( __n__ )
#endif // YGGR_PRAGMA_WARNING_ERROR_GCC

#endif // __YGGR_BASE_PRAGMA_WARNING_PUSH_POP_HPP__