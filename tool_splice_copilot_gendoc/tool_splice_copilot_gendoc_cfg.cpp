// tool_splice_copilot_gendoc_cfg.cpp

#include "tool_splice_copilot_gendoc_cfg.hpp"

#ifdef _MSC_VER
#	include <vld.h>
#endif //_MSC_VER

tool_splice_copilot_gendoc_cfg::tool_splice_copilot_gendoc_cfg(void)
{
}

#if defined(__MINGW32__)

tool_splice_copilot_gendoc_cfg::tool_splice_copilot_gendoc_cfg(tool_splice_copilot_gendoc_cfg_sample)
	: file_md_("./test_data/all.md"),
		sp_beg1_("# "),
		sp_beg2_(L" doc"),
		sp_end_(L"alucard-dracula: create_doc")
{
}

#else

tool_splice_copilot_gendoc_cfg::tool_splice_copilot_gendoc_cfg(tool_splice_copilot_gendoc_cfg_sample)
	: file_md_("./test_data/all.md"),
		sp_beg1_("# "),
        sp_beg2_(L" 文档"),
		sp_end_(L"alucard-dracula: 为这个文件生成文档")
{
}

#endif // __MINGW32__

tool_splice_copilot_gendoc_cfg::tool_splice_copilot_gendoc_cfg(const this_type& right)
	: file_md_(right.file_md_),
		sp_beg1_(right.sp_beg1_),
		sp_beg2_(right.sp_beg2_),
		sp_end_(right.sp_end_)
{
}

tool_splice_copilot_gendoc_cfg::~tool_splice_copilot_gendoc_cfg(void)
{
}

tool_splice_copilot_gendoc_cfg::this_type&
	tool_splice_copilot_gendoc_cfg::operator=(const this_type& right)
{
	if(this == &right)
	{
		return *this;
	}

	file_md_ = right.file_md_;
	sp_beg1_ = right.sp_beg1_;
	sp_beg2_ = right.sp_beg2_;
	sp_end_ = right.sp_end_;

	return *this;
}

void tool_splice_copilot_gendoc_cfg::swap(this_type& right)
{
	if(this == &right)
	{
		return;
	}

	yggr::swap(file_md_, right.file_md_);
	yggr::swap(sp_beg1_, right.sp_beg1_);
	yggr::swap(sp_beg2_, right.sp_beg2_);
	yggr::swap(sp_end_, right.sp_end_);
}

namespace swap_support
{
	YGGR_PP_SWAP_THIS_REF_DEF_IMPL(tool_splice_copilot_gendoc_cfg)
} // namespace swap_support
