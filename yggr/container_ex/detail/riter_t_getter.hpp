// riter_t_getter.hpp

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

#ifndef __YGGR_CONTAINER_EX_DETAIL_RITER_T_GETTER_HPP__
#define __YGGR_CONTAINER_EX_DETAIL_RITER_T_GETTER_HPP__

#include <yggr/container/rbegin.hpp>
#include <boost/mpl/if.hpp>

namespace yggr
{
namespace container_ex
{

namespace detail
{

template<typename Cont, bool chk_has_beg_end>
struct riter_t_getter;

template<typename Cont>
struct riter_t_getter<Cont, true>
{
protected:
	typedef Cont cont_type;

public:
	typedef typename cont_type::reverse_iterator riter_type;
	typedef typename cont_type::const_reverse_iterator criter_type;
};

template<typename Cont>
struct riter_t_getter<Cont, false>
{
protected:
	typedef Cont cont_type;

public:
	typedef typename range_ex::range_reverse_iterator_ex<cont_type>::type riter_type;
	typedef typename range_ex::range_const_reverse_iterator_ex<cont_type>::type criter_type;
};

} // namesapce detail
} // namespace container_ex
} // namespace yggr

#endif // __YGGR_CONTAINER_EX_DETAIL_RITER_T_GETTER_HPP__

