//foo_t_info_std_bind_impl.hpp

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

#ifndef __YGGR_FUNC_DETAIL_FOO_T_INFO_STD_BIND_IMPL_HPP__
#define __YGGR_FUNC_DETAIL_FOO_T_INFO_STD_BIND_IMPL_HPP__

#	if !defined(__YGGR_FUNC_FOO_T_INFO_HPP__)
#		error "foo_t_info_std_bind_impl.hpp is a impl file, please include foo_t_info.hpp"
#	endif // __YGGR_FUNC_FOO_T_INFO_HPP__

#if !defined(YGGR_NO_CXX11_VARIADIC_TEMPLATES) && defined(YGGR_FOO_T_INFO_SUPPORT_STD_BIND)


template<typename BindT>
struct foo_t_info_real_tpl_std_bind
{
private:
	typedef BindT std_bind_type;
	typedef mplex::typename_caster<std_bind_type> std_bind_caster_type;
	typedef typename std_bind_caster_type::template apply<boost::mpl::vector> tmp_std_bind_tpl_args;
	typedef typename tmp_std_bind_tpl_args::type std_bind_tpl_args;

	typedef typename boost::mpl::at_c<std_bind_tpl_args, 0>::type R;
	typedef typename boost::mpl::at_c<std_bind_tpl_args, 1>::type F;

private:
	typedef foo_t_info_real_tpl_detail<F> base_type;
	//typedef BindT<R, F, Args...> tpl_arg_type;
	typedef std_bind_type tpl_arg_type;

public:
	typedef typename base_type::null_type null_type;

	typedef typename base_type::result_type result_type;

	typedef boost::mpl::true_ is_callable_type;
	typedef boost::mpl::false_ is_native_foo_type;
	typedef typename base_type::is_member_foo_type is_member_foo_type;
	typedef typename base_type::has_va_list_type has_va_list_type;

	typedef typename base_type::class_type class_type;

	typedef typename base_type::arg_list_type arg_list_type;

private:
	typedef typename ::yggr::func::bind_av_list_cast<tpl_arg_type>::type av_list_type;

	typedef typename
		boost::mpl::copy_if
		<
			av_list_type,
			detail::is_placeholder_arg<boost::mpl::_>,
			boost::mpl::back_inserter< boost::mpl::vector<>::type >
		>::type nord_av_arg_list_type;

	typedef typename
		boost::mpl::sort
		<
			nord_av_arg_list_type,
			detail::placeholder_arg_less<boost::mpl::_1, boost::mpl::_2>
		>::type ord_av_arg_list_type;

	typedef typename
		boost::mpl::if_
		<
			is_member_foo_type,
			typename
				boost::mpl::push_front
				<
					arg_list_type,
					tag_object_reference
					<
						typename
							boost::mpl::if_
							<
								typename base_type::is_const_type,
								const class_type,
								class_type
							>::type
					>
				>::type,
			arg_list_type
		>::type av_arg_list_type;

public:
	typedef typename
		mplex::revert_to_vector
		<
			typename
				boost::mpl::transform
				<
					ord_av_arg_list_type,
					detail::conv_to_arg
					<
						boost::mpl::_1,
						av_list_type,
						av_arg_list_type
					>
				>::type
		>::type arg_holder_list_type;

	typedef typename base_type::is_const_type is_const_type;
	typedef typename base_type::is_volatile_type is_volatile_type;
	typedef typename base_type::is_noexcept_type is_noexcept_type;
	typedef typename base_type::arg_list_size_type arg_list_size_type;
	typedef boost::mpl::size_t<boost::mpl::size<arg_holder_list_type>::value> arg_holder_list_size_type;

	typedef tpl_arg_type foo_type;
	typedef typename boost::add_pointer<foo_type>::type foo_pointer_type;
	typedef typename boost::add_reference<foo_type>::type foo_reference_type;

	typedef typename base_type::foo_type native_foo_type;
	typedef typename base_type::foo_pointer_type native_foo_pointer_type;
	typedef typename base_type::foo_reference_type native_foo_reference_type;

	typedef foo_type type;
};

#if defined(__GNUC__) \
	&& ( (__GNUC__ > 15) || ( (__GNUC__ == 15) && (defined(__GNUC_MINOR__) && (__GNUC_MINOR__ > 1) ) ) )

template<typename _Functor, typename... _Bound_args>
struct foo_t_info_real_tpl_std_bind< std::_Bind< _Functor(_Bound_args...) > >
{
private:
	typedef std::_Bind< _Functor(_Bound_args...) > std_bind_type;

	typedef typename boost::remove_pointer<_Functor>::type F;

private:
	typedef foo_t_info_real_tpl_detail<F> base_type;
	typedef typename boost::mpl::vector<typename base_type::result_type, F, _Bound_args...>::type tpl_arg_type;

public:
	typedef typename base_type::null_type null_type;

	typedef typename base_type::result_type result_type;

	typedef boost::mpl::true_ is_callable_type;
	typedef boost::mpl::false_ is_native_foo_type;
	typedef typename base_type::is_member_foo_type is_member_foo_type;
	typedef typename base_type::has_va_list_type has_va_list_type;

	typedef typename base_type::class_type class_type;

	typedef typename base_type::arg_list_type arg_list_type;

private:
	typedef typename ::yggr::func::bind_av_list_cast<tpl_arg_type>::type av_list_type;

	typedef typename
		boost::mpl::copy_if
		<
			av_list_type,
			detail::is_placeholder_arg<boost::mpl::_>,
			boost::mpl::back_inserter< boost::mpl::vector<>::type >
		>::type nord_av_arg_list_type;

