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
	Command::pointer cmd = CommandParser::parse(input);
	if (cmd) {
		m_log->add(cmd);
	}
}


