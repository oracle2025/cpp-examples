#include "todolistserver.h"
#include <boost/bind.hpp>
#include <iostream>
#include "commandparser.h"

TodoListServer::TodoListServer() :
	m_log(TodoLog::create())
{
	m_receiver = SimpleReceiver::create(2015,
			boost::bind(&TodoListServer::receive, this, _1)
			);
}

TodoListServer::pointer TodoListServer::create()
{
    return pointer(new TodoListServer);
}

void TodoListServer::start()
{
	m_receiver->run();
}

void TodoListServer::receive(const std::string &input)
{
	std::cout << "TodoListServer::receive: " << input << std::endl;
	// if input == "request:never" || "request:timestamp..."
	// Send all log entries or all log entries since timestamp as result
	// Needs some sort of "connection" ideom
	// ConnectionFactory {
	// 	Connection create(log, send_callback);
	// }
	// class Connection {
	// 	 void Connection(log, function<> send)
	//   void receive(string input)
	//   }
	std::size_t remaining;
	Command::pointer cmd = CommandParser::parse(input, remaining);
	if (cmd) {
		m_log->add(cmd);
	}
}

