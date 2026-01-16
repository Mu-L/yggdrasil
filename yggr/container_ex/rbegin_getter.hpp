// rbegin_getter.hpp

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

#ifndef __YGGR_CONTAINER_EX_RBEGIN_GETTER_HPP__
#define __YGGR_CONTAINER_EX_RBEGIN_GETTER_HPP__

#include <yggr/container/rbegin.hpp>
#include <yggr/container_ex/detail/riter_t_getter.hpp>
#include <boost/mpl/if.hpp>

namespace yggr
{
namespace container_ex
{

template<typename Cont>
struct rbegin_getter
{
public:
	typedef Cont container_type;

protected:
	typedef 
		detail::riter_t_getter
		<
			container_type,
			container::detail::has_any_rbegin<container_type>::value
		> riter_t_getter_type;

public:
	typedef typename riter_t_getter_type::riter_type iterator_type;
	typedef typename riter_t_getter_type::criter_type const_iterator_type;

public:
	inline iterator_type operator()(container_type& cont) const
	{
		return container::rbegin(cont);
	}

	inline const_iterator_type operator()(const container_type& cont) const
	{
		return container::rbegin(cont);
	}
};

template<typename Cont>
struct crbegin_getter
{
public:
	typedef Cont container_type;

protected:
	typedef 
		detail::riter_t_getter
		<
			container_type,
			container::detail::has_any_rbegin<container_type>::value
		> riter_t_getter_type;

public:
	typedef typename riter_t_getter_type::riter_type iterator_type;
	typedef typename riter_t_getter_type::criter_type const_iterator_type;

public:
	inline const_iterator_type operator()(const container_type& cont) const
	{
		return container::crbegin(cont);
	}
};

} // namespace container_ex
} // namespace yggr

#endif // __YGGR_CONTAINER_EX_RBEGIN_GETTER_HPP__

