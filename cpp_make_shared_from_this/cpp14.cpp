#include <memory>
#include <iostream>

struct Good: std::enable_shared_from_this<Good> // note: public inheritance
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};

int main(int argc, const char *argv[])
{
	auto g = std::make_shared<Good>();
	auto p = g->getptr();
	auto &r = *std::make_shared<Good>().get();
	//auto p = std::make_unique<int>(42);
	std::cout << typeid(g).name() << std::endl;
	std::cout << typeid(p).name() << std::endl;
	std::cout << (g == p) << std::endl;
	std::cout << typeid(r).name() << std::endl;
	std::cout << r.getptr().use_count() << std::endl;
	return 0;
}
