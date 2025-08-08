// proxy_mode_monopolize.hpp

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

#ifndef __YGGR_PROXY_PROXY_MODE_PROXY_MODE_MONOPOLIZE_HPP__
#define __YGGR_PROXY_PROXY_MODE_PROXY_MODE_MONOPOLIZE_HPP__

#include <yggr/proxy/proxy_mode/proxy_mode_def.hpp>
#include <yggr/proxy/proxy_mode/basic_proxy_mode.hpp>

#include <yggr/iterator_ex/iterator.hpp>
#include <yggr/move/move.hpp>

#include <boost/range/functions.hpp>

namespace yggr
{
namespace proxy
{
namespace proxy_mode
{

template<typename ModeDataStore>
class proxy_mode_monopolize
	: public basic_proxy_mode<ModeDataStore>
{
public:
	YGGR_STATIC_CONSTANT(u32, E_mode = proxy_mode_def::E_proxy_mode_monopolize);

	typedef ModeDataStore mode_data_store_type;
	typedef basic_proxy_mode<mode_data_store_type> base_type;

	typedef typename base_type::owner_info_type owner_info_type;
	typedef typename base_type::owner_info_container_type owner_info_container_type;

	typedef typename base_type::store_type store_type;
	typedef typename base_type::ex_args_type ex_args_type;

private:
	typedef typename mode_data_store_type::vector_store_type vector_store_type;

private:
	typedef proxy_mode_monopolize this_type;

public:
	proxy_mode_monopolize(void) 
		: base_type(this_type::E_mode)
	{
	}

	~proxy_mode_monopolize(void) 
	{
	}

protected:
	virtual owner_info_container_type&
		pro_get_owner_info_container(owner_info_container_type& cont,
										const owner_info_type& owner_info,
										const store_type& oid_cont,
										const utility::basic_args_holder_nv*) const
	{
		const vector_store_type& vt = mode_data_store_type::s_get_vector_store_of_base(oid_cont);
		if(boost::empty(vt))
		{
			return cont;
		}

		owner_info_type info(owner_info);
		info.push(*(boost::begin(vt)));

		iterator_ex::inserter(cont, boost::end(cont)) = boost::move(info);

		return cont;
	}
};

} // namespace proxy_mode
} // namespace proxy
} // namespace yggr

#endif // __YGGR_PROXY_PROXY_MODE_PROXY_MODE_MONOPOLIZE_HPP__
