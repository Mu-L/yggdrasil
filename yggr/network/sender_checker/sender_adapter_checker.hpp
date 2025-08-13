//sender_adapter_checker.hpp

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

#ifndef __YGGR_NETWORK_SENDER_CHECKER_SENDER_ADAPTER_CHECKER_HPP__
#define __YGGR_NETWORK_SENDER_CHECKER_SENDER_ADAPTER_CHECKER_HPP__

#include <yggr/base/yggrdef.h>

#include <yggr/adapter/adapter_register_type_def.hpp>
#include <yggr/adapter/adapter_default_tag_def.hpp>

namespace yggr
{
namespace network
{
namespace sender_checker
{

struct sender_adapter_checker
{

private:
	typedef adapter::adapter_register_type_def reg_def_type;
	typedef adapter::adapter_default_tag_def tag_def_type;

private:
	typedef sender_adapter_checker this_type;

protected:
	template<typename Data, typename NetEntityPtr> inline
	static bool pro_s_chk_send_enable(NetEntityPtr pentity)
	{
		typedef NetEntityPtr net_entity_ptr_type;
		typedef Data data_type;
		typedef typename net_entity_ptr_type::value_type net_entity_type;
		typedef typename net_entity_type::adapter_mgr_ptr_type adapter_mgr_ptr_type;

		id_parser_type parser;
		adapter_mgr_ptr_type padp = pentity? pentity->get_adapter_mgr_ptr() : adapter_mgr_ptr_type();
		return padp && padp->template check_enable_adapter<data_type>(reg_def_type::E_to_src);
	}

	template<typename NetEntityPtr, typename ID> inline
	static bool pro_s_chk_send_enable(NetEntityPtr pentity, const ID& id)
	{
		typedef NetEntityPtr net_entity_ptr_type;
		typedef typename net_entity_ptr_type::value_type net_entity_type;
		typedef typename net_entity_type::adapter_mgr_ptr_type adapter_mgr_ptr_type;

		adapter_mgr_ptr_type padp = pentity? pentity->get_adapter_mgr_ptr() : adapter_mgr_ptr_type();

		return padp && padp->check_enable_adapter(id, tag_def_type::E_tag_send, reg_def_type::E_to_src);
	}

public:
	template<typename NetEntityPtr, typename Key, typename NetInfo, typename Data, typename Handler> inline
	bool operator()(NetEntityPtr pentity, const Key& /*key*/, const NetInfo& /*netinfo*/, const Data& /*data*/, const Handler& /*handler*/) const
	{
		typedef NetEntityPtr net_entity_ptr_type;
		typedef Data data_type;
		typedef typename net_entity_ptr_type::value_type net_entity_type;
		typedef typename net_entity_type::adapter_mgr_type adapter_mgr_type;
		typedef typename adapter_mgr_type::id_parser_type id_parser_type;
		typedef typename id_parser_type::tag_send tag_send_type;

		return this_type::pro_s_chk_send_enable<data_type>(pentity);

	}

	template<typename NetEntityPtr, typename Key, typename Pak, typename Handler> inline
	bool send_packet(NetEntityPtr pentity, const Key& /*key*/, Pak& pak, const Handler& /*handler*/) const
	{
		typedef NetEntityPtr net_entity_ptr_type;
		typedef typename net_entity_ptr_type::value_type net_entity_type;
		typedef typename net_entity_type::adapter_mgr_type adapter_mgr_type;
		typedef typename adapter_mgr_type::id_parser_type id_parser_type;
		typedef typename id_parser_type::tag_send tag_send_type;

		id_parser_type parser;

		return this_type::pro_s_chk_send_enable(pentity, parser.template value_id<tag_send_type>(pak));
	}

	template<typename NetEntityPtr, typename Key, typename Pak> inline
	bool send_packet(NetEntityPtr pentity, const Key& /*key*/, const Pak& pak) const
	{
		typedef NetEntityPtr net_entity_ptr_type;
		typedef typename net_entity_ptr_type::value_type net_entity_type;
		typedef typename net_entity_type::adapter_mgr_type adapter_mgr_type;
		typedef typename adapter_mgr_type::id_parser_type id_parser_type;
		typedef typename id_parser_type::tag_send tag_send_type;

		id_parser_type parser;

		return this_type::pro_s_chk_send_enable(pentity, parser.template value_id<tag_send_type>(pak));
	}

};

} // namespace sender_checker
} // namespace network
} // namespace yggr

#endif //__YGGR_NETWORK_SENDER_CHECKER_SENDER_ADAPTER_CHECKER_HPP__
