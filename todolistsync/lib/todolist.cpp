#include "todolist.h"
#include "commandadd.h"
#include "commandedit.h"
#include "commandremove.h"
#include "commandcheck.h"
#include "commanduncheck.h"
#include <boost/uuid/uuid_generators.hpp>

TodoList::TodoList(const std::string& server) :
	m_log(TodoLog::create()),
	m_client(TodoListClient::create(server))
{
}

bool TodoList::checked(id id_) const
{
    return true;
}

TodoList::id TodoList::add(const std::string &value)
{
	TodoList::id id = boost::uuids::random_generator()();
	TodoList::timestamp timestamp = boost::posix_time::microsec_clock::universal_time();
	Command::pointer cmd = CommandAdd::create(id, timestamp, value);
	log(cmd);
	return id;
}

TodoList::pointer TodoList::create(const std::string& server)
{
    return pointer(new TodoList(server));
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
	TodoList::timestamp timestamp = boost::posix_time::microsec_clock::universal_time();
	Command::pointer cmd = CommandCheck::create(id_, timestamp);
	log(cmd);
}

void TodoList::edit(id id_, const std::string &value)
{
	TodoList::timestamp timestamp = boost::posix_time::microsec_clock::universal_time();
	Command::pointer cmd = CommandEdit::create(id_, timestamp, value);
	log(cmd);
}

void TodoList::remove(id id_)
{
	TodoList::timestamp timestamp = boost::posix_time::microsec_clock::universal_time();
	Command::pointer cmd = CommandRemove::create(id_, timestamp);
	log(cmd);
}

void TodoList::uncheck(id id_)
{
	TodoList::timestamp timestamp = boost::posix_time::microsec_clock::universal_time();
	Command::pointer cmd = CommandUncheck::create(id_, timestamp);
	log(cmd);
}
void TodoList::log(Command::pointer cmd)
{
	//Send to m_client!
	m_client->send(cmd->serialize());
	m_log->add(cmd);
}

