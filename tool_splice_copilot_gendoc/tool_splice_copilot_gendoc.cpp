// test_project_maker.cpp



#include <yggr/base/yggrdef.h>

#include "tool_splice_copilot_gendoc_cfg.hpp"

#include <yggr/charset/string.hpp>
#include <yggr/charset/utf8_string.hpp>
#include <yggr/regular_parse/regex_parse.hpp>

#include <yggr/container/set.hpp>
#include <yggr/container/unordered_set.hpp>

#include <yggr/archive/xml_archive_partner.hpp>
#include <yggr/packet/packet.hpp>

#include <yggr/file_system/local_fsys_operators.hpp>
#include <yggr/algorithm/knuth_morris_pratt.hpp>

#include <iostream>
#include <sstream>

#include <yggr/compile_link/linker.hpp>

#ifdef _MSC_VER
#	include <vld.h>
#endif //_MSC_VER

#include YGGR_PP_LINK_LIB(exception)
#include YGGR_PP_LINK_LIB(system_controller)
#include YGGR_PP_LINK_LIB(regular_parse)
#include YGGR_PP_LINK_LIB(charset)
#include YGGR_PP_LINK_LIB(time)
#include YGGR_PP_LINK_LIB(ids)
#include YGGR_PP_LINK_LIB(base)


typedef yggr::file_system::local_fsys_operators local_fsys_operators_type;
typedef local_fsys_operators_type::directory_entry_type directory_entry_type;
typedef local_fsys_operators_type::path_type path_type;

typedef yggr::knuth_morris_pratt<yggr::string::const_iterator> kmp_type;

static const char* tool_splice_copilot_gendoc_cfg_mark = "tool_splice_copilot_gendoc_cfg";

template<typename Buffer>
Buffer& read_from_file(Buffer& file_content, const yggr::utf8_string& fpath)
{
	try
	{
		local_fsys_operators_type::read_file_of_binary(local_fsys_operators_type::make_path_object(fpath), file_content);
	}
	catch(const local_fsys_operators_type::exception_type& e)
	{
		std::cerr << e.what() << std::endl;
		assert(false);
	}

	return file_content;
}

template<typename Buffer>
Buffer& read_from_file(Buffer& file_content, const path_type& fpath)
{
	try
	{
		local_fsys_operators_type::read_file_of_binary(fpath, file_content);
	}
	catch(const local_fsys_operators_type::exception_type& e)
	{
		std::cerr << e.what() << std::endl;
		assert(false);
	}

	return file_content;
}

template<typename Buffer>
bool write_to_file(const yggr::utf8_string& fname, const Buffer& fbuf)
{
	try
	{
		local_fsys_operators_type::write_file_of_binary(
			local_fsys_operators_type::make_path_object(fname), fbuf,
			local_fsys_operators_type::options_type::dir_create_if_not_exists);
	}
	catch(const local_fsys_operators_type::exception_type& e)
	{
		std::cerr << e.what() << std::endl;
		assert(false);
		return false;
	}

	return true;
}


bool is_validate_sp_beg(yggr::string::const_iterator s, yggr::string::const_iterator e)
{
	return std::find(s, e, '\n') == e;
}

yggr::utf8_string get_out_fname(const yggr::utf8_string& out_dir, const yggr::string& fname)
{
	int n = 1;
	yggr::utf8_string tmp_out_fname;


	do
	{
		if(n - 1)
		{
			std::stringstream ss;
			ss << n;
			tmp_out_fname = out_dir + "/" + fname + " (" + ss.str() + ")" + ".md";
		}
		else
		{
			tmp_out_fname = out_dir + "/" + fname + ".md";
		}

		++n;
	} while(local_fsys_operators_type::is_exists(local_fsys_operators_type::make_path_object(tmp_out_fname)));
	
	return tmp_out_fname;
}

yggr::string get_file_dir(const yggr::string& file_path)
{
	std::size_t pos1 = file_path.rfind('/');
	std::size_t pos2 = file_path.rfind('\\');

	std::size_t pos = 
		(std::max)(
			(pos1 == yggr::string::npos? 0 : pos1), 
			(pos2 == yggr::string::npos? 0 : pos2));

	return pos == 0?  yggr::string(".") : file_path.substr(0, pos);
}

yggr::utf8_string get_file_dir(const yggr::utf8_string& file_path)
{
	yggr::string ret_str = get_file_dir(file_path.org_str());

	return yggr::utf8_string(ret_str, YGGR_STR_UTF8_STRING_CHARSET_NAME());

}

bool write_cfg_file(const yggr::utf8_string& fname, const tool_splice_copilot_gendoc_cfg& cfg)
{
	typedef yggr::packet::packet<yggr::archive::archive_partner::xml_oarchive_partner> opak_type;

	opak_type opak;
	opak.save(YGGR_SERIALIZATION_NAME_NVP(tool_splice_copilot_gendoc_cfg_mark, cfg));

	return write_to_file(fname, opak.org_buf());
}

