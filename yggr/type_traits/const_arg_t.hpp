// const_arg_t.hpp

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

#ifndef __YGGR_TYPE_TRAITS_CONST_ARG_T_HPP__
#define __YGGR_TYPE_TRAITS_CONST_ARG_T_HPP__

#include <yggr/base/yggrdef.h>

#include <yggr/type_traits/traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_class.hpp>

namespace yggr
{
namespace type_traits
{

namespace detail
{

template<typename T, bool chk_is_class = boost::is_class<T>::value >
struct const_arg_t_impl
	: public traits<const T&>
{
};

template<typename T>
struct const_arg_t_impl<T, false>
	: public traits<T>
{
};

} // namespace detail

template<typename T>
struct const_arg_t
	: public detail::const_arg_t_impl<T>
{
};

} // namespace type_traits

using type_traits::const_arg_t;

} // namespace yggr

#endif // __YGGR_TYPE_TRAITS_CONST_ARG_T_HPP__
