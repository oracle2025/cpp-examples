#include <iostream>
#include "tcpserver.h"
#include <sstream>


int main(int argc, const char *argv[])
{
	int count = 0;
	try {
		TCPServer server(2014, [&count](){std::stringstream h; h << count++ << "\n";return h.str();});
		server.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
