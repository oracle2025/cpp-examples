#include <memory>
#include <iostream>


int main(int argc, const char *argv[])
{
	auto p = std::make_unique<int>(42);
	std::cout << *p << std::endl;
	return 0;
}
