// any_has_value_empty.hpp

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

#ifndef __YGGR_ANY_VAL_ANY_HAS_VALUE_EMPTY_HPP__
#define __YGGR_ANY_VAL_ANY_HAS_VALUE_EMPTY_HPP__

#include <yggr/base/yggrdef.h>

#include <yggr/ppex/has_member_check.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>

namespace yggr
{
namespace any_val
{
namespace detail
{

YGGR_PP_HAS_MEMBER_FOO_DEF(any_empty, T, bool, empty, YGGR_PP_SYMBOL_BOOL_TRUE(), void)

YGGR_PP_HAS_MEMBER_FOO_DEF(any_has_value, T, bool, has_value, YGGR_PP_SYMBOL_BOOL_TRUE(), void)

template<typename T>
struct any_has_empty_and_has_value_both
	: public
		boost::mpl::and_
		<
			has_any_empty<T>,
			has_any_has_value<T>
		>::type
{
};

template<typename T>
struct any_has_empty_only
	: public
		boost::mpl::and_
		<
			has_any_empty<T>,
			typename boost::mpl::not_< has_any_has_value<T> >::type
		>::type
{
};

template<typename T>
struct any_has_has_value_only
	: public
		boost::mpl::and_
		<
			typename boost::mpl::not_< has_any_empty<T> >::type,
			has_any_has_value<T>
		>::type
{
};

} // namespace detail
} // namespace any_val
} // namespace yggr

namespace yggr
{
namespace any_val
{

template<typename Any> inline
typename 
	boost::enable_if
	<
		typename
			boost::mpl::and_
			<
				is_any<Any>,
				typename
					boost::mpl::or_
					<
						detail::any_has_empty_and_has_value_both<Any>,
						detail::any_has_empty_only<Any>
					>::type
			>::type,
		bool
	>::type
	any_has_value(const Any& val)
{
	return !val.empty();
}

template<typename Any> inline
typename 
	boost::enable_if
	<
		typename
			boost::mpl::and_
			<
				is_any<Any>,
				detail::any_has_has_value_only<Any>
			>::type,
		bool
	>::type
	any_has_value(const Any& val)
{
	return val.has_value();
}

template<typename Any> inline
typename 
	boost::enable_if
	<
		typename
			boost::mpl::and_
			<
				is_any<Any>,
				typename
					boost::mpl::or_
					<
						detail::any_has_empty_and_has_value_both<Any>,
						detail::any_has_empty_only<Any>
					>::type
			>::type,
		bool
	>::type
	any_empty(const Any& val)
{
	return val.empty();
}

template<typename Any> inline
typename 
	boost::enable_if
	<
		typename
			boost::mpl::and_
			<
				is_any<Any>,
				detail::any_has_has_value_only<Any>
			>::type,
		bool
	>::type
	any_empty(const Any& val)
{
	return !val.has_value();
}

} // namespace any_val
} // namespace yggr

#endif // __YGGR_ANY_VAL_ANY_HAS_VALUE_EMPTY_HPP__