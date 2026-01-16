//default_value_comparer.hpp

/****************************************************************************
Copyright (c) 2026-2026 yggdrasil

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

#ifndef __YGGR_UTILITY_DEFAULT_VALUE_COMPARER_HPP__
#define __YGGR_UTILITY_DEFAULT_VALUE_COMPARER_HPP__

#include <yggr/base/yggrdef.h>
#include <yggr/typeof/default_value.hpp>


namespace yggr
{
namespace utility
{

template<typename T> YGGR_CXX17_CONSTEXPR_OR_INLINE
bool equal_to_default_value(const T& l)
{
	return l == create_object<T>();
}

template<typename T> YGGR_CXX17_CONSTEXPR_OR_INLINE
bool not_equal_to_default_value(const T& l)
{
	return !equal_to_default_value(l);
}

template<typename T> YGGR_CXX17_CONSTEXPR_OR_INLINE
bool less_default_value(const T& l)
{
	return l < create_object<T>();
}

template<typename T> YGGR_CXX17_CONSTEXPR_OR_INLINE
bool less_equal_default_value(const T& l)
{
	return !(create_object<T>() < l);
}

template<typename T> YGGR_CXX17_CONSTEXPR_OR_INLINE
bool greater_default_value(const T& l)
{
	return !less_equal_default_value(l);
}

template<typename T> YGGR_CXX17_CONSTEXPR_OR_INLINE
bool greater_equal_default_value(const T& l)
{
	return !less_default_value(l);
}

} // namespace utility

using utility::equal_to_default_value;
using utility::not_equal_to_default_value;
using utility::less_default_value;
using utility::less_equal_default_value;
using utility::greater_default_value;
using utility::greater_equal_default_value;

} // namespace yggr

#endif // __YGGR_UTILITY_DEFAULT_VALUE_COMPARER_HPP__
