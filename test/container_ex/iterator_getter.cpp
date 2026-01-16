// iterator_getter.cpp


#include <yggr/base/yggrdef.h>
#include <test/wait_any_key/wait_any_key.hpp>

#include <yggr/container_ex/begin_getter.hpp>
#include <yggr/container_ex/end_getter.hpp>
#include <yggr/container_ex/rbegin_getter.hpp>
#include <yggr/container_ex/rend_getter.hpp>

#include <yggr/container/vector.hpp>
#include <yggr/container/list.hpp>
#include <yggr/container/set.hpp>

#ifdef _MSC_VER
#	include <vld.h>
#endif // _MSC_VER


template<typename Cont>
void test_begin_detail(Cont& cont)
{
	typedef Cont cont_type;
	typedef yggr::container_ex::begin_getter<cont_type> getter_type;
	typedef yggr::container_ex::cbegin_getter<cont_type> cgetter_type;

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(cont.size())
	{
		std::cout << (*getter(cont_ref)) << std::endl;
		std::cout << (*getter(cont_cref)) << std::endl;
		
		std::cout << (*cgetter(cont_ref)) << std::endl;
		std::cout << (*cgetter(cont_cref)) << std::endl;
	}

}

template<typename Val, std::size_t N>
void test_begin_detail(Val (&cont)[N])
{
	typedef Val (cont_type)[N];
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	typedef yggr::container_ex::begin_getter<cont_type> getter_type;
	typedef yggr::container_ex::cbegin_getter<cont_type> cgetter_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(N)
	{
		std::cout << (*getter(cont_ref)) << std::endl;
		std::cout << (*getter(cont_cref)) << std::endl;
		
		std::cout << (*cgetter(cont_ref)) << std::endl;
		std::cout << (*cgetter(cont_cref)) << std::endl;
	}

}

void test_begin(void)
{
	int test_data[3] = {1, 2, 3};

	{
		test_begin_detail(test_data);
	}

	{
		typedef yggr::vector<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_begin_detail(cont);
	}

	{
		typedef yggr::list<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_begin_detail(cont);
	}

	{
		typedef yggr::set<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_begin_detail(cont);
	}
}

template<typename Cont>
void test_end_detail(Cont& cont)
{
	typedef Cont cont_type;
	typedef yggr::container_ex::end_getter<cont_type> getter_type;
	typedef yggr::container_ex::cend_getter<cont_type> cgetter_type;

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(cont.size())
	{
		std::cout << yggr::distance(yggr::begin(cont_ref), getter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::cbegin(cont_cref), cgetter(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::cbegin(cont_ref), cgetter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::cbegin(cont_cref), cgetter(cont_cref)) << std::endl;
	}
}

template<typename Val, std::size_t N>
void test_end_detail(Val (&cont)[N])
{
	typedef Val (cont_type)[N];
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	typedef yggr::container_ex::end_getter<cont_type> getter_type;
	typedef yggr::container_ex::cend_getter<cont_type> cgetter_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(N)
	{
		std::cout << yggr::distance(yggr::begin(cont_ref), getter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::cbegin(cont_cref), cgetter(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::cbegin(cont_ref), cgetter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::cbegin(cont_cref), cgetter(cont_cref)) << std::endl;
	}
}

void test_end(void)
{
	int test_data[3] = {1, 2, 3};

	{
		test_end_detail(test_data);
	}

	{
		typedef yggr::vector<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_end_detail(cont);
	}

	{
		typedef yggr::list<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_end_detail(cont);
	}

	{
		typedef yggr::set<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_end_detail(cont);
	}
}

template<typename Cont>
void test_rbegin_detail(Cont& cont)
{
	typedef Cont cont_type;
	typedef yggr::container_ex::rbegin_getter<cont_type> getter_type;
	typedef yggr::container_ex::crbegin_getter<cont_type> cgetter_type;

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(cont.size())
	{
		std::cout << (*getter(cont_ref)) << std::endl;
		std::cout << (*getter(cont_cref)) << std::endl;
		
		std::cout << (*cgetter(cont_ref)) << std::endl;
		std::cout << (*cgetter(cont_cref)) << std::endl;
	}

}

template<typename Val, std::size_t N>
void test_rbegin_detail(Val (&cont)[N])
{
	typedef Val (cont_type)[N];
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	typedef yggr::container_ex::rbegin_getter<cont_type> getter_type;
	typedef yggr::container_ex::crbegin_getter<cont_type> cgetter_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(N)
	{
		std::cout << (*getter(cont_ref)) << std::endl;
		std::cout << (*getter(cont_cref)) << std::endl;
		
		std::cout << (*cgetter(cont_ref)) << std::endl;
		std::cout << (*cgetter(cont_cref)) << std::endl;
	}

}

void test_rbegin(void)
{
	int test_data[3] = {1, 2, 3};

	{
		test_rbegin_detail(test_data);
	}

	{
		typedef yggr::vector<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_rbegin_detail(cont);
	}

	{
		typedef yggr::list<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_rbegin_detail(cont);
	}

	{
		typedef yggr::set<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_rbegin_detail(cont);
	}
}

template<typename Cont>
void test_rend_detail(Cont& cont)
{
	typedef Cont cont_type;
	typedef yggr::container_ex::rend_getter<cont_type> getter_type;
	typedef yggr::container_ex::crend_getter<cont_type> cgetter_type;

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(cont.size())
	{
		std::cout << yggr::distance(yggr::rbegin(cont_ref), getter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::crbegin(cont_cref), cgetter(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::crbegin(cont_ref), cgetter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::crbegin(cont_cref), cgetter(cont_cref)) << std::endl;
	}
}

template<typename Val, std::size_t N>
void test_rend_detail(Val (&cont)[N])
{
	typedef Val (cont_type)[N];
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	typedef yggr::container_ex::rend_getter<cont_type> getter_type;
	typedef yggr::container_ex::crend_getter<cont_type> cgetter_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	getter_type getter;
	cgetter_type cgetter;

	if(N)
	{
		std::cout << yggr::distance(yggr::rbegin(cont_ref), getter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::crbegin(cont_cref), cgetter(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::crbegin(cont_ref), cgetter(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::crbegin(cont_cref), cgetter(cont_cref)) << std::endl;
	}
}

void test_rend(void)
{
	int test_data[3] = {1, 2, 3};

	{
		test_rend_detail(test_data);
	}

	{
		typedef yggr::vector<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_rend_detail(cont);
	}

	{
		typedef yggr::list<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_rend_detail(cont);
	}

	{
		typedef yggr::set<int> cont_type;
		cont_type cont(test_data, test_data + 3);
		test_rend_detail(cont);
	}
}

int main(int argc, char *argv[])
{
	test_begin();

	std::cout << "-------------" << std::endl;

	test_end();

	std::cout << "-------------" << std::endl;

	test_rbegin();

	std::cout << "-------------" << std::endl;

	test_rend();

	std::cout << "-------------" << std::endl;

	wait_any_key(argc, argv);
	return 0;
}
