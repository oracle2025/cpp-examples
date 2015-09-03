#include <iostream>
#include "todolistserver.h"
#include "todolistserver2.h"
#include "commandadd.h"
#include "todolist.h"
#include <boost/uuid/uuid_generators.hpp>

int main(int argc, const char *argv[])
{
	std::cout << "TodoList Server" << std::endl;

	TodoListServer2::pointer server = TodoListServer2::create();

	TodoLog::pointer log = server->log();

	/*TodoList::id id = boost::uuids::random_generator()();
	TodoList::timestamp timestamp = boost::posix_time::microsec_clock::universal_time();
	Command::pointer cmd = CommandAdd::create(id, timestamp, "Get Milk");
	log->add(cmd);


	id = boost::uuids::random_generator()();
	timestamp = boost::posix_time::microsec_clock::universal_time();
	cmd = CommandAdd::create(id, timestamp, "Call Joe");
	log->add(cmd);

	id = boost::uuids::random_generator()();
	timestamp = boost::posix_time::microsec_clock::universal_time();
	cmd = CommandAdd::create(id, timestamp, "Call Frank");
	log->add(cmd);

	id = boost::uuids::random_generator()();
	timestamp = boost::posix_time::microsec_clock::universal_time();
	cmd = CommandAdd::create(id, timestamp, "Call Peter");
	log->add(cmd);

	id = boost::uuids::random_generator()();
	timestamp = boost::posix_time::microsec_clock::universal_time();
	cmd = CommandAdd::create(id, timestamp, "Call Jen");
	log->add(cmd);
*/
	server->start();

	return 0;
}