bool read_cfg_file(const yggr::utf8_string& fname, tool_splice_copilot_gendoc_cfg& cfg)
{
	typedef yggr::packet::packet<yggr::archive::archive_partner::xml_iarchive_partner> ipak_type;

	ipak_type ipak;
	return
		read_from_file(ipak.org_buf(), fname).size()
		&& ipak.load(YGGR_SERIALIZATION_NAME_NVP(tool_splice_copilot_gendoc_cfg_mark, cfg));
}


void tool_splice_copilot_gendoc(const yggr::utf8_string& fpath, 
									const yggr::utf8_string& sp_beg1, 
									const yggr::utf8_string& sp_beg2, 
									const yggr::utf8_string& sp_end)
{
	typedef std::pair<yggr::string::const_iterator, yggr::string::const_iterator> iter_pair_type;

	yggr::string file_buf;

	read_from_file(file_buf, fpath);


	yggr::string::const_iterator src_siter = file_buf.begin();
	yggr::string::const_iterator src_eiter = file_buf.end();


	kmp_type kmp_beg1(sp_beg1.org_str().begin(), sp_beg1.org_str().end());
	kmp_type kmp_beg2(sp_beg2.org_str().begin(), sp_beg2.org_str().end());
	kmp_type kmp_end(sp_end.org_str().begin(), sp_end.org_str().end());

	yggr::utf8_string out_dir = get_file_dir(fpath);

	bool beg2_is_ext = 
		(sp_beg2.org_str() == ".hpp"
			|| sp_beg2.org_str() == ".ipp"
			|| sp_beg2.org_str() == ".h"
			|| sp_beg2.org_str() == ".c"
			|| sp_beg2.org_str() == ".cpp");

	
	for(;src_siter != src_eiter;)
	{
		iter_pair_type iter_beg1_pair = kmp_beg1(src_siter, src_eiter);
		if(iter_beg1_pair.first == iter_beg1_pair.second)
		{
			break;
		}

		iter_pair_type iter_beg2_pair = kmp_beg2(iter_beg1_pair.second, src_eiter);
		if(iter_beg2_pair.first == iter_beg2_pair.second)
		{
			break;
		}

		if(!is_validate_sp_beg(iter_beg1_pair.first, iter_beg2_pair.second))
		{
			src_siter = iter_beg2_pair.second;
			continue;
		}

		yggr::utf8_string out_fname = 
			beg2_is_ext?
				get_out_fname(out_dir, yggr::string(iter_beg1_pair.second, iter_beg2_pair.first) + sp_beg2)
				: get_out_fname(out_dir, yggr::string(iter_beg1_pair.second, iter_beg2_pair.first));
		
		iter_pair_type iter_end_pair = kmp_end(iter_beg2_pair.second, src_eiter);

		yggr::string file_buf;

		if(iter_end_pair.first != iter_end_pair.second)
		{
			file_buf.assign(iter_beg1_pair.first, iter_end_pair.first);
		}
		else
		{
			file_buf.assign(iter_beg1_pair.first, src_eiter);
		}

		static const yggr::string file_buf_title = "---\n";

		write_to_file(out_fname, file_buf_title + file_buf);

		src_siter = iter_end_pair.second;
	}


	//std::cout << file_buf << std::endl;

}



static yggr::utf8_string cfg_fname("tool_splice_copilot_gendoc_cfg.xml");

int main_detail(int argc, char* argv[])
{
	if(argc > 1)
	{
		cfg_fname = yggr::utf8_string(argv[1], YGGR_STR_UTF8_STRING_CHARSET_NAME());
	}

	if(!local_fsys_operators_type::is_exists(local_fsys_operators_type::make_path_object(cfg_fname)))
	{
		tool_splice_copilot_gendoc_cfg cfg_sample = tool_splice_copilot_gendoc_cfg(tool_splice_copilot_gendoc_cfg_sample());
		write_cfg_file(cfg_fname, cfg_sample);
		std::cout << "gen config file succeed, please modify it" << std::endl;
		return -1;
	}

	tool_splice_copilot_gendoc_cfg cfg;

	if(!read_cfg_file(cfg_fname, cfg))
	{
		std::cout << "read config file failed" << std::endl;
		return -1;
	}

	tool_splice_copilot_gendoc(cfg.file_md_, cfg.sp_beg1_, cfg.sp_beg2_, cfg.sp_end_);

	return 0;
}

int main(int argc, char* argv[])
{
	int ret = main_detail(argc, argv);

	std::cout << "end" << std::endl;
	char cc = 0;
	std::cin >> cc;
	return ret;
}