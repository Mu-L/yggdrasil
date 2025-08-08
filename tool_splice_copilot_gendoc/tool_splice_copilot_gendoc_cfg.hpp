// tool_splice_copilot_gendoc_cfg.hpp

#ifndef __TOOL_SUO_BATCH_SELECTOR_CFG_HPP__
#define __TOOL_SUO_BATCH_SELECTOR_CFG_HPP__

#include <yggr/base/yggrdef.h>

#include <boost/ref.hpp>

#include <yggr/ppex/swap_this_def.hpp>
#include <yggr/utility/copy_or_move_or_swap.hpp>

#include <yggr/serialization/access.hpp>

#include <yggr/charset/utf8_string.hpp>
#include <yggr/container/array.hpp>

#include <yggr/serialization/nvp.hpp>
#include <yggr/serialization/utf8_string.hpp>
#include <yggr/serialization/array.hpp>


struct tool_splice_copilot_gendoc_cfg_sample {};

struct tool_splice_copilot_gendoc_cfg
{
public:
	typedef yggr::utf8_string string_type;

private:
	typedef tool_splice_copilot_gendoc_cfg this_type;
	BOOST_COPYABLE_AND_MOVABLE(this_type);

public:
	tool_splice_copilot_gendoc_cfg(void);
	tool_splice_copilot_gendoc_cfg(tool_splice_copilot_gendoc_cfg_sample);

	tool_splice_copilot_gendoc_cfg(BOOST_RV_REF(this_type) right)
		: file_md_(boost::move(right.file_md_)),
			sp_beg1_(boost::move(right.sp_beg1_)),
			sp_beg2_(boost::move(right.sp_beg2_)),
			sp_end_(boost::move(right.sp_end_))
	{
	}

	tool_splice_copilot_gendoc_cfg(const this_type& right);
	~tool_splice_copilot_gendoc_cfg(void);

public:
	inline this_type& operator=(BOOST_RV_REF(this_type) right)
	{
		this_type& right_ref = right;

		if(this == &right_ref)
		{
			return *this;
		}

		yggr::copy_or_move_or_swap(file_md_, boost::move(right_ref.file_md_));
		yggr::copy_or_move_or_swap(sp_beg1_, boost::move(right_ref.sp_beg1_));
		yggr::copy_or_move_or_swap(sp_beg2_, boost::move(right_ref.sp_beg2_));
		yggr::copy_or_move_or_swap(sp_end_, boost::move(right_ref.sp_end_));

		return *this;
	}

	this_type& operator=(const this_type& right);

public:
	inline void swap(BOOST_RV_REF(this_type) right)
	{
		this_type& right_ref = right;
		this_type::swap(right_ref);
	}

	void swap(this_type& right);

private:
	friend class yggr::serialization::access;

	template<typename Archive>
	void serialize(Archive& ar, const yggr::u32 version)
	{
		ar & YGGR_SERIALIZATION_NVP(file_md_);
		ar & YGGR_SERIALIZATION_NVP(sp_beg1_);
		ar & YGGR_SERIALIZATION_NVP(sp_beg2_);
		ar & YGGR_SERIALIZATION_NVP(sp_end_);
	}

public:
	string_type file_md_;
	string_type sp_beg1_;
	string_type sp_beg2_;
	string_type sp_end_;
};

namespace swap_support
{
	YGGR_PP_SWAP_THIS_REF_DEF(tool_splice_copilot_gendoc_cfg)
} // namespace swap_support

namespace std
{

using swap_support::swap;

} // namespace std

namespace boost
{

using swap_support::swap;

} // namespace boost


#endif // __TOOL_SUO_BATCH_SELECTOR_CFG_HPP__
