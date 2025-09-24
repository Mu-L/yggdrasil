//io_error_def.hpp

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

#ifndef __YGGR_NETWORK_IO_IO_ERROR_DEF_HPP__
#define __YGGR_NETWORK_IO_IO_ERROR_DEF_HPP__

#include <yggr/base/yggrdef.h>
#include <yggr/exception/exception.hpp>
#include <yggr/base/error_make.hpp>

#define YGGR_PP_NETWORK_IO_ERROR_DEF( __io_name__ ) \
	ERROR_MAKER_BEGIN( __io_name__ ) \
		ERROR_CODE_DEF_BEGIN(exception::exception_sort::E_code_start_17) \
			ERROR_CODE_DEF(E_invalid_recv_size) \
			ERROR_CODE_DEF(E_invalid_recv_head) \
			ERROR_CODE_DEF(E_invalid_recv_data) \
		ERROR_CODE_DEF_END(exception::exception_sort::E_code_end_17) \
	\
		ERROR_CODE_MSG_BEGIN() \
			ERROR_CODE_MSG(E_invalid_recv_size, "invalid recv size") \
			ERROR_CODE_MSG(E_invalid_recv_head, "invalid recv head") \
			ERROR_CODE_MSG(E_invalid_recv_data, "invalid recv data") \
		ERROR_CODE_MSG_END() \
	ERROR_MAKER_END()

namespace yggr
{
namespace network
{
namespace io
{
} // namespace io
} // namespace network
} // namespace yggr

#endif //__YGGR_NETWORK_IO_IO_ERROR_DEF_HPP__
