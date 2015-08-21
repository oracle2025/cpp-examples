#include "simplereceiver.h"
#include <iostream>
#include "command_parser.h"

int main(int argc, const char *argv[])
{

	CommandParser parser;
	try {
		SimpleReceiver server(2014, [&parser](const std::string& s){
				std::cout << "-" << s << "-" << std::endl;
				parser.debug_print_command(parser.parse(s));
				});
		server.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