	typedef typename
		boost::mpl::sort
		<
			nord_av_arg_list_type,
			detail::placeholder_arg_less<boost::mpl::_1, boost::mpl::_2>
		>::type ord_av_arg_list_type;

	typedef typename
		boost::mpl::if_
		<
			is_member_foo_type,
			typename
				boost::mpl::push_front
				<
					arg_list_type,
					tag_object_reference
					<
						typename
							boost::mpl::if_
							<
								typename base_type::is_const_type,
								const class_type,
								class_type
							>::type
					>
				>::type,
			arg_list_type
		>::type av_arg_list_type;

public:
	typedef typename
		mplex::revert_to_vector
		<
			typename
				boost::mpl::transform
				<
					ord_av_arg_list_type,
					detail::conv_to_arg
					<
						boost::mpl::_1,
						av_list_type,
						av_arg_list_type
					>
				>::type
		>::type arg_holder_list_type;

	typedef typename base_type::is_const_type is_const_type;
	typedef typename base_type::is_volatile_type is_volatile_type;
	typedef typename base_type::is_noexcept_type is_noexcept_type;
	typedef typename base_type::arg_list_size_type arg_list_size_type;
	typedef boost::mpl::size_t<boost::mpl::size<arg_holder_list_type>::value> arg_holder_list_size_type;

	typedef std_bind_type foo_type;
	typedef typename boost::add_pointer<foo_type>::type foo_pointer_type;
	typedef typename boost::add_reference<foo_type>::type foo_reference_type;

	typedef typename base_type::foo_type native_foo_type;
	typedef typename base_type::foo_pointer_type native_foo_pointer_type;
	typedef typename base_type::foo_reference_type native_foo_reference_type;

	typedef foo_type type;
};

#endif // __GNUC__ gcc > 15.1

#if defined(__GNUC__) && defined(__clang__)

template<typename _Fp, typename... _BoundArgs>
struct foo_t_info_real_tpl_std_bind< std::__bind<_Fp, _BoundArgs...> >
{
private:
	typedef std::__bind<_Fp, _BoundArgs...> std_bind_type;

	typedef typename boost::remove_pointer<_Fp>::type F;

private:
	typedef foo_t_info_real_tpl_detail<F> base_type;
	typedef typename boost::mpl::vector<typename base_type::result_type, F, _BoundArgs...>::type tpl_arg_type;

public:
	typedef typename base_type::null_type null_type;

	typedef typename base_type::result_type result_type;

	typedef boost::mpl::true_ is_callable_type;
	typedef boost::mpl::false_ is_native_foo_type;
	typedef typename base_type::is_member_foo_type is_member_foo_type;
	typedef typename base_type::has_va_list_type has_va_list_type;

	typedef typename base_type::class_type class_type;

	typedef typename base_type::arg_list_type arg_list_type;

private:
	typedef typename ::yggr::func::bind_av_list_cast<tpl_arg_type>::type av_list_type;

	typedef typename
		boost::mpl::copy_if
		<
			av_list_type,
			detail::is_placeholder_arg<boost::mpl::_>,
			boost::mpl::back_inserter< boost::mpl::vector<>::type >
		>::type nord_av_arg_list_type;

	typedef typename
		boost::mpl::sort
		<
			nord_av_arg_list_type,
			detail::placeholder_arg_less<boost::mpl::_1, boost::mpl::_2>
		>::type ord_av_arg_list_type;

	typedef typename
		boost::mpl::if_
		<
			is_member_foo_type,
			typename
				boost::mpl::push_front
				<
					arg_list_type,
					tag_object_reference
					<
						typename
							boost::mpl::if_
							<
								typename base_type::is_const_type,
								const class_type,
								class_type
							>::type
					>
				>::type,
			arg_list_type
		>::type av_arg_list_type;

public:
	typedef typename
		mplex::revert_to_vector
		<
			typename
				boost::mpl::transform
				<
					ord_av_arg_list_type,
					detail::conv_to_arg
					<
						boost::mpl::_1,
						av_list_type,
						av_arg_list_type
					>
				>::type
		>::type arg_holder_list_type;

	typedef typename base_type::is_const_type is_const_type;
	typedef typename base_type::is_volatile_type is_volatile_type;
	typedef typename base_type::is_noexcept_type is_noexcept_type;
	typedef typename base_type::arg_list_size_type arg_list_size_type;
	typedef boost::mpl::size_t<boost::mpl::size<arg_holder_list_type>::value> arg_holder_list_size_type;

	typedef std_bind_type foo_type;
	typedef typename boost::add_pointer<foo_type>::type foo_pointer_type;
	typedef typename boost::add_reference<foo_type>::type foo_reference_type;

	typedef typename base_type::foo_type native_foo_type;
	typedef typename base_type::foo_pointer_type native_foo_pointer_type;
	typedef typename base_type::foo_reference_type native_foo_reference_type;

	typedef foo_type type;
};

#endif // #if defined(__GNUC__) && defined(__clang__)

template<typename T>
struct foo_t_info_real_tpl_detail_sel<T, true>
    : public foo_t_info_real_tpl_std_bind<T>
{
};

#endif // YGGR_NO_CXX11_VARIADIC_TEMPLATES && defined(YGGR_FOO_T_INFO_SUPPORT_STD_BIND)

#endif // __YGGR_FUNC_DETAIL_FOO_T_INFO_STD_BIND_IMPL_HPP__
