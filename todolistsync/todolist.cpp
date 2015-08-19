#include "todolist.h"
#include "commandadd.h"
#include "commandedit.h"
#include "commandremove.h"
#include "commandcheck.h"
#include "commanduncheck.h"
#include <boost/uuid/uuid_generators.hpp>

TodoList::TodoList() :
	m_log(TodoLog::create())
{
}

bool TodoList::checked(id id_) const
{
    return true;
}

TodoList::id TodoList::add(const std::string &value)
{
	TodoList::id id = boost::uuids::random_generator()();
	TodoList::timestamp timestamp = std::chrono::system_clock::now();
	Command::pointer cmd = CommandAdd::create(id, timestamp, value);
	m_log->add(cmd);
	return id;
}

TodoList::pointer TodoList::create()
{
    return pointer(new TodoList);
}

std::list<TodoList::id> TodoList::ids() const
{
	std::list<id> result;
    return result;
}

std::string TodoList::get(id id_) const
{
    return "";
}

void TodoList::check(id id_)
{
	TodoList::timestamp timestamp = std::chrono::system_clock::now();
	Command::pointer cmd = CommandCheck::create(id_, timestamp);
	m_log->add(cmd);
}

void TodoList::edit(id id_, const std::string &value)
{
	TodoList::timestamp timestamp = std::chrono::system_clock::now();
	Command::pointer cmd = CommandEdit::create(id_, timestamp, value);
	m_log->add(cmd);
}

void TodoList::remove(id id_)
{
	TodoList::timestamp timestamp = std::chrono::system_clock::now();
	Command::pointer cmd = CommandRemove::create(id_, timestamp);
	m_log->add(cmd);
}

void TodoList::uncheck(id id_)
{
	TodoList::timestamp timestamp = std::chrono::system_clock::now();
	Command::pointer cmd = CommandUncheck::create(id_, timestamp);
	m_log->add(cmd);
}

