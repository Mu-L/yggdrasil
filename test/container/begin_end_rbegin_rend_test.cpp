// begin_end_rbegin_rend_test.cpp

#include <yggr/base/yggrdef.h>
#include <test/wait_any_key/wait_any_key.hpp>

#include <yggr/container/begin.hpp>
#include <yggr/container/end.hpp>
#include <yggr/container/rbegin.hpp>
#include <yggr/container/rend.hpp>

#include <yggr/container/vector.hpp>
#include <yggr/container/list.hpp>
#include <yggr/container/set.hpp>

#include <yggr/iterator_ex/iterator.hpp>

#include <yggr/compile_link/linker.hpp>

#ifdef _MSC_VER
#	include <vld.h>
#endif // _MSC_VER

template<typename Cont>
void test_begin_detail(Cont& cont)
{
	typedef Cont cont_type;

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	if(cont.size())
	{
		std::cout << (*yggr::begin(cont_ref)) << std::endl;
		std::cout << (*yggr::begin(cont_cref)) << std::endl;
		
		std::cout << (*yggr::cbegin(cont_ref)) << std::endl;
		std::cout << (*yggr::cbegin(cont_cref)) << std::endl;
	}

}

template<typename Val, std::size_t N>
void test_begin_detail(Val (&cont)[N])
{
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	if(N)
	{
		std::cout << (*yggr::begin(cont_ref)) << std::endl;
		std::cout << (*yggr::begin(cont_cref)) << std::endl;
		
		std::cout << (*yggr::cbegin(cont_ref)) << std::endl;
		std::cout << (*yggr::cbegin(cont_cref)) << std::endl;
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

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	if(cont.size())
	{
		std::cout << yggr::distance(yggr::begin(cont_ref), yggr::end(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::begin(cont_cref), yggr::end(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::cbegin(cont_ref), yggr::cend(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::cbegin(cont_cref), yggr::cend(cont_cref)) << std::endl;
	}

}

template<typename Val, std::size_t N>
void test_end_detail(Val (&cont)[N])
{
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	if(N)
	{
		std::cout << yggr::distance(yggr::begin(cont_ref), yggr::end(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::begin(cont_cref), yggr::end(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::cbegin(cont_ref), yggr::cend(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::cbegin(cont_cref), yggr::cend(cont_cref)) << std::endl;
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

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	if(cont.size())
	{
		std::cout << (*yggr::rbegin(cont_ref)) << std::endl;
		std::cout << (*yggr::rbegin(cont_cref)) << std::endl;
		
		std::cout << (*yggr::crbegin(cont_ref)) << std::endl;
		std::cout << (*yggr::crbegin(cont_cref)) << std::endl;
	}

}

template<typename Val, std::size_t N>
void test_rbegin_detail(Val (&cont)[N])
{
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	if(N)
	{
		std::cout << (*yggr::rbegin(cont_ref)) << std::endl;
		std::cout << (*yggr::rbegin(cont_cref)) << std::endl;
		
		std::cout << (*yggr::crbegin(cont_ref)) << std::endl;
		std::cout << (*yggr::crbegin(cont_cref)) << std::endl;
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

	cont_type& cont_ref = cont;
	const cont_type& cont_cref = cont;

	if(cont.size())
	{
		std::cout << yggr::distance(yggr::rbegin(cont_ref), yggr::rend(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::rbegin(cont_cref), yggr::rend(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::crbegin(cont_ref), yggr::crend(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::crbegin(cont_cref), yggr::crend(cont_cref)) << std::endl;
	}

}

template<typename Val, std::size_t N>
void test_rend_detail(Val (&cont)[N])
{
	typedef Val(&cont_ref_type)[N];
	typedef cont_ref_type const cont_cref_type;

	cont_ref_type cont_ref = cont;
	cont_cref_type cont_cref = cont;

	if(N)
	{
		std::cout << yggr::distance(yggr::rbegin(cont_ref), yggr::rend(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::rbegin(cont_cref), yggr::rend(cont_cref)) << std::endl;
		
		std::cout << yggr::distance(yggr::crbegin(cont_ref), yggr::crend(cont_ref)) << std::endl;
		std::cout << yggr::distance(yggr::crbegin(cont_cref), yggr::crend(cont_cref)) << std::endl;
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
