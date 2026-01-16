//identity_test.cpp

#include <test/wait_any_key/wait_any_key.hpp>
#include <yggr/utility/identity.hpp>

#include <iostream>

#ifdef _MSC_VER
#	include <vld.h>
#endif // _MSC_VER



int main(int argc, char* argv[])
{
	yggr::utility::identity idt;

	std::cout << idt(10) << std::endl;
	assert(idt(10) == 10);

	std::cout << idt(10.5f) << std::endl;
	assert(idt(10.5f) == 10.5f);

	wait_any_key(argc, argv);
	return 0;
}