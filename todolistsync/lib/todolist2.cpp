#include "todolist2.h"
#include <boost/uuid/uuid_io.hpp>



TodoList2::TodoList2(const std::string& server) :
	m_display(0),
	m_log(TodoLog::create()),
	m_connection(TodoListClient::create([this](Command::pointer cmd){from_connection(cmd);}, server))
{
	m_connection->get();
}

TodoList2::pointer TodoList2::create(const std::string &server)
{
    return pointer(new TodoList2(server));
}

void TodoList2::from_connection(Command::pointer cmd)
{
	std::cout << "from_connection: " << cmd->getId() << std::endl;
	type_lock lock(m_mutex);
	m_display->send(cmd);
	m_log->add(cmd);
}

void TodoList2::from_display(Command::pointer cmd)
{
	type_lock lock(m_mutex);
	m_connection->send(cmd);
	m_log->add(cmd);
}

void TodoList2::setDisplay(ITodoListDisplay *display)
{
	m_display = display;
	m_display->setFromDisplayFunction([this](Command::pointer cmd){from_display(cmd);});
}

void TodoList2::close()
{
	m_connection->close();
}

void TodoList2::run()
{
	m_connection->run();
}

