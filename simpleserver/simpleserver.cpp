#include <iostream>
#include "tcpserver.h"


int main(int argc, const char *argv[])
{
	try {
		TCPServer server(2014, [](){return "bla\n";});
		server.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
