// begin_getter.hpp

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

#ifndef __YGGR_CONTAINER_EX_BEGIN_GETTER_HPP__
#define __YGGR_CONTAINER_EX_BEGIN_GETTER_HPP__

#include <yggr/container/begin.hpp>
#include <yggr/range_ex/range_iterator_ex.hpp>

namespace yggr
{
namespace container_ex
{

template<typename Cont>
struct begin_getter
{
public:
	typedef Cont container_type;
	typedef typename range_ex::range_iterator_ex<container_type>::type iterator_type;
	typedef typename range_ex::range_const_iterator_ex<container_type>::type const_iterator_type;

public:
	inline iterator_type operator()(container_type& cont) const
	{
		return container::begin(cont);
	}

	inline const_iterator_type operator()(const container_type& cont) const
	{
		return container::cbegin(cont);
	}
};

template<typename Cont>
struct cbegin_getter
{
public:
	typedef Cont container_type;
	typedef typename range_ex::range_iterator_ex<container_type>::type iterator_type;
	typedef typename range_ex::range_const_iterator_ex<container_type>::type const_iterator_type;

public:
	inline const_iterator_type operator()(const container_type& cont) const
	{
		return container::cbegin(cont);
	}
};

} // namespace container_ex
} // namespace yggr

#endif // __YGGR_CONTAINER_EX_BEGIN_GETTER_HPP__

